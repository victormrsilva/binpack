#include "Container.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

#define str(a) to_string(a)

Container::Container( const Instance &_inst ): inst_(_inst){
    ocupado_ = 0;
    itens_ = vector<int>();
}

int Container::item(int i) const {
    return itens_[i]; 
}

void Container::clear(){
    itens_.clear();
    ocupado_ = 0;
}

bool Container::removerItem(int i){
    for (unsigned int j = 0; j < itens_.size(); j++){
        if (itens_[j] == i){
            itens_.erase(itens_.begin()+j);
            ocupado_ = ocupado_ - inst_.w(i);
            return true;
        }
    }
    #ifdef DEBUG
        cout << "Item não encontrado" << endl;
    #endif
    return false;
}

bool Container::incluiritem(int i){
    // se não der pra incluir pelo espaço, retornar falso
    if (inst_.w(i) > livre()) {
        #ifdef DEBUG
            cout << "Ultrapassa capacidade" << endl;
        #endif
        return false;
    }

    for (unsigned int j = 0; j < itens_.size(); j++){
        if (itens_[j] == i){
            #ifdef DEBUG
                cout << "Item já presente neste container" << endl;
            #endif
            return false;
        }
        if (inst_.conflito(i,itens_[j])) {
            #ifdef DEBUG
                cout << "Há conflito entre item " << i+1 << " e o item " << j+1 << " que já está no container." << endl;
            #endif
            return false;
        }
    }
    itens_.push_back(i);
    ocupado_ = ocupado_ + inst_.w(i);
    return true;
}

string Container::toString(){
    string out = "";
    for (unsigned int i = 0; i < itens_.size(); i++){
        out = out + str(itens_[i]+1) + " ";
    }
    return out;
}
