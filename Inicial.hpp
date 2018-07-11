#ifndef INICIAL_HPP
#define INICIAL_HPP

#include "Instance.hpp"
#include "Container.hpp"
#include <string>
#include <vector>

/*
    Tenta colocar todos os itens de uma forma aleatória no primeiro container que conseguir. 
    Se não conseguir colocar em nenhum, cria novo container.
    Há número de repetições para tentar encontrar melhores.
*/
class Inicial{
public:

    Inicial(const Instance &_inst);

    bool removerItem(int i);

    bool incluiritem(int i);

    std::vector<int> itens() { return itens_; };

    std::string toString();

    std::vector<Container> createRandom();

    std::vector<Container> createOrdered();

    void writeSolution();

    void writeResultFile(char* filename);

    int caixas();

    bool wayToSort(int i, int j) { return inst_.w(i) > inst_.w(j); }

private:
    const Instance &inst_;
    int repeat_;
    
    std::vector<Container> containers;

    std::vector< int > itens_;

};

#endif

