#include <iostream>
#include "Instance.hpp"
#include "GRASP.hpp"
#include "GreedyRandom.hpp"
#include "GreedyOrdenado.hpp"
#include "ILS.hpp"

using namespace std;

#include <cstdio>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

class Timeout;
static Timeout * global_timeout_instance = 0;

class Timeout {
public:
	int m_timeout;
	jmp_buf env;

	Timeout(int timeout) : m_timeout(timeout) {
		if (global_timeout_instance) {
			throw "Timeout already in use";
		}
		global_timeout_instance = this;
	}

	~Timeout() {
		stop();
		global_timeout_instance = 0;
	}

	static void alarm_handler(int signum) {
		longjmp(global_timeout_instance->env, 1);
	}

	void start() {
		Timeout * ptr = this;
		if (setjmp(env) != 0) {
			// Don't do anything except throw here, since the state
			// is... funky...
			printf("Alarm fired: %p\n", ptr);
			throw global_timeout_instance;
		}
		signal(SIGALRM, alarm_handler);
		alarm(m_timeout);
		printf("Alarm set: %p\n", ptr);
	}

	void stop() {
		alarm(0);
	}
};

int main(int argc, char** argv){

    if (argc < 5){
        cerr << "binpack arquivoInstancia arquivoSolucao maxSeconds tipoAlgoritmo parametros" << endl;
        cerr << "tipoAlgoritmo = A -> Guloso Aleatório; D -> Guloso Ordenado; G -> GRASP; I -> ILS; " << endl;
        cerr << "parametros para:" << endl;
        cerr << "* Guloso Aleatório:  buscaLocal <bins timeout>" << endl;
        cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
        cerr << "* Guloso Ordenado: buscaLocal <bins timeout>" << endl; 
        cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
        cerr << "* GRASP: repeticoes buscaLocal <bins timeout>" << endl;
        cerr << "  - repeticoes" << endl;
        cerr << "  - buscaLocal -> 0 para ambas, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
        cerr << "* ILS: repeticoes metodoInicial bins timeout" << endl;
        cerr << "  - repeticoes" << endl;
        cerr << "  - metodoInicial: 1 para guloso ordenado, 2 para guloso aleatório." << endl;
        cerr << "  - bins timeout -> quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato " << endl;
        return 0;
    }

    string inst_file = argv[1];
    string sol_file = argv[2];
    int maxSeconds = atoi(argv[3]);
    string algoritmo = argv[4];

    srand(time(NULL));
    
    Instance inst(inst_file, maxSeconds);

    try {
		Timeout timeout(maxSeconds); timeout.start();
        if (algoritmo == "A"){
            if (argc < 6){
                cerr << "Para Guloso Aleatório são necessários os seguintes parâmetros: " << endl;
                cerr << "* Guloso Aleatório: buscaLocal <bins timeout>" << endl;
                cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
                return 0;
            }
            int buscaLocal = atoi(argv[5]);

            int bin = 0;
            int timeExato = 0;

            if (buscaLocal == 2){
                if (argc < 8){
                    cerr << "Quantidade de parâmetros insuficiente" << endl;
                    return 0;
                }
                bin = atoi(argv[6]);
                timeExato = atoi(argv[7]);
            }
            GreedyRandom g = GreedyRandom(inst,sol_file);
            g.execute(buscaLocal,bin,timeExato);
        } else
        if (algoritmo == "D"){
            if (argc < 6){
                cerr << "Para Guloso Ordenado são necessários os seguintes parâmetros: " << endl;
                cerr << "* Guloso Ordenado: buscaLocal <bins timeout>" << endl; 
                cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
                return 0;
            }
            int buscaLocal = atoi(argv[5]);

            int bin = 0;
            int timeExato = 0;

            if (buscaLocal == 2){
                if (argc < 8){
                    cerr << "Quantidade de parâmetros insuficiente" << endl;
                    return 0;
                }
                bin = atoi(argv[6]);
                timeExato = atoi(argv[7]);
            }
            GreedyOrdenado g = GreedyOrdenado(inst,sol_file);
            g.execute(buscaLocal,bin,timeExato);
        } else 
        if (algoritmo == "G"){
            if (argc < 7){
                cerr << "Para GRASP são necessários os seguintes parâmetros: " << endl;
                cerr << "* GRASP: repeticoes buscaLocal <bins timeout>" << endl;
                cerr << "  - repeticoes" << endl;
                cerr << "  - buscaLocal -> 2 para ambas, 0 para removeUm, 1 para exato. Caso 2, indicar quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
                return 0;
            }

            int repeticoes = atoi(argv[5]);
            int buscaLocal = atoi(argv[6]);
            int bin = 0;
            int timeExato = 0;
            if (buscaLocal > 0){
                if (argc < 9){
                    cerr << "Quantidade de parâmetros insuficiente" << endl;
                    return 0;
                }
                bin = atoi(argv[7]);
                timeExato = atoi(argv[8]);
            }

            GRASP g = GRASP(inst,sol_file);
            g.execute(repeticoes,buscaLocal,bin,timeExato);
        } else
        if (algoritmo == "I"){
            if (argc < 9){
                cerr << "Para ILS são necessários os seguintes parâmetros: " << endl;
                cerr << "* ILS: repeticoes metodoInicial bins timeout" << endl;
                cerr << "  - repeticoes" << endl;
                cerr << "  - metodoInicial: 1 para guloso ordenado, 2 para guloso aleatório." << endl;
                cerr << "  - bins timeout -> quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato " << endl;
                return 0;
            }
            int repeticoes = atoi(argv[5]);
            int inicial = atoi(argv[6]);
            int bin = atoi(argv[7]);
            int timeExato = atoi(argv[8]);

            ILS i = ILS(inst,sol_file);
            i.execute(repeticoes,inicial,bin,timeExato);
        } else {
            cerr << "binpack arquivoInstancia arquivoSolucao maxSeconds tipoAlgoritmo parametros" << endl;
            cerr << "tipoAlgoritmo = A -> Guloso Aleatório; D -> Guloso Ordenado; G -> GRASP; I -> ILS; " << endl;
            cerr << "parametros para:" << endl;
            cerr << "* Guloso Aleatório: seed buscaLocal <bins timeout>" << endl;
            cerr << "  - seed -> Semente para aleatoriedade. -1 indica tempo como aleatoriedade" << endl;
            cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
            cerr << "* Guloso Ordenado: buscaLocal <bins timeout>" << endl; 
            cerr << "  - buscaLocal -> 0 para nenhum, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos e qual o tempo limite de execução. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
            cerr << "* GRASP: repeticoes buscaLocal <bins timeout>" << endl;
            cerr << "  - repeticoes" << endl;
            cerr << "  - buscaLocal -> 0 para ambas, 1 para removeUm, 2 para exato. Caso 2, indicar quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato" << endl;
            cerr << "* ILS: repeticoes metodoInicial perturbacao bins timeout" << endl;
            cerr << "  - repeticoes" << endl;
            cerr << "  - metodoInicial: 1 para guloso ordenado, 2 para guloso aleatório. A seed do aletório será a iteração" << endl;
            cerr << "  - perturbacao -> 1 para considerar conflitos, 2 para não considerar conflitos. " << endl;
            cerr << "  - bins timeout -> quantos bins serão movidos. Se existirem menos bins do que o indicado, serão considerados todos. timeout é o tempo limite do exato " << endl;
            return 0;
        }
        // GRASP g = GRASP(inst, repeat, maxSeconds);
        // g.execute(0.1);
	} catch (Timeout * t) {
		printf("Timeout!\n");
    }


    return 0;
} 