#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "grafo.h"

/* Solucao é uma classe filha de Grafo. */
class Solucao : public Grafo
{
    public:        
	Solucao(int nodos = 0);         	/* Construtor da classe. Inicializa o grafo com um determinado número de nodos. */

	Solucao(const Solucao &s);	        /* Construtor */

	void insereTerminal(int t);     	/* Insere um terminal. */

	vector< int > getTerminals();	    /* retorna o vetor de terminais */

	int getAvaliacao();		            /* retorna o valor da avaliacao */	

	void setAvaliacao(int x);           /* seta o valor da avaliaçao. */

	void print();                  		/* Imprime toda estrutura. Sobrescrita do método da classe Grafo. */

	void printTerminais();		        /* Imprime apenas os terminais. */

	void printNodosIn();		        /* Imprime apenas os nodos contidos na solução */

	bool ehSolucao();              	    /* Verifica se o grafo armazenado é uma solução so problema.
								   Isto é, se é uma árvore e se contém todos os nodos terminais. */
				   
	void insereAresta( aresta_t a );	/* Insere uma aresta no Grafo. Sobrescrita da função de Grafo. */

	void removeAresta( aresta_t a );	/* Remove uma aresta do grafo. Sobrescrita da função de Grafo. */

	bool ehConexo();                	/* Verifica se todos nodos que estão presentes na solução são conexos.
								   Deve ser executado depois de temCiclo(int) */
				   
	bool temTerminais();           	    /* Verifica se todos terminais estão presentes na solução. */

	bool existe(aresta_t a);		    /* Verifica se uma aresta está na solução */

	void trivial( Grafo g );        	/* Acha uma solução trivial */

	void criaVizinhos(vector<Solucao> *v, Grafo g);	/* Cria um vetor com vizinhos da solucao atual */	

	void printPontuacao();               /* Escreve a pontuaçao do grafo na tela. */

	void incTabu();			/* incrementa o contador */

	void setTabu(int x);		/* seta o contador com um valor */

	int getTabu();				/* retorna o valor do contador */
	
	aresta_t getInserida();		/* retorna a aresta inserida */
	aresta_t getRemovida();		/* retorna a aresta removida */
	void setTabuAtivo();
	void resetTabuAtivo();
	bool igualInserida(aresta_t a);
	bool igualRemovida(aresta_t a);
	
    protected:
        vector< int > terminals;        	/* Além dos atributos de um Grafo, Contém um vetor de terminais. */
        
    private:
        int avaliacao;				/* Guarda a soma dos pesos das arestas contidas na solução */
        vector<int> nodosIn;            	/* Nodos que estão contidos no grafo. Como a estrutura grafo é do tamanho máximo, 
							este vetor guarda quais nodos foram efetivemente inseridos na solução. */
    
        int contTabu;				/* Usado para contar o tempo de permanencia na lista tabu */
    
	aresta_t inserida;				/* aresta inserida pra criar essa solução */
	aresta_t removida;				/* aresta removida pra criar essa solução */
	bool tabuAtivo;			/* Indica se essa solução é tabu ativa ou não */
    
};

#endif
