#include "../includes/steiner.h"
#include "../includes/buscas.h"
#include "time.h"

int main() {
	Grafo graph;
	Solucao s;
	graph = leEntrada(s);
	time_t time1 = time(NULL);
	s.trivial(graph);
	time_t time2;
	double diff;
	cout << "Inicial - ";
	s.printPontuacao();
	Solucao melhor, primeira, tabu;
	Listabu listaTabu;
	listaTabu.atualizaOtima(s);	
	tabu = buscaTabuRec(s,graph,0,listaTabu);
	time2 = time(NULL);
	diff = difftime(time2,time1);
	cout << "Tempo gasto = " << diff << "segs" << endl << "Tabu - ";
	tabu.printPontuacao();
	cout << "Otima Tabu - ";
	listaTabu.printOtima();
	return 0;
}