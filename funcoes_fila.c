#include "funcoes.h"

void inicializa(char* nome_arq_entrada)
{
	FILE *arq_entrada;	
	int n_obstaculos,		
		 n_linhas_obst,
		 n_colunas_obst;

	t_celula obstaculo;

	arq_entrada = fopen(nome_arq_entrada, "rt");

	if (arq_entrada == NULL)
	{
		printf("\nArquivo texto de entrada não encontrado\n");
		exit(1) ;
	}

	fscanf(arq_entrada, "%d %d", &n_linhas, &n_colunas);
	fscanf(arq_entrada, "%d %d", &origem.i, &origem.j);
	fscanf(arq_entrada, "%d %d", &destino.i, &destino.j);
	fscanf(arq_entrada, "%d", &n_obstaculos);

	dist = malloc(n_linhas * sizeof (int*));
	//#pragma omp parallel for schedule(static)
	for (int i = 0; i < n_linhas; i++)
		//#pragma omp task
		dist[i] = malloc(n_colunas * sizeof (int));

	for (int i = 0 ; i < n_linhas ; i++)
		//#pragma omp parallel for
		for (int j = 0 ; j < n_colunas ; j++)
			dist[i][j] = INT_MAX;

	dist[origem.i][origem.j] = 0;
	
	for (int k = 0 ; k < n_obstaculos ; k++)
	{
		fscanf(arq_entrada, "%d %d %d %d", &obstaculo.i, &obstaculo.j, &n_linhas_obst, &n_colunas_obst);
		#pragma omp parallel for
		for (int i = obstaculo.i; i < obstaculo.i + n_linhas_obst; i++)
			//#pragma omp parallel for
			for (int j = obstaculo.j ; j < obstaculo.j + n_colunas_obst ; j++)
				dist[i][j] = -1;
	}

	fclose(arq_entrada);

	// Inicializa fila vazia
	ini_fila = NULL;
	fim_fila = NULL;

	// Inicializa caminho vazio
	ini_caminho = NULL;
}

// ----------------------------------------------------------------------------

void finaliza(char* nome_arq_saida)
{
	FILE *arq_saida;	
	t_no *no;
	arq_saida = fopen(nome_arq_saida, "wt");
	fprintf(arq_saida, "%d\n", distancia_min);
	while (ini_caminho != NULL)
	{
		fprintf(arq_saida, "%d %d\n", ini_caminho->i, ini_caminho->j);
		no = ini_caminho ;
		ini_caminho = ini_caminho->prox;
		free(no);
	}
	fclose(arq_saida);
	for (int i = 0; i < n_linhas; i++)
		free(dist[i]);
	free(dist);
}

void insere_fila(t_celula celula)
{
	t_no *no = malloc(sizeof(t_no)) ;
	no->i = celula.i;
	no->j = celula.j;
	no->prox = NULL;

	if (ini_fila == NULL)
		ini_fila = no;
	else
		fim_fila->prox = no;

	fim_fila = no ;
}

t_celula remove_fila()
{
	t_celula celula;
	t_no *no;

	no = ini_fila ;

	celula.i = no->i;
	celula.j = no->j;

	ini_fila = no->prox;

	if (ini_fila == NULL)
		fim_fila = NULL;
	
	free(no) ;

	return celula ;
}

void insere_caminho(t_celula celula)
{
	t_no *no = malloc(sizeof(t_no));
	no->i = celula.i ;
	no->j = celula.j ;
	no->prox = ini_caminho ;
	ini_caminho = no ;
}