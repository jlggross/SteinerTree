#ifndef LISTA_TABU_H
#define LISTA_TABU_H

#define BT_MAX 40
#define TABU_SIZE 10
#define TABU_TIME 15

#define EVALUATION_MAX 999999999

#include "solucao.h"

class TabuList {
	public:
		TabuList();
		bool hasSolution(Solution s);
		void addTabu(Solution s);
		bool updateOptimum(Solution s);
		void printOptimum();
		void printEvaluationList();
		Solucao getOptimum();
		void round();
	protected:
		vector<Solution> tabus;
		Solution optimum;
};

#endif