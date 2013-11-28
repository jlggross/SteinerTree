#ifndef GRAFO_H
#define GRAFO_H

#include "set.h"

typedef struct{
	int v;
	int peso;
	bool acessado;
} node_t;

class Grafo {
	public:
		Grafo(int nodos = 0);
		void insereAresta( aresta_t a );
		void removeAresta( aresta_t a );
		void print();
		vector< vector<node_t> > getGraph();
		bool ciclo(int nodo);
		bool temCiclo(int nodo);
		aresta_t random(int seed);
		Set getArestas();
	protected:
		vector< vector<node_t> > graph;
		int arestas;
		int nodos;
		vector<bool> visitado;
		Set setArestas;
};

#endif