#include "../includes/buscas.h"

Solution searchBestLocal(Solution startSolution, Graph g, int iter) {
	cout << iter << "   ---   meio: " << startSolution.getEvaluation() << endl;
	if (iter < ITERATION_MAX) {
		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g);
		int posMenor = -1;
		int menor = startSolution.getEvaluation();
		for (int i=0; i < neighborhood.size(); ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < menor) {
				menor = avaliado;
				posMenor = i;
			}
		}
		if (posMenor == -1) {
			return startSolution;
		} else {
			return searchBestLocal(neighborhood[posMenor],g,iter+1);
		}
	} else {
		return startSolution;
	}
}

Solution searchFirstLocal(Solution startSolution, Graph g, int iter) {
	cout << iter << "   ---   meio: " << startSolution.getEvaluation() << endl;
	if (iter < ITERATION_MAX) {
		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g);
		int menor = startSolution.getEvaluation();
		for (int i=0; i < neighborhood.size(); ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < menor) {
				return searchFirstLocal(neighborhood[i], g, iter+1);
			}
		}
		return startSolution;
	} else {
		return startSolution;
	}
}

Solution searchTabu(Solution startSolution, Graph g, int iter, TabuList &lstTabu) {
	while (iter < BT_MAX) {
		cout << iter << "   ---   meio: " << startSolution.getEvaluation() << " optimum: " << lstTabu.getOptimum().getEvaluation() << endl;
		lstTabu.printEvaluationList();
		cout << endl;
		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g);
		cout << "neighborhood = " << neighborhood.size() << endl;
		lstTabu.addTabu(startSolution);
		int menor = startSolution.getEvaluation();
		int tamanho = neighborhood.size();
		bool achou = false;
		int indMenor = -1;
		for (int i=0; i < tamanho; ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < menor && !lstTabu.hasSolution(neighborhood[i])) {
					menor = avaliado;
					indMenor = i;
			}
		}
		if (indMenor != -1) {
			if (lstTabu.updateOptimum(neighborhood[indMenor])) {
				startSolution = neighborhood[indMenor];
				iter = 0;
				cout << "achou um melhor!" << endl;
			} else {
				startSolution = neighborhood[indMenor];
				iter++;
			}
		} else {
			cout << "nao achou!" << endl;
			indMenor = -1;
			int valorMenor = EVALUATION_MAX;
			for (int i=0; i < tamanho; ++i) {
				int avaliado = neighborhood[i].getEvaluation();
				if (avaliado < valorMenor && !lstTabu.hasSolution(neighborhood[i])) {
					if (lstTabu.updateOptimum(neighborhood[i])) {
						valorMenor = avaliado;
						indMenor = i;
						achou = true;
						startSolution = neighborhood[i];
						iter = 0;
					} else {
						valorMenor = avaliado;
						indMenor = i;
						achou = true;
						startSolution = neighborhood[i];
						iter++;
					}
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
	cout << iter << "   ---   meio: " << startSolution.getEvaluation() << " optimum: " << lstTabu.getOptimum().getEvaluation() << endl;
	lstTabu.printEvaluationList();
	cout << endl;
	if (iter < BT_MAX) {
		vector<Solution> neighborhood;
		startSolution.createNeighborhood(&neighborhood,g);
		int menor = startSolution.getEvaluation();
		int tamanho = neighborhood.size();
		for (int i=0; i < tamanho; ++i) {
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
		int indMenor = -1, valorMenor = EVALUATION_MAX;
		for (int i=0; i < tamanho; ++i) {
			int avaliado = neighborhood[i].getEvaluation();
			if (avaliado < valorMenor && !lstTabu.hasSolution(neighborhood[i])) {
				valorMenor = avaliado;
				indMenor = i;
				return searchTabuRecursive(neighborhood[i],g,iter+1,lstTabu);
			}
		}
		if (indMenor != -1) {
			return searchTabuRecursive(neighborhood[indMenor],g,iter+1,lstTabu);
		}
		return lstTabu.getOptimum();
	} else {
		return startSolution
	};
}