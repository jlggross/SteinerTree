#include "../includes/graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph::Graph(int nodesCount) {
	graph.clear();
	graph.resize(nodesCount+1);
	for (int i=0; i < nodesCount+1; ++i) {
		graph[i].clear();
	}
	numberOfNodes = nodesCount;
	edgeCount = 0;
}

void Graph::addEdge(edge_t edge) {
	node_t newNode;
	newNode.weight = edge.weight;
	newNode.vertex = edge.node1;
	graph[ edge.node2 ].push_back(newNode);
	newNode.vertex = edge.node2;
	graph[ edge.node1 ].push_back(newNode);
	++edgeCount;
	edgeSet.add(edge);
}
		
void Graph::removeEdge(edge_t edge) {
	bool achou = false;
	for (int i=0; i < graph[edge.node1].size(); ++i) {
		if (graph[edge.node1][i].vertex == edge.node2) {
			achou = true;
			graph[edge.node1].erase(graph[edge.node1].begin() + i);
			break;
		}
	}
	if (achou) {
		for (int i=0; i < graph[edge.node2].size(); ++i)
		{
		   if (graph[edge.node2][i].vertex == edge.node1)
		   {
			  graph[edge.node2].erase(graph[edge.node2].begin() + i);
			  break;
		   }
		}
		--edgeCount;
	}
	edgeSet.remove(edge);
}

void Graph::print() {
	cout << "         IMPRESSAO DO GRAFO" << endl << "Numero de nodos: " << numberOfNodes << endl << "Numero de arestas: " << edgeCount << endl << endl << "--- ARESTAS ---" << endl;
	for (int i = 1; i < numberOfNodes+1; ++i) {
		cout << i << " : " ;
		for (int j = 0; j < graph[i].size(); j++) {
			cout << "[" << graph[i][j].vertex << " " << graph[i][j].weight << "]" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector< vector<node_t> > Graph::getGraph() {
	return graph;
}

/*
 * Check if there is a loop 
 */
bool Graph::hasLoop(int nodo) {
	int a;
	wasAccessed_vector[ nodo ] = true;
	//cout << "hasLoop: nodo=" << nodo << endl;
	for (int i=0; i < graph[nodo].size(); ++i) {
		if (!graph[nodo][i].wasAccessed) {
			graph[nodo][i].wasAccessed = true;
			for (int j = 0; j < graph[ graph[nodo][i].vertex ].size(); j++) {
				//cout << "hasLoop: i=" << i << ", j=" << j << ", nodo=" << nodo << ", [nodo][i].vertex=" << graph[nodo][i].vertex << endl;
				if (graph[ graph[nodo][i].vertex ][j].vertex == nodo) {
					graph[ graph[nodo][i].vertex ][j].wasAccessed = true;
					break;
				}
			}
			if (wasAccessed_vector[ graph[nodo][i].vertex ]) {
				return true;
			} else if (hasLoop(graph[nodo][i].vertex)) {
				return true;
			}
		}
	}
	return false;
}

/*
 * Initialization for hasLoop function.
 */
bool Graph::loop(int nodo) {
	wasAccessed_vector.clear();
	wasAccessed_vector.resize(numberOfNodes+1);

	/* All nodes from the accessed list of nodes are set as not accesed */
	for (int i=0; i < wasAccessed_vector.size(); ++i) {
		wasAccessed_vector[i] = false;
	}
	
	/* All nodes from the adjacency list are set as not accessed */	
	for (int i=0; i < graph.size(); ++i) {
		for (int j = 0; j < graph[i].size(); j++) {
			graph[i][j].wasAccessed = false;
		}
	}

	return hasLoop(nodo);
}

edge_t Graph::getRandomEdge() {
	int random = rand() % (edgeSet.getSet().size() - 1);
	return edgeSet.getEdgeByIndex(random);
}


Set Graph::getEdges() {
	return edgeSet;
}







