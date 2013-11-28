#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "grafo.h"

/* Solucao é uma classe filha de Grafo. */
class Solucao : public Grafo {
	public:
		Solucao(int nodos = 0);
		Solucao(const Solucao &s);
		void insereTerminal(int t);
		vector< int > getTerminals();
		int getAvaliacao();
		void setAvaliacao(int x);
		void print();
		void printTerminais();
		void printNodosIn();
		bool ehSolucao();
		void insereAresta(aresta_t a);
		void removeAresta(aresta_t a);
		bool ehConexo();
		bool temTerminais();
		bool existe(aresta_t a);
		void trivial(Grafo g);
		void criaVizinhos(vector<Solucao> *v, Grafo g);
		void printPontuacao();
		void incTabu();
		void setTabu(int x);
		int getTabu();
		aresta_t getInserida();
		aresta_t getRemovida();
		void setTabuAtivo();
		void resetTabuAtivo();
		bool igualInserida(aresta_t a);
		bool igualRemovida(aresta_t a);
	protected:
		vector< int > terminals;
	private:
		int avaliacao;
		vector<int> nodosIn;
		int contTabu;
		aresta_t inserida;
		aresta_t removida;
		bool tabuAtivo;
};

#endif