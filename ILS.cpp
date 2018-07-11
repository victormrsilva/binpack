#include "ILS.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <functional>
#include <fstream>

using namespace std;

#define str(a) to_string(a)

ILS::ILS( const Instance &_inst, string output ) : inst_(_inst),bl_(_inst),inicial_(_inst){
    output_ = output;
    k_ = inst_.n();
}

void ILS::execute(int repeticoes, int inicial, int bins, int timeout){
    vector<Container> sol;
    if (inicial == 1)
        sol = inicial_.createOrdered();
    else 
        sol = inicial_.createRandom();

    bl_.lp(sol,bins,timeout);

    int k_novo = 0;
    for (unsigned int i = 0; i < sol.size(); i++){
        if (sol[i].ocupado() != 0){
            k_novo++;
        }
    }

    k_ = k_novo;
    melhorSol_ = sol;
    writeResultFile(output_);
    for (int i = 0; i < repeticoes; i++){
        // perturbação
        sol = melhorSol_;
        bl_.reordenaUm(sol);
        int k_novo = 0;
        for (unsigned int i = 0; i < sol.size(); i++){
            if (sol[i].ocupado() != 0){
                k_novo++;
            }
        }
        #ifdef DEBUG
            cout << "Solução depois da perturbação: " << endl;
            writeSolution(sol);
        #endif
        bl_.lp(sol,bins,timeout);
        #ifdef DEBUG
            cout << "Solução depois da busca local: " << endl;
            writeSolution(sol);
            cout << "k_novo = " << k_novo << " melhor k " << k_ << endl;
        #endif

        if (k_novo < k_){
            melhorSol_ = sol;
            k_ = k_novo;
            writeResultFile(output_);
            #ifdef DEBUG
                cout << "Solução atualizada: " << endl;
                writeSolution(melhorSol_);
            #endif

        }
        sol.clear();
    }
    #ifdef DEBUG
        cout << "Solução encontrada: " << endl;
        writeSolution(melhorSol_);
    #endif
}

void ILS::writeSolution(vector<Container> &sol){
    int k = 0;
    for (unsigned int i = 0; i < sol.size(); i++){
        if (sol[i].ocupado() != 0){
            k++;
        }
    }
    int elegivel = 0;

    cout << "Quantas caixas: " << k << endl;
    for (unsigned int i = 0; i < sol.size(); i++){
        if (sol[i].ocupado() !=0){
            elegivel++;
            cout << "Caixa " << elegivel << "(" << 1+i << ") Espaço Livre " << sol[i].livre() << " Quantidade de itens: " << sol[i].size() << endl;
            cout << sol[i].toString() << endl;
        }
    }
}

void ILS::writeResultFile(string filename){
    #ifdef DEBUG
        cout << "Escrevendo arquivo " << filename << endl;
    #endif

    string out = "";
    int k = 0;
    for (unsigned int i = 0; i < melhorSol_.size(); i++){
        if (melhorSol_[i].ocupado() != 0){
            k++;
            out = out + str(melhorSol_[i].size()) + " " + melhorSol_[i].toString() + '\n';
        }
    }
    //int k = melhorSol_.size();
    ofstream myfile;
    myfile.open (filename);
    myfile << k << endl;
    myfile << out;

    // for (unsigned int i = 0; i < melhorSol_.size(); i++){
    //     if (melhorSol_[i].ocupado() != 0){
    //         k++;
    //     }
    // }
    // //int k = melhorSol_.size();
    // ofstream myfile;
    // myfile.open (filename); 
    // myfile << k << endl;
    // cout << "Quantas caixas: " << k << endl;
    // for (unsigned int i = 0; i < melhorSol_.size(); i++){
    //     if (melhorSol_[i].ocupado() != 0){
    //         elegivel++;
    //         myfile << elegivel << " " << melhorSol_[i].toString() << endl;
    //     }
    // }
    myfile.close();
}