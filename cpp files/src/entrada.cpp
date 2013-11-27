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
    
    /* pula tudo, at� os nodos */
    while( palavra != "Nodes" )
        cin >> palavra;
    cin >> nodos;
    
    /********************
     aloca��o do grafo 
     *******************/   
    Grafo graph(nodos);    
//Solucao sAux(nodos);       /* Esta linha est� aqui s� para testes!!! */
	
    /* at� as arestas */
    while( palavra != "Edges" )
	    cin >> palavra;
    cin >> arestas;
    
    Solucao sAux(nodos);
    for (int i = 0; i < arestas; i++)
    {
	aresta_t a;
	cin >> palavra >> a.n1 >> a.n2 >> a.peso;
	    
        graph.insereAresta( a );
        //sAux.insereAresta( a );  /* Esta linha est� aqui s� para testes!!! */
    }
    
    /* at� os terminais: primeira apari��o */
    while( palavra != "Terminals" )
        cin >> palavra;
    palavra = "";
    
    /* segunda apari��o */
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

    /* vai at� o fim do arquivo: n�o serve para nada */
    while( palavra != "EOF" )
        cin >> palavra;

    return graph;
}
