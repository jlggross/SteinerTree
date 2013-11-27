#ifndef LISTA_TABU_H
#define LISTA_TABU_H

#define BT_MAX 40
#define TABU_SIZE 10
#define TEMPO_TABU 15

#define MAX_AVALIACAO 999999999

#include "solucao.h"

class Listabu
{
	public:
		Listabu();		/* Construtor, inicia a pos em zero */
		
		bool contem(Solucao s); 	/* Verifica se a lista tabu contem o elemento passado. */
		
		void insereTabu(Solucao s);	/* Insere um elemento na lista tabu */
		
		bool atualizaOtima( Solucao s );    /* Verifica se a solucao s eh melhor que a melhor solucao ateh o momento. */
		
		void printOtima();            /* Imprime a pontuacao da soluacao otima. */
	
		void printLista();		/* Imprime toda a lista da tabus */
	
		Solucao getOtima();	/* Retorna a solucao otima */
		
		void turno();                 /* Incrementa o tempo de todos na lista tabu. */

	protected:
		vector<Solucao> tabus;	    /* lista de solucoes tabu */
		
		Solucao otima;              /* Melhor soluçao encontrada na busca Tabu. */
};


#endif
	
