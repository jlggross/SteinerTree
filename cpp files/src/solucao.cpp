#include "../includes/solucao.h"

Solucao::Solucao(int nodos)
   : Grafo(nodos)
{
	avaliacao = 0;
	terminals.clear();
}

Solucao::Solucao(const Solucao &s)
{
	arestas = s.arestas;
	nodos = s.nodos;
	graph = s.graph;
	setArestas = s.setArestas;
	terminals = s.terminals;
	avaliacao = s.avaliacao;		
	nodosIn = s.nodosIn;
}
void Solucao::insereTerminal(int t)
{
	terminals.push_back(t);
}
	
vector< int > Solucao::getTerminals()
{
	return terminals;
}


int Solucao::getAvaliacao()
{
	return avaliacao;
}

void Solucao::setAvaliacao(int x)
{
	avaliacao = x;
}

void Solucao::printTerminais()
{
	cout << "Terminais: ";
	for (int i = 0; i < terminals.size(); ++i)
		cout << terminals[i] << " ";	
	cout << endl << endl;
}

void Solucao::printNodosIn()
{
	cout << "Nodos Incluidos na Solucao: " << endl;
	for (int i = 0; i < nodosIn.size(); ++i)	
		cout << nodosIn[i] << " ";	
	cout << endl << endl;
}

void Solucao::print()
{
	cout << "******************************************" << endl;
	cout << "---------/ SOLUCAO /--------" << endl;
	Grafo::print();
	if (terminals.size() > 0)
		printTerminais();
	if (nodosIn.size() > 0)
		printNodosIn();
	cout << "Avaliacao = " << avaliacao << endl;
	if (ehSolucao())
		cout << "Solucao Valida." << endl;
	else cout << "Solucao Invalida!" << endl;
	cout << "******************************************" << endl << endl;
}

void Solucao::insereAresta( aresta_t a )
{
	node_t n;
	n.peso = a.peso;	
	n.v = a.n1;

	// Verifica se a aresta já não foi incluída no grafo.
	bool achou0 = false;
	for (int i = 0; i < graph[ a.n2 ].size() && !achou0; i++)
	{
		if ( graph[ a.n2 ][i].v == n.v )
		{
		    achou0 = true;
		    break;
        }
	}	
	
	if (!achou0)
	{
		graph[ a.n2 ].push_back( n );
		n.v = a.n2;
		graph[ a.n1 ].push_back( n );
		++arestas;
		setArestas.insere(a);
		avaliacao += a.peso;	// Se a aresta é inserida na solucao, então soma ela ao peso total
	}
	
	bool achou1 = false, achou2 = false;
	for (int i = 0; i < nodosIn.size() && !(achou1 && achou2); i++)
	{
		if ( nodosIn[i] == a.n1 )
		    achou1 = true;
		else if ( nodosIn[i] == a.n2 )
		    achou2 = true;
	}

	if ( !achou1 )
		nodosIn.push_back( a.n1 );
	if ( !achou2 )
		nodosIn.push_back( a.n2 );
}
		
void Solucao::removeAresta( aresta_t a )
{
	bool achou = false;
    
	for (int i = 0; i < graph[a.n1].size(); i++)
	{
		if ( graph[a.n1][i].v == a.n2 )
		{
			avaliacao -= graph[a.n1][i].peso;	// Se a aresta é retirada da solucao, então diminiu ela do peso total.			
			achou = true;
			graph[a.n1].erase( graph[a.n1].begin() + i );
			setArestas.remove(a);
			break;
		}
	}

	if (achou)
	{
		for (int i = 0; i < graph[a.n2].size(); i++)
		{
			if ( graph[a.n2][i].v == a.n1 )
			{
				graph[a.n2].erase( graph[a.n2].begin() + i );
				break;
			}
		}

		--arestas;
	}

	if (graph[a.n1].empty())
	{
		for (int i = 0; i < nodosIn.size(); i++)
		{
			if ( nodosIn[i] == a.n1 )
			{
				nodosIn.erase( nodosIn.begin() + i );
				break;
			}
		}
	}
	    
	if (graph[a.n2].empty())
	{
		for (int i = 0; i < nodosIn.size(); i++)
		{
			if ( nodosIn[i] == a.n2 )
			{
				nodosIn.erase( nodosIn.begin() + i );
				break;
			}
		}
	}
}

