#include "BuscaLocal.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <functional>


using namespace std;

#define str(a) toString(a)

BuscaLocal::BuscaLocal( const Instance &_inst ) : inst_(_inst){
}


void BuscaLocal::lp(vector<Container> &sol, int bins, int timeout){
    int tamanho = sol.size();
    if (bins > tamanho){
        bins = tamanho;
    }
    mip = lp_create();
    #ifdef DEBUG
        cout << "Timeout do modelo: "<< timeout <<" Quantidade de bins: " << bins << endl;
    #endif
    lp_set_max_seconds( mip, timeout );
    vector<int> sorteio = vector<int>();
    
    for (int i = 0; i < tamanho; i++){
        if (sol[i].ocupado() != 0){
            sorteio.push_back(i);
        }
    }

    random_shuffle (sorteio.begin(), sorteio.end());

    #ifdef DEBUG
        cout << "Bins escolhidos: "<< endl;
        for (int j = 0; j < bins; j++){
            cout << "Bin " << sorteio[j]+1 << " Itens: " << sol[sorteio[j]].toString() << endl;
        }
    #endif

    vector<int> itens = vector<int>();
    for (int j = 0; j < bins; j++){
        for (int item : sol[sorteio[j]].itens()){
            itens.push_back(item);
        }
    }

    #ifdef DEBUG
        cout << "Itens a serem redimensionados: "<< endl;
        for (unsigned int j = 0; j < itens.size(); j++){
            cout << itens[j]+1 << " ";
        }
        cout << endl;
    #endif

    vector< string > names;
    vector< double > lb;
    vector< double > ub;
    vector< double > obj;
    vector< char > integer;
    vector<vector<int>> x = vector<vector<int>>(itens.size(),vector<int>(tamanho));
    vector<int> y = vector<int>(tamanho);

    // variaveis
    for (int j = 0; j < bins; j++){
        y[j] = names.size();
        names.push_back("y("+to_string(sorteio[j]+1)+")");
        lb.push_back( 0.0 );
        ub.push_back( 1 );
        obj.push_back( 1 );
        integer.push_back( 1 );
        for (unsigned int i = 0; i < itens.size(); i++){
      
            x[i][j] = names.size();
            //cout << "x("+to_string(itens[i])+","+to_string(sorteio[j])+")" << " ";
            names.push_back("x("+to_string(itens[i]+1)+","+to_string(sorteio[j]+1)+")");
            lb.push_back( 0.0 );
            ub.push_back( 1 );
            obj.push_back( 0 );
            integer.push_back( 1 );
        }
        //std::cin.get();
    }

    lp_add_cols(mip, obj, lb, ub, integer, names);
    //std::cin.get();
    #ifdef DEBUG
        cout << "Variáveis criadas "<< endl;
    #endif

    // restricao capacidade
    for (int j = 0; j < bins; j++){
        vector< int > idx;
        vector< double > coef;
        for (unsigned int i = 0; i < itens.size(); i++){
            idx.push_back(x[i][j]);
            coef.push_back(inst_.w(itens[i]));
            
        }
        idx.push_back(y[j]);
        coef.push_back(-1 * inst_.c());
        
        lp_add_row( mip, idx, coef, "capacidade(j="+to_string(sorteio[j]+1)+")", 'L', 0 );
    }
    #ifdef DEBUG
        cout << "Restrição capacidade ok "<< endl;
    #endif

    // restricao alocacao unica
    for (unsigned int i = 0; i < itens.size(); i++){
        vector< int > idx;
        vector< double > coef;
        for (int j = 0; j < bins; j++){
            idx.push_back(x[i][j]);
            coef.push_back(1);
        }
        lp_add_row( mip, idx, coef, "unico(i="+to_string(itens[i]+1)+")", 'E', 1 );
    }

    #ifdef DEBUG
        cout << "Restrição alocação ok "<< endl;
    #endif

    // restricao conflito
    for (unsigned int i = 0; i < itens.size(); i++){
        for (unsigned int j = 0; j < itens.size(); j++){
            if (inst_.conflito(itens[i],itens[j])){
                for (int k = 0; k < bins; k++){
                    vector< int > idx;
                    vector< double > coef;
                    idx.push_back(x[i][k]);
                    coef.push_back(1);
                    idx.push_back(x[j][k]);
                    coef.push_back(1);
                    lp_add_row( mip, idx, coef, "conflito(i="+to_string(itens[i]+1)+",j="+to_string(itens[j]+1)+",k="+to_string(sorteio[k]+1)+")", 'L', 1 );
                }
            }
        }
    }
    #ifdef DEBUG
        cout << "Restrição conflito ok "<< endl;
    #endif

    lp_write_lp( mip, "teste.lp" );
    int status = lp_optimize( mip );
    if (status == 0 || status == 3){
    
        double* x_opt = lp_x(mip);

        #ifdef DEBUG
            cout << "Valores obtidos: " << endl;
            for (unsigned int i = 0; i < names.size(); i++){
                if (x_opt[i] == 1)
                    cout << names[i] << " = " << x_opt[i] << endl;
            }
        #endif

        for (int j = 0; j < bins; j++){
            #ifdef DEBUG
                cout << "Limpando bin  " << sorteio[j]+1;
            #endif
            sol[sorteio[j]].clear();
            #ifdef DEBUG
                cout << " itens:  " << sol[sorteio[j]].toString() << endl;
            #endif
            if (x_opt[y[j]] == 1){ // se o bin ainda continua na solução, inserir os itens dele
                for (unsigned int i = 0; i < itens.size(); i++){
                    if (x_opt[x[i][j]] == 1){
                        #ifdef DEBUG
                            cout << "variável  " << names[x[i][j]] << " no bin " << sorteio[j] << endl;
                        #endif
                        sol[sorteio[j]].incluiritem(itens[i]);
                    }
                }
            }
            #ifdef DEBUG
                cout << "bin: " << sorteio[j]+1 <<" Conteúdo:  " << sol[sorteio[j]].toString() << endl;
            #endif
        }
    }
    #ifdef DEBUG
        
        cout << "Bins: " << tamanho << endl;
        for (int i = 0; i < tamanho; i++){
            cout << "Bin  " << i+1 << " tamanho " << sol[i].size() << ". Itens: " << sol[i].toString() << endl;
        }

    #endif
    
    //lp_write_sol(mip, "jssp_flow.sol");
    //std::cin.get();
    
    lp_free(&mip);
    
}

