#include "../includes/tabulist.h"

TabuList::TabuList() {
	tabus.clear();
	optimum.setEvaluation(EVALUATION_MAX);
}

bool TabuList::hasSolution(Solution solution) {
	int valor = solution.getEvaluation();
	for (int i=0; i < tabus.size(); ++i) {
		if (valor == tabus[i].getEvaluation()) {
			return true;
		}
	}
	return false;
}

void TabuList::addTabu(Solution solution) {
	solution.setTabu(TABU_TIME);
	tabus.push_back(solution);
	if (tabus.size() == TABU_SIZE) {
		tabus.erase(tabus.begin());
	}
}

bool TabuList::updateOptimum(Solution solution) {
	if (solution.getEvaluation() < optimum.getEvaluation()) {
		optimum = solution;
		return true;
	}
	return false;
}

void TabuList::printEvaluationList() {
	cout << "Lista Tabu = ";
	for (int i=0; i < tabus.size(); ++i) {
		cout << tabus[i].getEvaluation() << " ";
	}
	cout << endl;
}

void TabuList::printOptimum() {
	optimum.printScore();
}

Solution TabuList::getOptimum() {
	return optimum;
}

void TabuList::round() {
	for (int i=0; i < tabus.size(); ++i) {
		tabus[i].incTabu();
		if (tabus[i].getTabu() > TABU_TIME) {
			tabus.erase(tabus.begin() + i);
		}
	}
}
