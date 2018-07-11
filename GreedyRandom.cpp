#include "GreedyRandom.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <fstream>


using namespace std;

#define str(a) to_string(a)

GreedyRandom::GreedyRandom(const Instance &_inst, std::string output): inst_(_inst),bl_(_inst),inicial_(_inst){
    output_ = output;
}

void GreedyRandom::execute(int buscaLocal, int bins/* = 0*/, int maxExato /*= 0*/){

    melhorSol_ = inicial_.createRandom();

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
        #ifdef DEBUG
            cout << "terminou lp" << endl;
        #endif
    }
    writeSolution();
    writeResultFile(output_);

}

void GreedyRandom::writeResultFile(string filename){
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
}

void GreedyRandom::writeSolution(){
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