#include "../includes/steiner.h"
#include "../includes/buscas.h"
#include "time.h"

int main() {
	Graph graph;
	Solution solution;
	graph = readInput(solution);
	time_t time1 = time(NULL);
	solution.trivial(graph);
	time_t time2;
	double diff;
	cout << "Inicial - ";
	solution.printScore();
	Solution melhor, primeira, tabu;
	TabuList lstTabu;
	lstTabu.updateOptimum(solution);
	tabu = searchTabuRecursive(solution,graph,0,lstTabu);
	time2 = time(NULL);
	diff = difftime(time2,time1);
	cout << "Tempo gasto = " << diff << "segs" << endl << "Tabu - ";
	tabu.printScore();
	cout << "Otima Tabu - ";
	lstTabu.printOptimum();
	return 0;
}