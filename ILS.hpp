#ifndef ILS_HPP
#define ILS_HPP

#include "Instance.hpp"
#include "Container.hpp"
#include "BuscaLocal.hpp"
#include "Inicial.hpp"
#include <string>
#include <vector>

/*
    Tenta colocar todos os itens de uma forma aleatória no primeiro container que conseguir. 
    Se não conseguir colocar em nenhum, cria novo container.
    Há número de repetições para tentar encontrar melhores.
*/
class ILS{
public:

    ILS(const Instance &_inst, std::string output);

    void execute(int repeticoes, int inicial, int bins, int timeout);

    void writeSolution(std::vector<Container> &sol);

    void writeResultFile(std::string filename);

    bool sortCheio(Container i, Container j) { return i.size() > j.size(); }

private:
    const Instance &inst_;
    BuscaLocal bl_;
    Inicial inicial_;
    std::vector<Container> melhorSol_;
    int maxTime_;
    int repeticoes_;
    int k_;
    std::string output_;
};

#endif

