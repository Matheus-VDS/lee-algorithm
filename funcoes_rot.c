#include "funcoes.h"

bool expansao()
{	
	bool achou = false; 
	t_celula celula, vizinho; 
	insere_fila(origem); 

	#pragma omp parallel private(vizinho)
	{
		#pragma omp single nowait
		while(ini_fila != NULL && !achou)
		{
			celula = remove_fila() ;	
			if (celula.i == destino.i && celula.j == destino.j)
				achou = true ;
			else
			{
				vizinho.i = celula.i - 1 ; // Vizinho norte
				vizinho.j = celula.j ;
				//#pragma omp task
				//{
					if ((vizinho.i >= 0) && (dist[vizinho.i][vizinho.j] == INT_MAX))
						{	
							dist[vizinho.i][vizinho.j] = dist[celula.i][celula.j] + 1 ;
							//#pragma omp atomic
							insere_fila(vizinho) ;
						}
				//}
				vizinho.i = celula.i + 1 ; // Vizinho sul
				vizinho.j = celula.j ;
				//#pragma omp task
				//{
					if ((vizinho.i < n_linhas) && (dist[vizinho.i][vizinho.j] == INT_MAX))
					{	
						dist[vizinho.i][vizinho.j] = dist[celula.i][celula.j] + 1 ;
						insere_fila(vizinho) ;
					}
				//}
				vizinho.i = celula.i ; // Vizinho oeste
				vizinho.j = celula.j - 1 ;
				//#pragma omp task
				//{
					if ((vizinho.j >= 0) && (dist[vizinho.i][vizinho.j] == INT_MAX))
					{	
						//#pragma omp atomic
						dist[vizinho.i][vizinho.j] = dist[celula.i][celula.j] + 1 ;
						insere_fila(vizinho) ;
					}
				//}
				//#pragma omp barrier
				vizinho.i = celula.i ; // Vizinho leste
				vizinho.j = celula.j + 1 ;
				//#pragma omp task
				//{
					if ((vizinho.j < n_colunas) && (dist[vizinho.i][vizinho.j] == INT_MAX))
					{
						dist[vizinho.i][vizinho.j] = dist[celula.i][celula.j] + 1 ;
						insere_fila(vizinho) ;
					}
				//}
				
			}
		}
	}	
	return achou;	
}

void traceback()
{
	t_celula celula, vizinho ;
	insere_caminho(destino) ;

	celula.i = destino.i ;
	celula.j = destino.j ;
	
	//#pragma omp parallel private(vizinho)
	//{	
		while (celula.i != origem.i || celula.j != origem.j)
		{
			// Determina se célula anterior no caminho é vizinho norte, sul, oeste ou leste
			// e insere esse vizinho no início do caminho
			
			vizinho.i = celula.i - 1 ; // Norte
			vizinho.j = celula.j ;
			if ((vizinho.i >= 0) && (dist[vizinho.i][vizinho.j] == dist[celula.i][celula.j] - 1))
				insere_caminho(vizinho) ;
			else
			{
				vizinho.i = celula.i + 1 ; // Sul
				vizinho.j = celula.j ;
				if ((vizinho.i < n_linhas) && (dist[vizinho.i][vizinho.j] == dist[celula.i][celula.j] - 1))
					insere_caminho(vizinho) ;
				else
				{
					vizinho.i = celula.i ; // Oeste
					vizinho.j = celula.j - 1 ;
					if ((vizinho.j >= 0) && (dist[vizinho.i][vizinho.j] == dist[celula.i][celula.j] - 1))
						insere_caminho(vizinho) ;
					else
					{
						vizinho.i = celula.i ; // Leste
						vizinho.j = celula.j + 1 ;
						if ((vizinho.j < n_colunas) && (dist[vizinho.i][vizinho.j] == dist[celula.i][celula.j] - 1))
							insere_caminho(vizinho) ;
					}
				}
			}
			celula.i = vizinho.i ;
			celula.j = vizinho.j ;
		}
		
	//}

}
