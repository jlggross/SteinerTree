#include "../includes/listabu.h"

Listabu::Listabu() {
	tabus.clear();
	otima.setAvaliacao(MAX_AVALIACAO);
}

bool Listabu::contem(Solucao s) {
	int valor = s.getAvaliacao();
	for (int i = 0; i < tabus.size(); ++i) {
		if (valor == tabus[i].getAvaliacao()) {
			return true;
		}
	}
	return false;
}

void Listabu::insereTabu(Solucao s) {
	s.setTabu(TEMPO_TABU);
	tabus.push_back(s);
	if (tabus.size() == TABU_SIZE) {
		tabus.erase(tabus.begin());
	}
}

bool Listabu::atualizaOtima(Solucao s) {
	if (s.getAvaliacao() < otima.getAvaliacao()) {
		otima = s;
		return true;
	}
	return false;
}

void Listabu::printLista() {
	cout << "Lista Tabu = ";
	for (int i = 0; i < tabus.size(); ++i) {
		cout << tabus[i].getAvaliacao() << " ";
	}
	cout << endl;
}

void Listabu::printOtima() {
	otima.printPontuacao();
}

Solucao Listabu::getOtima() {
	return otima;
}

void Listabu::turno() {
	for (int i = 0; i < tabus.size(); ++i) {
		tabus[i].incTabu();
		if (tabus[i].getTabu() > TEMPO_TABU) {
			tabus.erase(tabus.begin() + i);
		}
	}
}