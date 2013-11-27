#include "../includes/set.h"
        
Set::Set()
{
    conjunto.clear();
}
        
void Set::insere(aresta_t a)
{
    /*bool achou = false;
    for (int i = 0; i < conjunto.size(); i++)
    {
        if (( (conjunto[i].n1 == a.n1) && (conjunto[i].n2 == a.n2) && (conjunto[i].peso == a.peso) ) ||
           ( (conjunto[i].n1 == a.n2) && (conjunto[i].n2 == a.n1) && (conjunto[i].peso == a.peso) ))
        {
            achou = true;
            break;
        }
    }
    
    if (!achou)*/
        conjunto.push_back(a);
}

void Set::remove(aresta_t a)
{
	for (int i = 0; i < conjunto.size(); i++)
	{
		if (( (conjunto[i].n1 == a.n1) && (conjunto[i].n2 == a.n2) && (conjunto[i].peso == a.peso) ) ||
		   ( (conjunto[i].n1 == a.n2) && (conjunto[i].n2 == a.n1) && (conjunto[i].peso == a.peso) ))
		{
			conjunto.erase( conjunto.begin() + i );
			break;
		}
	}
}

vector< aresta_t > Set::getConjunto()
{
	return conjunto;
}
        
aresta_t Set::aleatoria(int seed)
{
    srand(seed);
    
    return conjunto[ rand() % conjunto.size() ];
}
