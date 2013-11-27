#ifndef GRAFO_H
#define GRAFO_H

#include "set.h"

// estrutura de um nodo, com um peso associado para chegar de um outro nodo neste.
typedef struct{
	int v;               /* Vértice a que é ligado. */
	int peso;            /* Peso da ligação entre os vérices 'v' e o vértice que contém 'v'. */
	bool acessado;       /* booleano para marcar se este vértice já foi escolhido. Utilizado 
                            por métodos da classe Solucao */
}node_t;

// Classe Grafo
class Grafo
{
    public:
        Grafo(int nodos = 0);                   	/* Construtor do grafo. Inicia o grafo com um certo de 
								número de nodos( default é 0 ) */
        
        void insereAresta( aresta_t a );	/* Insere uma aresta no grafo. */
        
        void removeAresta( aresta_t a );	/* Remove uma aresta do grafo. */
        
        void print();                           		/* Imprime o grafo na tela. */
        
        vector< vector<node_t> > getGraph();    /* Devolve a estrutura que armazena o grafo. */
        
        bool ciclo(int nodo);                   	/* Verifica se tem ciclo. Não precisa inicializar nada. */
        
        bool temCiclo(int nodo);		/* Verifica se o grafo possui algum ciclo. 
								IMPORTANTE: Para usar esta função eh preciso zerar o vector visitado 
								e os membros acessado dos vértices. */
        
        aresta_t random(int seed);		/* Devolve uma aresta aleatória do grafo. */
    
	    Set getArestas();				/* Retorna o conjunto das arestas do grafo. */
        
    protected:
        vector< vector<node_t> > graph;	/* Lista de adjacência dos nodos */
        int arestas;                            		/* Número de arestas do grafo */
        int nodos;                              		/* Número de nodos do grafo */
    
        vector<bool> visitado;                  	/* Vetor auxiliar para verificar ciclos. */   
        
        Set setArestas;                         	/* Conjunto das arestas do grafo. */     
};

#endif