bool Solucao::ehSolucao()
{    
	//if ( !temCiclo( nodosIn[0] ) )           /* Se não tem ciclos */
	//    cout << "sem ciclos!!" << endl;
	
	if (nodosIn.size() > 0)
	{	
		/*
		cout << "temCiclos: ";
		if (ciclo( nodosIn[0] )) cout << "SIM"<< endl;
		else cout << "NAO"<< endl;
		
		cout << "ehConexo: ";
		if (ehConexo()) cout << "SIM"<< endl;
		else cout << "NAO" << endl;
		
		cout << "temTerminais: ";
		if (temTerminais()) cout << "SIM"<< endl;
		else cout << "NAO" << endl;
		
		cout << "Avaliacao: " << avaliacao << endl;
		
		cout << endl;
		*/
		if (temTerminais() && !ciclo( nodosIn[0] ) && ehConexo() )
		return true;

	}
	//else cout << "Solucao vazia!!!" << endl;

	return false;
}

bool Solucao::ehConexo()
{
	for ( int i = 0; i < nodosIn.size(); i++ )
	{
		if ( !visitado[ nodosIn[i] ] )
			return false;
	}

	return true;
}

bool Solucao::temTerminais()
{
	
	bool todos = true;
	for (int i = 0; i < terminals.size(); i++)
	{
		bool achou = false;
		for (int j = 0; j < nodosIn.size(); j++)
		{
			if ( terminals[i] == nodosIn[j] )
			{
				achou = true;
				break;
			}
		}

		if ( !achou )
		{
			todos = false;
			break;
		}
	}
	
	return todos;
	
}

bool Solucao::existe(aresta_t a)
{
	vector< aresta_t > arestas = setArestas.getConjunto();
	for (int i = 0; i < arestas.size(); i++)
	{
		if (((a.n1 == arestas[i].n1) && (a.n2 == arestas[i].n2) && (a.peso == arestas[i].peso)) ||
		   ((a.n1 == arestas[i].n2) && (a.n2 == arestas[i].n1) && (a.peso == arestas[i].peso)))
					return true;
	}
	return false;
}

void Solucao::trivial( Grafo g )
{
     vector< aresta_t > arestas = g.getArestas().getConjunto();
     int i = 0;
     
     while ( !ehSolucao() )
     {
         insereAresta( arestas[i] );
         
         if ( ciclo( arestas[i].n1 ) )
         {
             removeAresta( arestas[i] );
         }
                  
         ++i;
     }
}

/* Um vizinho pode ser criado com uma inserção, remoção ou troca de uma aresta */
void Solucao::criaVizinhos(vector<Solucao> *v, Grafo g)
{
	vector<Solucao> vaux;
	vaux.clear();
		
	vector< aresta_t > arestas = g.getArestas().getConjunto();
	
	for (int i = 0; i < arestas.size(); i++){
		aresta_t a = arestas[i];
		Solucao viz(*this);
		
		// Se a aresta está na solução atual(this), remove ela
		if (viz.existe(a)){
			viz.removeAresta(a);
			
			if (viz.ehSolucao()) // Só adiciona o novo vizinho se ele for uma solução válida
				vaux.push_back(viz);
            
		    /**** começa a parte de trocas ****/
			
		    for ( int j = 0; j < arestas.size(); ++j )
		    {
			if ( i == j )
			    continue;
			    
			aresta_t b = arestas[j];
			if ( !viz.existe( b ) )
			{
			   viz.insereAresta(b);
			   
			   if (viz.ehSolucao()) // Só adiciona o novo vizinho se ele for uma solução válida
					       vaux.push_back(viz);
					       
			   viz.removeAresta( b );
			}
		    }	
			
		    /**** termina a parte de trocas ****/
		}/*
		else // Se a aresta não está na solução atual, insere ela
		{
			viz.insereAresta(a);
			if (viz.ehSolucao()) // Só adiciona o novo vizinho se ele for uma solução válida
				vaux.push_back(viz); // adiciona o novo grafo no vetor de vizinhos
		}*/				
	}
	(*v) = vaux;
}

void Solucao::printPontuacao()
{
    cout << "Avaliacao = " << avaliacao << endl << endl;
}

void Solucao::incTabu()
{
    ++contTabu;
}

void Solucao::setTabu(int x)
{
    contTabu = x;
}

int Solucao::getTabu()
{
    return contTabu;
}

aresta_t Solucao::getInserida()
{
	//return inserida;
}

aresta_t Solucao::getRemovida()
{
	//return removida;
}
