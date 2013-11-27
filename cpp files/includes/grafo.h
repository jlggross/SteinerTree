#ifndef GRAFO_H
#define GRAFO_H

#include "set.h"

// estrutura de um nodo, com um peso associado para chegar de um outro nodo neste.
typedef struct{
	int v;               /* V�rtice a que � ligado. */
	int peso;            /* Peso da liga��o entre os v�rices 'v' e o v�rtice que cont�m 'v'. */
	bool acessado;       /* booleano para marcar se este v�rtice j� foi escolhido. Utilizado 
                            por m�todos da classe Solucao */
}node_t;

// Classe Grafo
class Grafo
{
    public:
        Grafo(int nodos = 0);                   	/* Construtor do grafo. Inicia o grafo com um certo de 
								n�mero de nodos( default � 0 ) */
        
        void insereAresta( aresta_t a );	/* Insere uma aresta no grafo. */
        
        void removeAresta( aresta_t a );	/* Remove uma aresta do grafo. */
        
        void print();                           		/* Imprime o grafo na tela. */
        
        vector< vector<node_t> > getGraph();    /* Devolve a estrutura que armazena o grafo. */
        
        bool ciclo(int nodo);                   	/* Verifica se tem ciclo. N�o precisa inicializar nada. */
        
        bool temCiclo(int nodo);		/* Verifica se o grafo possui algum ciclo. 
								IMPORTANTE: Para usar esta fun��o eh preciso zerar o vector visitado 
								e os membros acessado dos v�rtices. */
        
        aresta_t random(int seed);		/* Devolve uma aresta aleat�ria do grafo. */
    
	    Set getArestas();				/* Retorna o conjunto das arestas do grafo. */
        
    protected:
        vector< vector<node_t> > graph;	/* Lista de adjac�ncia dos nodos */
        int arestas;                            		/* N�mero de arestas do grafo */
        int nodos;                              		/* N�mero de nodos do grafo */
    
        vector<bool> visitado;                  	/* Vetor auxiliar para verificar ciclos. */   
        
        Set setArestas;                         	/* Conjunto das arestas do grafo. */     
};

#endif
