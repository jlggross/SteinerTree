#ifndef SET_H
#define SET_H

#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct{
	int node1, node2;
	int weight;
} edge_t;

class Set {
	public:
		Set();
		void add(edge_t edge);
		void remove(edge_t edge);
		vector< edge_t > getSet();
		edge_t getEdgeByIndex(int i);
	protected:
		vector< edge_t > edge_vector;
};

#endif
