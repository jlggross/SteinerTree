#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "grafo.h"

/* Solucao � uma classe filha de Grafo. */
class Solucao : public Grafo
{
    public:        
	Solucao(int nodos = 0);         	/* Construtor da classe. Inicializa o grafo com um determinado n�mero de nodos. */

	Solucao(const Solucao &s);	        /* Construtor */

	void insereTerminal(int t);     	/* Insere um terminal. */

	vector< int > getTerminals();	    /* retorna o vetor de terminais */

	int getAvaliacao();		            /* retorna o valor da avaliacao */	

	void setAvaliacao(int x);           /* seta o valor da avalia�ao. */

	void print();                  		/* Imprime toda estrutura. Sobrescrita do m�todo da classe Grafo. */

	void printTerminais();		        /* Imprime apenas os terminais. */

	void printNodosIn();		        /* Imprime apenas os nodos contidos na solu��o */

	bool ehSolucao();              	    /* Verifica se o grafo armazenado � uma solu��o so problema.
								   Isto �, se � uma �rvore e se cont�m todos os nodos terminais. */
				   
	void insereAresta( aresta_t a );	/* Insere uma aresta no Grafo. Sobrescrita da fun��o de Grafo. */

	void removeAresta( aresta_t a );	/* Remove uma aresta do grafo. Sobrescrita da fun��o de Grafo. */

	bool ehConexo();                	/* Verifica se todos nodos que est�o presentes na solu��o s�o conexos.
								   Deve ser executado depois de temCiclo(int) */
				   
	bool temTerminais();           	    /* Verifica se todos terminais est�o presentes na solu��o. */

	bool existe(aresta_t a);		    /* Verifica se uma aresta est� na solu��o */

	void trivial( Grafo g );        	/* Acha uma solu��o trivial */

	void criaVizinhos(vector<Solucao> *v, Grafo g);	/* Cria um vetor com vizinhos da solucao atual */	

	void printPontuacao();               /* Escreve a pontua�ao do grafo na tela. */

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
        vector< int > terminals;        	/* Al�m dos atributos de um Grafo, Cont�m um vetor de terminais. */
        
    private:
        int avaliacao;				/* Guarda a soma dos pesos das arestas contidas na solu��o */
        vector<int> nodosIn;            	/* Nodos que est�o contidos no grafo. Como a estrutura grafo � do tamanho m�ximo, 
							este vetor guarda quais nodos foram efetivemente inseridos na solu��o. */
    
        int contTabu;				/* Usado para contar o tempo de permanencia na lista tabu */
    
	aresta_t inserida;				/* aresta inserida pra criar essa solu��o */
	aresta_t removida;				/* aresta removida pra criar essa solu��o */
	bool tabuAtivo;			/* Indica se essa solu��o � tabu ativa ou n�o */
    
};

#endif
