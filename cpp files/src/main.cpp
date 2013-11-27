#include "../includes/steiner.h"
#include "../includes/buscas.h"
#include "time.h"

int main()
{
    /* grafo: como uma lista de adjacências */
	Grafo graph;
	
    /* solução: guardará uma determinada solução e os respectivos terminais. */
	Solucao s;
    
    /* leitura do arquivo de entrada. */
	graph = leEntrada( s );
	
	time_t time1 = time(NULL);
	
	s.trivial(graph);
	
	time_t time2;
	// calcula o tempo gasto e escreve na tela
	double diff;
	//cout << "Tempo gasto = " << diff << "segs" << endl;
	//s.print();
	cout << "Inicial - ";
	s.printPontuacao();
	
	Solucao melhor, primeira, tabu;
	
	//time1 = time(NULL);
	
	//~ melhor = buscaLocalMelhor(s,graph,0);		
	
	//~ time2 = time(NULL);
	//~ // calcula o tempo gasto e escreve na tela
	//~ diff = difftime(time2,time1);
	//~ cout << "Tempo gasto = " << diff << "segs" << endl;
	
	//~ cout << "Melhor - ";
	//~ melhor.printPontuacao();	
	
	//~ primeira = buscaLocalPrimeira(s,graph,0);
	
	//~ time2 = time(NULL);
	//~ // calcula o tempo gasto e escreve na tela
	//~ diff = difftime(time2,time1);
	//~ cout << "Tempo gasto = " << diff << "segs"  << endl;
	
	//~ cout << "Primeira - ";
	//~ primeira.printPontuacao();

	
	Listabu listaTabu;
	listaTabu.atualizaOtima(s);	
		
	tabu = buscaTabuRec(s,graph,0,listaTabu);
	
	time2 = time(NULL);
	// calcula o tempo gasto e escreve na tela
	diff = difftime(time2,time1);
	cout << "Tempo gasto = " << diff << "segs" << endl;
	
	cout << "Tabu - ";
	tabu.printPontuacao();
	
	cout << "Otima Tabu - ";
	listaTabu.printOtima();
	
	
		
	/*
	int inter;		// numero de interações
	int BTmax;	// limite de interações da busca tabu
	
	// TODO - definir o numero de elementos da lista tabu
	// TODO - definir o numero limite de interações	
	
	while (inter < BTmax)
	{
		acha os vizinhos da solução atual.
		percorre os vizinhos e procura algum com um valor da avaliação melhor (menor que a atual)
		avaliação = soma dos pesos das arestas contidas no grafo.		
		Se não existe um vizinho que tenha um valor menor que o da solução atual, 
			pega o que tem o valor mais próximo e coloca a solução atual na Lista Tabu.
			inter++;
		Se existe, usa ele como nova solução atual e inter = 0.
	}
	*/

	return 0;
}

