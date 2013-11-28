#ifndef SET_H
#define SET_H

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct{
	int n1, n2;
	int peso;
} aresta_t;

class Set {
	public:
		Set();
		void insere(aresta_t a);
		void remove(aresta_t a);
		vector< aresta_t > getConjunto();
		aresta_t aleatoria(int seed);
	protected:
		vector< aresta_t > conjunto;
};

#endif