void BuscaLocal::reordenaUm(std::vector<Container> &sol){
    
    unsigned int bin = rand() % sol.size();
    #ifdef DEBUG
        cout << "Bin escolhido: "<< bin+1 << endl;
        cout << "Itens do bin escolhido(" << sol[bin].size() << "): "<< sol[bin].toString() << endl;
    #endif
    int tamanho = sol[bin].size();
    for (int i = tamanho-1; i >= 0; i--){
        //cout << bin << endl;
        //cout << sol[bin].toString() << endl;
        //vector<int> itens = sol[bin].itens();
        //int item = itens[i];
        int item = sol[bin].item(i);
        #ifdef DEBUG
            cout << "Item escolhido: "<< item+1 << endl;
        #endif
        for (unsigned int j = 0; j < sol.size(); j++){
            if (j == bin || sol[j].ocupado() == 0) continue;
            #ifdef DEBUG
                cout << "Tentando colocar no bin: " << j+1 << endl;
            #endif
            if (sol[j].incluiritem(item)){
                #ifdef DEBUG
                    cout << "Item " << item+1 << " incluído no bin " << j+1 << ". Novo espaço livre: " << sol[j].livre() << " itens atualmente: " << sol[j].toString() << endl;
                #endif  
                sol[bin].removerItem(item);
                #ifdef DEBUG
                    cout << "Item " << item+1 << " excluído do bin " << bin+1 << ". Novo espaço livre: " << sol[bin].livre() << " itens atualmente: " << sol[bin].toString() << endl;
                #endif
                break;  
            }
        }
        //std::cin.get();
    }
    // if (sol[bin].size() == 0) {
    //     sol.erase(sol.begin()+bin);
    // }
}

void BuscaLocal::menosCheio(int bins, std::vector<Container> &sol){
    //sort (sol.begin(), sol.end(), greater<Container>()); // a seed vai ser a iteração
    #ifdef DEBUG
        cout << "Ordem dos bins: "<< endl;
        for (unsigned int i = 0; i < sol.size(); i++ ){
            cout << "Bin: " << i+1 << " Espaço livre: " << sol[i].livre() << " Itens: " << sol[i].toString() << endl;
        }
    #endif
    

    #ifdef DEBUG
        cout << "Bins a serem verificados: " << bins << endl;
    #endif
    for (int b = 0; b < bins; b++){
        int ultimobin = sol.size() - b - 1;
        #ifdef DEBUG
            cout << "Verificando bin: " << ultimobin << endl;
        #endif
        for (int i = 0; i < sol[ultimobin].size(); i++){
            int item = sol[ultimobin].item(item);
            #ifdef DEBUG
                cout << "Item a ser movido: " << item+1 << endl;
            #endif

            for (int j = 0; j < ultimobin; j++){
                #ifdef DEBUG
                    cout << "Tentando colocar no bin: " << j << endl;
                #endif
                if (sol[j].incluiritem(item)){
                    #ifdef DEBUG
                        cout << "Item incluído no bin " << j << " itens atualmente: " << sol[j].toString() << endl;
                    #endif  
                    sol[ultimobin].removerItem(item);
                    #ifdef DEBUG
                        cout << "Item excluído do bin " << i << " itens atualmente: " << sol[i].toString() << endl;
                    #endif  
                }
            }
        }
        
        std::cin.get();
    }


}