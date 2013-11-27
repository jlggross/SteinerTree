#include "../includes/steiner.h"

/****************************************************
le Entrada
Le todos os dados de entrada
****************************************************/
Grafo leEntrada(Solucao &s)
{
    int nodos, arestas, terminais;
    
    /* string auxiliar para ler a entrada */
    string palavra = "";
    
    /* pula tudo, até os nodos */
    while( palavra != "Nodes" )
        cin >> palavra;
    cin >> nodos;
    
    /********************
     alocação do grafo 
     *******************/   
    Grafo graph(nodos);    
//Solucao sAux(nodos);       /* Esta linha está aqui só para testes!!! */
	
    /* até as arestas */
    while( palavra != "Edges" )
	    cin >> palavra;
    cin >> arestas;
    
    Solucao sAux(nodos);
    for (int i = 0; i < arestas; i++)
    {
	aresta_t a;
	cin >> palavra >> a.n1 >> a.n2 >> a.peso;
	    
        graph.insereAresta( a );
        //sAux.insereAresta( a );  /* Esta linha está aqui só para testes!!! */
    }
    
    /* até os terminais: primeira aparição */
    while( palavra != "Terminals" )
        cin >> palavra;
    palavra = "";
    
    /* segunda aparição */
    while( palavra != "Terminals" )
        cin >> palavra;
    cin >> terminais;


    //Solucao sAux(nodos);
    for (int i = 0; i < terminais; i++)
    {
        int t;
        cin >> palavra >> t;
	    sAux.insereTerminal(t);	
    }
    
    s = sAux;

    /* vai até o fim do arquivo: não serve para nada */
    while( palavra != "EOF" )
        cin >> palavra;

    return graph;
}
