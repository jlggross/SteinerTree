#ifndef GRAFO_H
#define GRAFO_H

#include "set.h"

typedef struct{
	int vertex;
	int weight;
	bool wasAccessed;
} node_t;

class Graph {
	public:
		Graph(int numberOfNodes = 0);
		void addEdge(edge_t edge);
		void removeEdge(edge_t edge);
		void print();
		vector< vector<node_t> > getGraph();
		bool loop(int nodo);
		bool hasLoop(int nodo);
		edge_t randomEdge(int seed);
		Set getEdges();
	protected:
		vector< vector<node_t> > graph;
		int edgeCount;
		int numberOfNodes;
		vector<bool> wasAccessed_vector;
		Set edgeSet;
};

#endif