#include "Inicial.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <functional>



using namespace std;

#define str(a) to_string(a)

Inicial::Inicial( const Instance &_inst) : inst_(_inst){
    containers = vector<Container>();
}

vector<Container> Inicial::createRandom(){
    containers.clear();
    vector<int> itens = vector<int>(inst_.n(),-1);
    for (int i = 0; i < inst_.n(); i++){
        itens[i] = i;
    }

    // inicia repetições

    // dar shuffle no vetor itens
    shuffle (itens.begin(), itens.end(), std::default_random_engine(time(NULL))); // a seed vai ser a iteração

    Container c = Container(inst_);
    containers.push_back(c);

    int melhor_container = 0; // melhor container para inserir (o que tem mais espaço livre)
    int melhor_livre = containers[0].livre();

    for (int i = 0; i < inst_.n(); i++){
        int a = itens[i];
        // tenta incluir no container de 
        if (containers[melhor_container].incluiritem(a)){
            // atualiza containuer com espaço livre
            for (unsigned int i = 0; i < containers.size(); i++){
                melhor_livre -= inst_.w(a);
                if (containers[i].livre() > melhor_livre){
                    melhor_container = i;
                    melhor_livre = containers[i].livre();
                }
            }
            continue;
        } 

        // não consegui. tentar incluir nos demais containers
        bool incluiu = false;
        for(unsigned int j = 0; j < containers.size(); j++){
            if (i == melhor_container)
                continue;

            if (containers[j].incluiritem(a)){
                incluiu = true;

                break;
            }
        }

        if (incluiu){ // conseguiu incluir em um outro
            continue;
        }


        // caso não tenha nenhum novo container para incluir, incluir neste. se espaço livre dele for maior que o atual melhor, ela se torna o atual melhor
        Container novo = Container(inst_);
        novo.incluiritem(a);
        if (melhor_livre < novo.livre()){
            melhor_livre = novo.livre();
            melhor_container = containers.size();
        }
        containers.push_back(novo);
    }

    return containers;
    
    // writeSolution();
    // containers.clear();
    
    
    //writeSolution();
}

vector<Container> Inicial::createOrdered(){
    vector<int> itens = vector<int>(inst_.n(),-1);
    for (int i = 0; i < inst_.n(); i++){
        itens[i] = i;
    }

    // dar shuffle no vetor itens
    sort (itens.begin(), itens.end(), bind(&Inicial::wayToSort, this, std::placeholders::_1, std::placeholders::_2)); // a seed vai ser a iteração
    #ifdef DEBUG
        for (int i : itens){
            cout << "item " << i+1 << " peso: " << inst_.w(i) << endl;
        }
    #endif
    int k = 1;
    Container c = Container(inst_);
    containers.push_back(c);
    
    int melhor_container = 0; // melhor container para inserir (o que tem mais espaço livre)
    int melhor_livre = containers[0].livre();

    for (int i = 0; i < inst_.n(); i++){
        int a = itens[i];
        // tenta incluir no container de 
        if (containers[melhor_container].incluiritem(a)){
    
            // atualiza containuer com espaço livre
            for (int i = 0; i < k; i++){
                melhor_livre -= inst_.w(a);
                if (containers[i].livre() > melhor_livre){
                    melhor_container = i;
                    melhor_livre = containers[i].livre();
                }
            }
            continue;
        } 
    
        // não consegui. tentar incluir nos demais containers
        bool incluiu = false;
        for(int j = 0; j < k; j++){
            if (i == melhor_container)
                continue;

            if (containers[j].incluiritem(a)){
                incluiu = true;

                break;
            }
        }
    
        if (incluiu){ // conseguiu incluir em um outro
            continue;
        }

    
        // caso não tenha nenhum novo container para incluir, incluir neste. se espaço livre dele for maior que o atual melhor, ela se torna o atual melhor
        Container novo = Container(inst_);
    
        k++;
        novo.incluiritem(a);
    
        if (melhor_livre < novo.livre()){
            melhor_livre = novo.livre();
            melhor_container = k-1;
        }
        #ifdef DEBUG
            cout << novo.toString() << endl;
        #endif
        containers.push_back(novo);
    }
        
    return containers;
    //writeSolution();

    
}

int Inicial::caixas(){
    int total = 0;
    for (unsigned int i = 0; i < containers.size(); i++ ){
        if (containers[i].size() != 0){
            total++;
        }
    }
    return total;
}

void Inicial::writeSolution(){
    cout << "Quantas caixas: " << caixas() << endl;
    for (unsigned int i = 0; i < containers.size(); i++){
        cout << "Caixa " << 1+i << " Espaço Livre " << containers[i].livre() << " Quantidade de itens: " << containers[i].size() << endl;
        cout << containers[i].toString() << endl;
    }
}

bool Inicial::removerItem(int i){
    for (unsigned int j = 0; j < itens_.size(); j++){
        if (itens_[j] == i){
            itens_.erase(itens_.begin()+j);
            return true;
        }
    }
    #ifdef DEBUG
        cout << "Item não encontrado" << endl;
    #endif
    return false;
}

bool Inicial::incluiritem(int i){
    for (unsigned int j = 0; j < itens_.size(); j++){
        if (itens_[j] == i){
            #ifdef DEBUG
                cout << "Item já presente neste Inicial" << endl;
            #endif
            return false;
        }
        if (inst_.conflito(i,j)) {
            #ifdef DEBUG
                cout << "Há conflito entre item " << i+1 << " e o item " << j+1 << " que já está no Inicial." << endl;
            #endif
            return false;
        }
    }
    itens_.push_back(i);
    return true;
}