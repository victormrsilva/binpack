#ifndef GRASP_HPP
#define GRASP_HPP

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
class GRASP{
public:

    GRASP(const Instance &_inst, std::string output);

    std::vector<Container> menosCheio(int bins, std::vector<Container> &sol);

    bool removerItem(int i);

    bool incluiritem(int i);


    std::string toString();

    void execute(int repeticoes, int buscaLocal, int bins, int timeout);

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

