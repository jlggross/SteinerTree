/*********************************************************
Autores: Gabriel Portal & Jonas Hartmann

Descrição: 
Funções de busca para achar a solução do problema da
           Árvore de Steiner
**********************************************************/
#ifndef BUSCAS_H
#define BUSCAS_H

#define ITER_MAX 100

#include <iostream>
#include <string>
#include "solucao.h"
#include "listabu.h"

/****************************************************
Faz uma busca local determinística
Procura pela melhor solução nos vizinhos
****************************************************/
Solucao buscaLocalMelhor(Solucao inicial, Grafo g, int inter);

/****************************************************
Faz uma busca local.
Vai para a primeira solução melhor.
****************************************************/
Solucao buscaLocalPrimeira(Solucao inicial, Grafo g,int inter);

/****************************************************
Faz uma busca tabu.
Vai para a primeira solução melhor.
Utiliza uma lista de proibidos (tabu).
****************************************************/
Solucao buscaTabu(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);
Solucao buscaTabuRec(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);

#endif
