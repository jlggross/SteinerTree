#include "../includes/buscas.h"

/****************************************************
Faz uma busca local determinística
Procura pela melhor solução nos vizinhos
****************************************************/
Solucao buscaLocalMelhor(Solucao inicial, Grafo g, int iter)
{
	cout << iter << "   ---   meio: " << inicial.getAvaliacao() << endl;
	if (iter < ITER_MAX) // define um limite de interações
	{
		vector<Solucao> vizinhos;
		inicial.criaVizinhos(&vizinhos,g);
		
		int posMenor = -1;
		int menor = inicial.getAvaliacao();
		for (int i = 0; i < vizinhos.size(); i++){
			int avaliado = vizinhos[i].getAvaliacao();
			if (avaliado < menor)
			{
				menor = avaliado;
				posMenor = i;
			}		
		}
		if (posMenor == -1)
			return inicial;
		else
		{
			return buscaLocalMelhor(vizinhos[posMenor],g,iter+1);
		}
	}else return inicial;
}

/****************************************************
Faz uma busca local.
Vai para a primeira solução melhor.
****************************************************/
Solucao buscaLocalPrimeira(Solucao inicial, Grafo g, int iter)
{
	cout << iter << "   ---   meio: " << inicial.getAvaliacao() << endl;
	if (iter < ITER_MAX) // define um limite de interações
	{
		vector<Solucao> vizinhos;
		inicial.criaVizinhos(&vizinhos,g);

		int menor = inicial.getAvaliacao();
		for (int i = 0; i < vizinhos.size(); i++)
		{
			int avaliado = vizinhos[i].getAvaliacao();
			if (avaliado < menor)
			{
				return buscaLocalPrimeira(vizinhos[i], g, iter+1);
			}		
		}

		return inicial;
	}else return inicial;
}


/****************************************************
Faz uma busca tabu.
Vai para a primeira solução melhor.
Utiliza uma lista de proibidos (tabu).
****************************************************/
Solucao buscaTabu(Solucao inicial, Grafo g, int iter, Listabu &listaTabu)
{
	while (iter < BT_MAX)
	{
		cout << iter << "   ---   meio: " << inicial.getAvaliacao() << " otima: " << listaTabu.getOtima().getAvaliacao() << endl;
		listaTabu.printLista();
		cout << endl;
		
		vector<Solucao> vizinhos;
		inicial.criaVizinhos(&vizinhos,g);
		cout << "vizinhos = " << vizinhos.size() << endl;

		listaTabu.insereTabu(inicial);		
		
		int menor = inicial.getAvaliacao();
		int tamanho = vizinhos.size();
		bool achou = false;
		int indMenor = -1;
		for (int i = 0; i < tamanho; i++)
		{				
			/* Procura pelo melhor vizinho */
			int avaliado = vizinhos[i].getAvaliacao();
			if (avaliado < menor && !listaTabu.contem(vizinhos[i]))
			{
				//~ if (listaTabu.atualizaOtima(vizinhos[i]))
				//~ {
					
					/* achou uma solução melhor, então zera as iterações em que a solução não mudou. */
					//listaTabu.insereTabu(vizinhos[i]);
					//achou = true;
					menor = avaliado;
					indMenor = i;
				//~ }
				//~ else 
				//~ {
					//~ //listaTabu.insereTabu(vizinhos[i]);
					//~ menor = avaliado;
					//~ indMenor = i;
				//~ }
			}
		}
		if (indMenor != -1)
		{
			if (listaTabu.atualizaOtima(vizinhos[indMenor]))
			{
				inicial = vizinhos[indMenor];
				iter = 0;				
				cout << "achou um melhor!" << endl;
			}
			else 
			{
				inicial = vizinhos[indMenor];
				iter++;				
			}
		}
		/*
		** se não houver um vizinho melhor que a solucao inicial
		** então insere a solução inicial na lista tabu e continua		
		** a busca com a primeira solução possível.
		**/
		else{			
			cout << "nao achou!" << endl;
			
			indMenor = -1;
			int valorMenor = MAX_AVALIACAO;
			for (int i = 0; i < tamanho; i++)
			{				
				int avaliado = vizinhos[i].getAvaliacao();
				if ( avaliado < valorMenor && !listaTabu.contem(vizinhos[i]))
				{
					if (listaTabu.atualizaOtima(vizinhos[i]))
					{
						valorMenor = avaliado;
						indMenor = i;
						achou = true;
						inicial = vizinhos[i];
						iter = 0;
					}
					else
					{
						valorMenor = avaliado;
						indMenor = i;
						achou = true;
						inicial = vizinhos[i];
						iter++;
					}
				}			
			}		
			if (!achou)
			{
				inicial = listaTabu.getOtima();
				iter++;
			}
			//~ else
			//~ {		    
				//~ /*
				//~ se todos os vizinhos estão na lista tabu retorna a solução ótima.
				//~ */
				//~ if (indMenor == -1)
				//~ {
					//~ if (vizinhos.size() > 0)
						//~ inicial = vizinhos[0];
					//~ else inicial = listaTabu.getOtima();
					//~ iter++;
				//~ }
			//~ }
		}		
	}return listaTabu.getOtima();
}

Solucao buscaTabuRec(Solucao inicial, Grafo g, int iter, Listabu &listaTabu)
{
	cout << iter << "   ---   meio: " << inicial.getAvaliacao() << " otima: " << listaTabu.getOtima().getAvaliacao() << endl;
	listaTabu.printLista();
	cout << endl;
	
	if (iter < BT_MAX) // define um limite de iterações
	{
		vector<Solucao> vizinhos;
		inicial.criaVizinhos(&vizinhos,g);

		//listaTabu.insereTabu(inicial);

		int menor = inicial.getAvaliacao();
		int tamanho = vizinhos.size();
		for (int i = 0; i < tamanho; i++)
		{	
			/* Procura pelo primeiro melhor vizinho */
			int avaliado = vizinhos[i].getAvaliacao();
			if (avaliado < menor && !listaTabu.contem(vizinhos[i]))
			{
				if (listaTabu.atualizaOtima(vizinhos[i]))
				{
				/* achou uma solução melhor, então zera as iterações em que a solução não mudou. */
					listaTabu.insereTabu(vizinhos[i]);
					return buscaTabuRec(vizinhos[i], g, 0, listaTabu);
				}
				else 
				{
					listaTabu.insereTabu(vizinhos[i]);
					return buscaTabuRec(vizinhos[i], g, iter+1, listaTabu);
				}
			}				
		}
		/*
		** se não houver um vizinho melhor que a solucao inicial
		** então insere a solução inicial na lista tabu e continua		
		** a busca com a primeira solução possível.
		**/
		int indMenor = -1, valorMenor = MAX_AVALIACAO;
		for (int i = 0; i < tamanho; i++)
		{
			int avaliado = vizinhos[i].getAvaliacao();
			if ( avaliado < valorMenor && !listaTabu.contem(vizinhos[i]))
			{
				valorMenor = avaliado;
				indMenor = i;
				return buscaTabuRec(vizinhos[i],g,iter+1,listaTabu);
			}
		}
		
		if (indMenor != -1)
			return buscaTabuRec(vizinhos[indMenor],g,iter+1,listaTabu);
		    
		/*
		se todos os vizinhos estão na lista tabu retorna a solução ótima.
		*/
		return listaTabu.getOtima();
	}else return inicial;
}
