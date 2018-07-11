CC=g++
OPTIONS=-Wall -g3 -DGRB -std=c++11 -I/opt/gurobi800/linux64/include 
#OPTIONS=-Wall -g3 -DDEBUG -DGRB -std=c++11 -I/opt/gurobi800/linux64/include 

all:binpack

binpack:main.o lp.o Instance.o Container.o Inicial.o BuscaLocal.o GRASP.o ILS.o GreedyRandom.o GreedyOrdenado.o
	$(CC) $(OPTIONS) main.o Instance.o lp.o Container.o Inicial.o BuscaLocal.o GRASP.o ILS.o GreedyRandom.o GreedyOrdenado.o -L/opt/gurobi800/linux64/lib -lgurobi80 -o binpack 
#-lasan -lm `pkg-config --libs cbc` 

main.o:main.cpp 
	$(CC) $(OPTIONS) -c main.cpp -o main.o

Instance.o:Instance.cpp Instance.hpp
	$(CC) $(OPTIONS) -c Instance.cpp -o Instance.o

lp.o:lp.cpp lp.hpp lp.h
	$(CC) $(OPTIONS) -c lp.cpp -o lp.o

Container.o:Container.cpp Container.hpp Instance.o lp.o
	$(CC) $(OPTIONS) -c Container.cpp -o Container.o

Inicial.o:Inicial.cpp Inicial.hpp Instance.o Container.o
	$(CC) $(OPTIONS) -c Inicial.cpp -o Inicial.o

BuscaLocal.o:BuscaLocal.cpp BuscaLocal.hpp Instance.o Container.o lp.o
	$(CC) $(OPTIONS) -c BuscaLocal.cpp -o BuscaLocal.o 

GRASP.o:GRASP.cpp GRASP.hpp Instance.o BuscaLocal.o Container.o Inicial.o
	$(CC) $(OPTIONS) -c GRASP.cpp -o GRASP.o

ILS.o:ILS.cpp ILS.hpp Instance.o BuscaLocal.o Container.o Inicial.o
	$(CC) $(OPTIONS) -c ILS.cpp -o ILS.o

GreedyRandom.o:GreedyRandom.cpp GreedyRandom.hpp Instance.o BuscaLocal.o Container.o Inicial.o
	$(CC) $(OPTIONS) -c GreedyRandom.cpp -o GreedyRandom.o

GreedyOrdenado.o:GreedyOrdenado.cpp GreedyOrdenado.hpp Instance.o BuscaLocal.o Container.o Inicial.o
	$(CC) $(OPTIONS) -c GreedyOrdenado.cpp -o GreedyOrdenado.o

clean:
	rm -rf *.o *~ jssp