#include "GRASP.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <functional>
#include <fstream>

using namespace std;

#define str(a) to_string(a)

GRASP::GRASP( const Instance &_inst, string output ) : inst_(_inst),bl_(_inst),inicial_(_inst){
    output_ = output;
    k_ = inst_.n();
}

void GRASP::execute(int repeticoes, int buscaLocal, int bins, int timeout){
    for (int i = 0; i < repeticoes; i++){
        vector<Container> sol = inicial_.createRandom();
        #ifdef DEBUG
            cout << "Solução antes da busca local: " << endl;
            writeSolution(sol);
        #endif
        //bl_.menosCheio(2, sol);
        if (buscaLocal != 1){
            bl_.reordenaUm(sol);
        }
        if (buscaLocal != 0){
            bl_.lp(sol,bins,timeout);
        }
        int k_novo = 0;
        for (unsigned int i = 0; i < sol.size(); i++){
            if (sol[i].ocupado() != 0){
                k_novo++;
            }
        }
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

void GRASP::writeSolution(vector<Container> &sol){
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

void GRASP::writeResultFile(string filename){
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