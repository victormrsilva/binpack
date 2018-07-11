#ifndef BuscaLocal_HPP
#define BuscaLocal_HPP

#include "Instance.hpp"
#include "Container.hpp"
#include "lp.hpp"
#include <string>
#include <vector>

/*
    Tenta colocar todos os itens de uma forma aleatória no primeiro container que conseguir. 
    Se não conseguir colocar em nenhum, cria novo container.
    Há número de repetições para tentar encontrar melhores.
*/
class BuscaLocal{
public:

    BuscaLocal(const Instance &_inst);

    void execute();

    void menosCheio(int bins, std::vector<Container> &sol);

    void reordenaUm(std::vector<Container> &sol);

    void lp(std::vector<Container> &sol, int bins, int timeout);

    bool removerItem(int i);

    bool incluiritem(int i);


    std::string toString();

    void writeSolution();

    void writeResultFile(char* filename);

    bool sortCheio(Container i, Container j) { return i.size() > j.size(); }

    void removeBinVazio(std::vector<Container> &sol);

private:
    const Instance &inst_;
    LinearProgram *mip;
};

#endif

