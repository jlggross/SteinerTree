#ifndef SET_H
#define SET_H

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

// estrutura de aresta. dois nodos interligados e um peso.
typedef struct{
	int n1, n2;         /* Nodos interligados pelo v�rtice. */
	int peso;           /* Peso da liga��o entre estes v�rtices. */
} aresta_t;

// Classe Set
class Set
{
    public:
        Set();                     /* Construtor. */
        
        void insere(aresta_t a);   /* Insere uma aresta no conjunto. */
        
        void remove(aresta_t a);   /* Insere uma aresta no conjunto. */
    
	vector< aresta_t > getConjunto();
        
        aresta_t aleatoria(int seed);      /* Devolve uma aresta aleat�ria do conjunto. */
        
    protected:
        vector< aresta_t > conjunto;         /* Conjunto de arestas */   
};

#endif
