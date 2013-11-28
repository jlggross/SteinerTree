#include "../includes/steiner.h"

Graph readInput(Solution &solution) {
	int numberOfNodes, edgeCount, terminais;
	string word = "";
	while(word != "Nodes") {
		cin >> word;
	}
	cin >> numberOfNodes;
	Graph graph(numberOfNodes);
	while(word != "Edges") {
		cin >> word;
	}
	cin >> edgeCount;
	for (int i=0; i < edgeCount; ++i) {
		edge_t edge;
		cin >> word >> edge.node1 >> edge.node2 >> edge.weight;
		graph.addEdge(edge);
	}

	Solution sAux(numberOfNodes);
	while(word != "Terminals") {
		cin >> word;
	}
	word = "";
	while(word != "Terminals") {
		cin >> word;
	}
	cin >> terminais;
	for (int i=0; i < terminais; ++i) {
		int terminal;
		cin >> word >> terminal;
		sAux.addTerminal(terminal);	
	}
	solution = sAux;
	while(word != "EOF") {
		cin >> word;
	}
	return graph;
}
