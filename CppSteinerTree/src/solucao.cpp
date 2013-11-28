#include "../includes/solucao.h"

Solucao::Solucao(int nodos) : Grafo(nodos) {
	avaliacao = 0;
	terminals.clear();
}

Solucao::Solucao(const Solucao &s) {
	arestas = s.arestas;
	nodos = s.nodos;
	graph = s.graph;
	setArestas = s.setArestas;
	terminals = s.terminals;
	avaliacao = s.avaliacao;
	nodosIn = s.nodosIn;
}

void Solucao::insereTerminal(int t) {
	terminals.push_back(t);
}

vector< int > Solucao::getTerminals() {
	return terminals;
}

int Solucao::getAvaliacao() {
	return avaliacao;
}

void Solucao::setAvaliacao(int x) {
	avaliacao = x;
}

void Solucao::printTerminais() {
	cout << "Terminais: ";
	for (int i = 0; i < terminals.size(); ++i) {
		cout << terminals[i] << " ";
	}
	cout << endl << endl;
}

void Solucao::printNodosIn() {
	cout << "Nodos Incluidos na Solucao: " << endl;
	for (int i = 0; i < nodosIn.size(); ++i) {
		cout << nodosIn[i] << " ";
	}
	cout << endl << endl;
}

void Solucao::print() {
	cout << "******************************************" << endl << "---------/ SOLUCAO /--------" << endl;
	Grafo::print();
	if (terminals.size() > 0) {
		printTerminais();
	}
	if (nodosIn.size() > 0) {
		printNodosIn();
	}
	cout << "Avaliacao = " << avaliacao << endl;
	if (ehSolucao()) {
		cout << "Solucao Valida." << endl;
	} else {
		cout << "Solucao Invalida!" << endl;
	}
	cout << "******************************************" << endl << endl;
}

void Solucao::insereAresta(aresta_t a) {
	node_t n;
	n.peso = a.peso;
	n.v = a.n1;
	bool achou0 = false;
	for (int i = 0; i < graph[ a.n2 ].size() && !achou0; ++i) {
		if (graph[ a.n2 ][i].v == n.v) {
			achou0 = true;
			break;
		}
	}
	if (!achou0) {
		graph[ a.n2 ].push_back(n);
		n.v = a.n2;
		graph[ a.n1 ].push_back(n);
		++arestas;
		setArestas.insere(a);
		avaliacao += a.peso;
	}
	bool achou1 = false, achou2 = false;
	for (int i = 0; i < nodosIn.size() && !(achou1 && achou2); ++i) {
		if (nodosIn[i] == a.n1) {
			achou1 = true;
		} else if (nodosIn[i] == a.n2) {
			achou2 = true;
		}
	}
	if (!achou1) {
		nodosIn.push_back(a.n1);
	}
	if (!achou2) {
		nodosIn.push_back(a.n2);
	}
}

void Solucao::removeAresta(aresta_t a) {
	bool achou = false;
	for (int i = 0; i < graph[a.n1].size(); ++i) {
		if (graph[a.n1][i].v == a.n2) {
			avaliacao -= graph[a.n1][i].peso;
			achou = true;
			graph[a.n1].erase(graph[a.n1].begin() + i);
			setArestas.remove(a);
			break;
		}
	}
	if (achou) {
		for (int i = 0; i < graph[a.n2].size(); ++i) {
			if (graph[a.n2][i].v == a.n1) {
				graph[a.n2].erase(graph[a.n2].begin() + i);
				break;
			}
		}
		--arestas;
	}
	if (graph[a.n1].empty()) {
		for (int i = 0; i < nodosIn.size(); ++i) {
			if (nodosIn[i] == a.n1) {
				nodosIn.erase(nodosIn.begin() + i);
				break;
			}
		}
	}
	if (graph[a.n2].empty()) {
		for (int i = 0; i < nodosIn.size(); ++i) {
			if (nodosIn[i] == a.n2) {
				nodosIn.erase(nodosIn.begin() + i);
				break;
			}
		}
	}
}

bool Solucao::ehSolucao() {
	if (nodosIn.size() > 0) {
		if (temTerminais() && !ciclo(nodosIn[0]) && ehConexo()) {
			return true;
		}
	}
	return false;
}

bool Solucao::ehConexo() {
	for (int i = 0; i < nodosIn.size(); ++i) {
		if (!visitado[ nodosIn[i] ]) {
			return false;
		}
	}
	return true;
}

bool Solucao::temTerminais() {
	bool todos = true;
	for (int i = 0; i < terminals.size(); ++i) {
		bool achou = false;
		for (int j = 0; j < nodosIn.size(); j++) {
			if (terminals[i] == nodosIn[j]) {
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

bool Solucao::existe(aresta_t a) {
	vector< aresta_t > arestas = setArestas.getConjunto();
	for (int i = 0; i < arestas.size(); ++i) {
		if (((a.n1 == arestas[i].n1) && (a.n2 == arestas[i].n2) && (a.peso == arestas[i].peso)) || ((a.n1 == arestas[i].n2) && (a.n2 == arestas[i].n1) && (a.peso == arestas[i].peso))) {
			return true;
		}
	}
	return false;
}

void Solucao::trivial(Grafo g) {
	vector< aresta_t > arestas = g.getArestas().getConjunto();
	int i = 0;
	while (!ehSolucao()) {
		insereAresta(arestas[i]);
		if (ciclo(arestas[i].n1)) {
			removeAresta(arestas[i]);
		}
		++i;
	}
}

void Solucao::criaVizinhos(vector<Solucao> *v, Grafo g) {
	vector<Solucao> vaux;
	vaux.clear();
	vector< aresta_t > arestas = g.getArestas().getConjunto();
	for (int i = 0; i < arestas.size(); ++i) {
		aresta_t a = arestas[i];
		Solucao viz(*this);
		if (viz.existe(a)) {
			viz.removeAresta(a);
			if (viz.ehSolucao()) {
				vaux.push_back(viz);
			}
			for (int j = 0; j < arestas.size(); ++j) {
				if (i == j) {
					continue;
				}
				aresta_t b = arestas[j];
				if (!viz.existe(b)) {
					viz.insereAresta(b);
					if (viz.ehSolucao()) {
						vaux.push_back(viz);
					}
					viz.removeAresta(b);
				}
			}
		}
	}
	(*v) = vaux;
}

void Solucao::printPontuacao() {
	cout << "Avaliacao = " << avaliacao << endl << endl;
}

void Solucao::incTabu() {
	++contTabu;
}

void Solucao::setTabu(int x) {
	contTabu = x;
}

int Solucao::getTabu() {
	return contTabu;
}

aresta_t Solucao::getInserida() {
	
}

aresta_t Solucao::getRemovida() {
	
}
