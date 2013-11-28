#include "../includes/grafo.h"

Grafo::Grafo(int nroNodos) {
	graph.clear();
	graph.resize(nroNodos+1);
	for (int i = 0; i < nroNodos+1; ++i) {
		graph[i].clear();
	}
	nodos = nroNodos;
	arestas = 0;
}

void Grafo::insereAresta(aresta_t a) {
	node_t n;
	n.peso = a.peso;
	n.v = a.n1;
	graph[ a.n2 ].push_back(n);
	n.v = a.n2;
	graph[ a.n1 ].push_back(n);
	++arestas;
	setArestas.insere(a);
}
		
void Grafo::removeAresta(aresta_t a) {
	bool achou = false;
	for (int i = 0; i < graph[a.n1].size(); ++i) {
		if (graph[a.n1][i].v == a.n2) {
			achou = true;
			graph[a.n1].erase(graph[a.n1].begin() + i);
			break;
		}
	}
	if (achou) {
		for (int i = 0; i < graph[a.n2].size(); ++i)
		{
		   if (graph[a.n2][i].v == a.n1)
		   {
			  graph[a.n2].erase(graph[a.n2].begin() + i);
			  break;
		   }
		}
		--arestas;
	}
	setArestas.remove(a);
}

void Grafo::print() {
	cout << "         IMPRESSAO DO GRAFO" << endl << "Numero de nodos: " << nodos << endl << "Numero de arestas: " << arestas << endl << endl << "--- ARESTAS ---" << endl;
	for (int i = 1; i < nodos+1; ++i) {
		cout << i << " : " ;
		for (int j = 0; j < graph[i].size(); j++) {
			cout << "[" << graph[i][j].v << " " << graph[i][j].peso << "]" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector< vector<node_t> > Grafo::getGraph() {
	return graph;
}

bool Grafo::temCiclo(int nodo) {
	visitado[ nodo ] = true;
	for (int i = 0; i < graph[nodo].size(); ++i) {
		if (!graph[nodo][i].acessado) {
			graph[nodo][i].acessado = true;
			for (int j = 0; j < graph[ graph[nodo][i].v ].size(); j++) {
				if (graph[ graph[nodo][i].v ][j].v == nodo) {
					graph[ graph[nodo][i].v ][j].acessado = true;
					break;
				}
			}
			if (visitado[ graph[nodo][i].v ]) {
				return true;
			} else if (temCiclo(graph[nodo][i].v)) {
				return true;
			}
		}
	}
	return false;
}

aresta_t Grafo::random(int seed) {
	return setArestas.aleatoria(seed);
}

bool Grafo::ciclo(int nodo) {
	visitado.clear();
	visitado.resize(nodos+1);
	for (int i = 0; i < visitado.size(); ++i) {
		visitado[i] = false;
	}
	for (int i = 0; i < graph.size(); ++i) {
		for (int j = 0; j < graph[i].size(); j++) {
			graph[i][j].acessado = false;
		}
	}
	return temCiclo(nodo);
}

Set Grafo::getArestas() {
	return setArestas;
}