#include "GreedyOrdenado.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <fstream>


using namespace std;

#define str(a) to_string(a)

GreedyOrdenado::GreedyOrdenado(const Instance &_inst, std::string output): inst_(_inst),bl_(_inst),inicial_(_inst){
    output_ = output;
}

void GreedyOrdenado::execute(int buscaLocal, int bins/* = 0*/, int maxExato /*= 0*/){
    melhorSol_ = inicial_.createOrdered();

    if (buscaLocal == 1){
        #ifdef DEBUG
            cout << "Busca reordenaUm" << endl;
        #endif
        bl_.reordenaUm(melhorSol_);
    } else if (buscaLocal == 2){
        #ifdef DEBUG
            cout << "Busca lp" << endl;
        #endif
        bl_.lp(melhorSol_,bins,maxExato);
    }
    #ifdef DEBUG
        writeSolution();
    #endif
    writeResultFile(output_);

}

void GreedyOrdenado::writeResultFile(string filename){
    #ifdef DEBUG
        cout << "Escrevendo arquivo" << endl;
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
    // cout << "Quantas caixas: " << k << endl;
    // for (unsigned int i = 0; i < melhorSol_.size(); i++){
    //     if (melhorSol_[i].ocupado() != 0){
    //         elegivel++;
    //         myfile << elegivel << " " << melhorSol_[i].toString() << endl;
    //     }
    // }
    myfile.close();
}

void GreedyOrdenado::writeSolution(){
    int k = 0;
    for (unsigned int i = 0; i < melhorSol_.size(); i++){
        if (melhorSol_[i].ocupado() != 0){
            k++;
        }
    }
    int elegivel = 0;

    cout << "Quantas caixas: " << k << endl;
    for (unsigned int i = 0; i < melhorSol_.size(); i++){
        if (melhorSol_[i].ocupado() !=0){
            elegivel++;
            cout << "Caixa " << elegivel << "(" << 1+i << ") Espaço Livre " << melhorSol_[i].livre() << " Quantidade de itens: " << melhorSol_[i].size() << endl;
            cout << melhorSol_[i].toString() << endl;
        }
    }
}