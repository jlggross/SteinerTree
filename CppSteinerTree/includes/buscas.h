#ifndef BUSCAS_H
#define BUSCAS_H

#define ITERATION_MAX 100

#include <iostream>
#include <string>
#include "solucao.h"
#include "listabu.h"

Solution searchBestLocal(Solution startSolution, Graph g, int inter);
Solution searchFirstLocal(Solution startSolution, Graph g, int inter);
Solution searchTabu(Solution startSolution, Graph g, int inter, TabuList &lstTabu);
Solution searchTabuRecursive(Solution startSolution, Graph g, int inter, TabuList &lstTabu);

#endif