#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "graph.h"

#define FATOR_VIZINHOS 8

class Solution : public Graph {
	public:
		Solution(int numberOfNodes = 0);
		Solution(const Solution &solution);
		vector<int> getTerminals();
		void addTerminal(int terminal);
		int getEvaluation();
		void setEvaluation(int x);
		void print();
		void printTerminals();
		void printNodosIn();
		bool isSolution();
		void addEdge(edge_t edge);
		void removeEdge(edge_t edge);
		bool isConnected();
		bool hasTerminal();
		bool exist(edge_t edge);
		void trivial(Graph g);
		void createNeighborhood(vector<Solution> *solution_vector, Graph g);
		void printScore();
		void incTabu();
		void setTabu(int x);
		int getTabu();
		edge_t getAddedEdge();
		edge_t getRemovedEdge();
		void setActiveTabu();
		void resetActiveTabu();
		bool equalsAdded(edge_t edge);
		bool equalsRemoved(edge_t edge);
	protected:
		vector<int> terminal_vector;
	private:
		int evaluation;
		vector<int> solutionNodes_vector;
		int tabuCount;
		edge_t addedEdge;
		edge_t removedEdge;
		bool activeTabu;
};

#endif
