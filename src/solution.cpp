#include "../includes/solution.h"

Solution::Solution(int numberOfNodes) : Graph(numberOfNodes) {
	evaluation = 0;
	terminal_vector.clear();
}

Solution::Solution(const Solution &solution) {
	edgeCount = solution.edgeCount;
	numberOfNodes = solution.numberOfNodes;
	graph = solution.graph;
	edgeSet = solution.edgeSet;
	terminal_vector = solution.terminal_vector;
	evaluation = solution.evaluation;
	solutionNodes_vector = solution.solutionNodes_vector;
}

void Solution::addTerminal(int terminal) {
	terminal_vector.push_back(terminal);
}

vector<int> Solution::getTerminals() {
	return terminal_vector;
}

int Solution::getEvaluation() {
	return evaluation;
}

void Solution::setEvaluation(int x) {
	evaluation = x;
}

void Solution::printTerminals() {
	cout << "Terminais: ";
	for (int i=0; i < terminal_vector.size(); ++i) {
		cout << terminal_vector[i] << " ";
	}
	cout << endl << endl;
}

void Solution::printNodosIn() {
	cout << "Nodos Incluidos na Solution: " << endl;
	for (int i=0; i < solutionNodes_vector.size(); ++i) {
		cout << solutionNodes_vector[i] << " ";
	}
	cout << endl << endl;
}

void Solution::print() {
	cout << "******************************************" << endl << "---------/ Solution /--------" << endl;
	Graph::print();
	if (terminal_vector.size() > 0) {
		printTerminals();
	}
	if (solutionNodes_vector.size() > 0) {
		printNodosIn();
	}
	cout << "Avaliacao = " << evaluation << endl;
	if (isSolution()) {
		cout << "Solution Valida." << endl;
	} else {
		cout << "Solution Invalida!" << endl;
	}
	cout << "******************************************" << endl << endl;
}

void Solution::addEdge(edge_t edge) {
	node_t newNode;
	newNode.weight = edge.weight;
	newNode.vertex = edge.node1;
	bool achou0 = false;
	for (int i=0; i < graph[ edge.node2 ].size() && !achou0; ++i) {
		if (graph[ edge.node2 ][i].vertex == newNode.vertex) {
			achou0 = true;
			break;
		}
	}
	if (!achou0) {
		graph[ edge.node2 ].push_back(newNode);
		newNode.vertex = edge.node2;
		graph[ edge.node1 ].push_back(newNode);
		++edgeCount;
		edgeSet.add(edge);
		evaluation += edge.weight;
		//cout << "added edge " << edge.node1 << " " << edge.node2 << " " << edge.weight << endl;
		//cout << "evaluation=" << evaluation << endl;
	}
	bool achou1 = false, achou2 = false;
	for (int i=0; i < solutionNodes_vector.size() && !(achou1 && achou2); ++i) {
		if (solutionNodes_vector[i] == edge.node1) {
			achou1 = true;
		} else if (solutionNodes_vector[i] == edge.node2) {
			achou2 = true;
		}
	}
	if (!achou1) {
		solutionNodes_vector.push_back(edge.node1);
	}
	if (!achou2) {
		solutionNodes_vector.push_back(edge.node2);
	}
}

void Solution::removeEdge(edge_t edge) {
	bool achou = false;
	for (int i=0; i < graph[edge.node1].size(); ++i) {
		if (graph[edge.node1][i].vertex == edge.node2) {
			evaluation -= graph[edge.node1][i].weight;
			//cout << "removed edge " << edge.node1 << " " << edge.node2 << " " << edge.weight << endl;
			//cout << "evaluation=" << evaluation << endl;
			achou = true;
			graph[edge.node1].erase(graph[edge.node1].begin() + i);
			edgeSet.remove(edge);
			break;
		}
	}
	if (achou) {
		for (int i=0; i < graph[edge.node2].size(); ++i) {
			if (graph[edge.node2][i].vertex == edge.node1) {
				graph[edge.node2].erase(graph[edge.node2].begin() + i);
				break;
			}
		}
		--edgeCount;
	}
	if (graph[edge.node1].empty()) {
		for (int i=0; i < solutionNodes_vector.size(); ++i) {
			if (solutionNodes_vector[i] == edge.node1) {
				solutionNodes_vector.erase(solutionNodes_vector.begin() + i);
				break;
			}
		}
	}
	if (graph[edge.node2].empty()) {
		for (int i=0; i < solutionNodes_vector.size(); ++i) {
			if (solutionNodes_vector[i] == edge.node2) {
				solutionNodes_vector.erase(solutionNodes_vector.begin() + i);
				break;
			}
		}
	}
}

