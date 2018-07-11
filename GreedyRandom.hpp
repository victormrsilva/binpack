#ifndef GREEDYRANDOM_HPP
#define GREEDYRANDOM_HPP

#include "Instance.hpp"
#include "Container.hpp"
#include "BuscaLocal.hpp"
#include "Inicial.hpp"
#include <string>
#include <vector>

class GreedyRandom{
public:

    GreedyRandom(const Instance &_inst, std::string output);

    void execute(int buscaLocal, int bins = 0, int maxExato = 0);

    void writeSolution();

    void writeResultFile(std::string filename);



private:
    const Instance &inst_;
    BuscaLocal bl_;
    Inicial inicial_;
    std::string output_;
    std::vector<Container> melhorSol_;
};

#endif

