#include "../includes/steiner.h"

Grafo leEntrada(Solucao &s) {
	int nodos, arestas, terminais;
	string palavra = "";
	while(palavra != "Nodes") {
		cin >> palavra;
	}
	cin >> nodos;
	Grafo graph(nodos);
	while(palavra != "Edges") {
		cin >> palavra;
	}
	cin >> arestas;
	Solucao sAux(nodos);
	for (int i = 0; i < arestas; ++i) {
		aresta_t a;
		cin >> palavra >> a.n1 >> a.n2 >> a.peso;
		graph.insereAresta(a);
	}
	while(palavra != "Terminals") {
		cin >> palavra;
	}
	palavra = "";
	while(palavra != "Terminals") {
		cin >> palavra;
	}
	cin >> terminais;
	for (int i = 0; i < terminais; ++i) {
		int t;
		cin >> palavra >> t;
		sAux.insereTerminal(t);	
	}
	s = sAux;
	while(palavra != "EOF") {
		cin >> palavra;
	}
	return graph;
}
