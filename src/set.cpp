#include "../includes/set.h"

Set::Set() {
	edge_vector.clear();
}

void Set::add(edge_t edge) {
	edge_vector.push_back(edge);
}

void Set::remove(edge_t edge) {
	for (int i=0; i < edge_vector.size(); ++i) {
		if (((edge_vector[i].node1 == edge.node1) && (edge_vector[i].node2 == edge.node2) && (edge_vector[i].weight == edge.weight)) || ((edge_vector[i].node1 == edge.node2) && (edge_vector[i].node2 == edge.node1) && (edge_vector[i].weight == edge.weight))) {
			edge_vector.erase(edge_vector.begin() + i);
			break;
		}
	}
}

vector< edge_t > Set::getSet() {
	return edge_vector;
}

edge_t Set::getEdgeByIndex(int i) {
	return edge_vector[i];
}