/*
 * Checks if there is a solution. 
 */
bool Solution::isSolution() {
	if (solutionNodes_vector.size() > 0) {
		//cout << "isSolution: solutionNodes_vector[0] = " << solutionNodes_vector[0] << endl;
		if (hasTerminal() && !loop(solutionNodes_vector[0]) && isConnected()) {
			return true;
		}
	}
	return false;
}


/*
 * Checks if all the nodes in the graph are connected
 */
bool Solution::isConnected() {
	for (int i=0; i < solutionNodes_vector.size(); ++i) {
		if (!wasAccessed_vector[ solutionNodes_vector[i] ]) {
			return false;
		}
	}
	return true;
}


/*
 * Checks if all the terminals are in the solution vector.
 * If they are, the function returns true, otherwise it returns false.
 */
bool Solution::hasTerminal() {
	bool todos = true;
	for (int i=0; i < terminal_vector.size(); ++i) {
		bool achou = false;
		for (int j = 0; j < solutionNodes_vector.size(); j++) {
			if (terminal_vector[i] == solutionNodes_vector[j]) {
				achou = true;
				break;
			}
		}
		if (!achou) {
			todos = false;
			break;
		}
	}
	return todos;
}

/*
 * First of all the edge vector is extracted from the graph to b manipulated.
 * Secondly, the function looks for a trivial solution.
 */
void Solution::trivial(Graph g) {
	cout << "trivial" << endl;
	vector< edge_t > edge_vector = g.getEdges().getSet();
	int i=0;
	while (!isSolution()) {
		addEdge(edge_vector[i]);
		if (loop(edge_vector[i].node1)) {
			removeEdge(edge_vector[i]);
		}
		++i;
	}

	printNodosIn();
}

/*
 * Checks if an edge is in the edge vector. 
 * Returns true if it is or false otherwise.
 */
bool Solution::exist(edge_t edge) {
	vector< edge_t > edge_vector = edgeSet.getSet();
	for (int i=0; i < edge_vector.size(); ++i) {
		if (((edge.node1 == edge_vector[i].node1) && (edge.node2 == edge_vector[i].node2) && (edge.weight == edge_vector[i].weight)) || ((edge.node1 == edge_vector[i].node2) && (edge.node2 == edge_vector[i].node1) && (edge.weight == edge_vector[i].weight))) {
			return true;
		}
	}
	return false;
}

/*
 * Finds a vector os solutions based on the "this" solution.
 */
void Solution::createNeighborhood(vector<Solution> *solution_vector, Graph g) {
	vector<Solution> vaux;
	vaux.clear();
	vector< edge_t > edgeCount = g.getEdges().getSet();
	
	int edgeCountSize = edgeCount.size();
	int size = edgeCountSize / FATOR_VIZINHOS;
	for (int i=0; i < size; ++i) {
		int index = rand() % (edgeCountSize - 1);
		edge_t edge = edgeCount[index];
		Solution viz(*this);
		if (viz.exist(edge)) {
			viz.removeEdge(edge);
			if (viz.isSolution()) {
				vaux.push_back(viz);
			}
			for (int j = 0; j < size; ++j) {
				int index2 = rand() % (edgeCountSize - 1);
				if (index == index2) {
					continue;
				}
				edge_t b = edgeCount[index2];
				if (!viz.exist(b)) {
					viz.addEdge(b);
					if (viz.isSolution()) {
						vaux.push_back(viz);
					}
					viz.removeEdge(b);
				}
			}
		}
	}
	(*solution_vector) = vaux;
}

void Solution::printScore() {
	cout << "Avaliacao = " << evaluation << endl << endl;
}

void Solution::incTabu() {
	++tabuCount;
}

void Solution::setTabu(int x) {
	tabuCount = x;
}

int Solution::getTabu() {
	return tabuCount;
}

edge_t Solution::getAddedEdge() {
	
}

edge_t Solution::getRemovedEdge() {
	
}
