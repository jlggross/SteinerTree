#include "../includes/search.h"

Solution searchTabu(Solution startSolution, Graph g, int iter, TabuList &lstTabu) {
	while (iter < BT_MAX) {
		cout << iter << " -- startSolution: " << startSolution.getEvaluation() << " optimum: " << lstTabu.getOptimum().getEvaluation() << endl;
		lstTabu.printEvaluationList();
		cout << endl;

		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g);
		cout << "neighborhood = " << neighborhood.size() << endl;
		lstTabu.addTabu(startSolution);
		
		int menor = startSolution.getEvaluation();
		int neighborhoodSize = neighborhood.size();
		bool achou = false;
		int indexMenor = -1;

		
		for (int i = 0; i < neighborhoodSize; ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < menor && !lstTabu.hasSolution(neighborhood[i])) {
				menor = avaliado;
				indexMenor = i;
			}
		}

		if (indexMenor != -1) {
			startSolution = neighborhood[indexMenor];
			if (lstTabu.updateOptimum(neighborhood[indexMenor])) {
				cout << "achou uma solução melhor!" << endl;				
				iter = 0;
			} else {
				iter++;
			}
		} else {
			cout << "nao achou!" << endl;
			int valorMenor = EVALUATION_MAX;
			for (int i = 0; i < neighborhoodSize; ++i) {
				int avaliado = neighborhood[i].getEvaluation();
				if (avaliado < valorMenor && !lstTabu.hasSolution(neighborhood[i])) {
					valorMenor = avaliado;
					achou = true;
					startSolution = neighborhood[i];					
					if (lstTabu.updateOptimum(neighborhood[i])) {
						iter = 0;
					} else {
						iter++;
					}
					break;
				}
			}
			if (!achou) {
				startSolution = lstTabu.getOptimum();
				iter++;
			}
		}
	}
	return lstTabu.getOptimum();
}

Solution searchTabuRecursive(Solution startSolution, Graph g, int iter, TabuList &lstTabu) {
	cout << iter << " -- startSolution: " << startSolution.getEvaluation() << " optimum: " << lstTabu.getOptimum().getEvaluation() << endl;
	lstTabu.printEvaluationList();
	cout << endl;
	if (iter < BT_MAX) {
		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g); //creates a vector of solutions based on the startSolution
		
		int menor = startSolution.getEvaluation();
		int neighborhoodSize = neighborhood.size();
		for (int i=0; i < neighborhoodSize; ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < menor && !lstTabu.hasSolution(neighborhood[i])) {
				if (lstTabu.updateOptimum(neighborhood[i])) {
					lstTabu.addTabu(neighborhood[i]);
					return searchTabuRecursive(neighborhood[i], g, 0, lstTabu);
				} else {
					lstTabu.addTabu(neighborhood[i]);
					return searchTabuRecursive(neighborhood[i], g, iter+1, lstTabu);
				}
			}
		}
		
		int valorMenor = EVALUATION_MAX;
		for (int i=0; i < neighborhoodSize; ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < valorMenor && !lstTabu.hasSolution(neighborhood[i])) {
				valorMenor = avaliado;
				return searchTabuRecursive(neighborhood[i],g,iter+1,lstTabu);
			}
		}
		return lstTabu.getOptimum();
	} else {
		return startSolution;
	}
}
