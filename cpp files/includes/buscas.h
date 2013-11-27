/*********************************************************
Autores: Gabriel Portal & Jonas Hartmann

Descri��o: 
Fun��es de busca para achar a solu��o do problema da
           �rvore de Steiner
**********************************************************/
#ifndef BUSCAS_H
#define BUSCAS_H

#define ITER_MAX 100

#include <iostream>
#include <string>
#include "solucao.h"
#include "listabu.h"

/****************************************************
Faz uma busca local determin�stica
Procura pela melhor solu��o nos vizinhos
****************************************************/
Solucao buscaLocalMelhor(Solucao inicial, Grafo g, int inter);

/****************************************************
Faz uma busca local.
Vai para a primeira solu��o melhor.
****************************************************/
Solucao buscaLocalPrimeira(Solucao inicial, Grafo g,int inter);

/****************************************************
Faz uma busca tabu.
Vai para a primeira solu��o melhor.
Utiliza uma lista de proibidos (tabu).
****************************************************/
Solucao buscaTabu(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);
Solucao buscaTabuRec(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);

#endif
