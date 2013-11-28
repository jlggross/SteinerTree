#ifndef LISTA_TABU_H
#define LISTA_TABU_H

#define BT_MAX 40
#define TABU_SIZE 10
#define TEMPO_TABU 15

#define MAX_AVALIACAO 999999999

#include "solucao.h"

class Listabu {
	public:
		Listabu();
		bool contem(Solucao s);
		void insereTabu(Solucao s);
		bool atualizaOtima( Solucao s );
		void printOtima();
		void printLista();
		olucao getOtima();
		void turno();
	protected:
		vector<Solucao> tabus;
		Solucao otima;
};

#endif