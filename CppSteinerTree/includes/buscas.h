#ifndef BUSCAS_H
#define BUSCAS_H

#define ITER_MAX 100

#include <iostream>
#include <string>
#include "solucao.h"
#include "listabu.h"

Solucao buscaLocalMelhor(Solucao inicial, Grafo g, int inter);
Solucao buscaLocalPrimeira(Solucao inicial, Grafo g,int inter);
Solucao buscaTabu(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);
Solucao buscaTabuRec(Solucao inicial, Grafo g, int inter, Listabu &listaTabu);

#endif