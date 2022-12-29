#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <omp.h>
// ----------------------------------------------------------------------------
// Tipos
typedef struct	// Posição de uma célula do grid
{
	int i, j;
} t_celula;

typedef struct no	// Nó da fila de células a serem tratadas e do caminho encontrado 
{
	int i, j ;
	struct no *prox;
} t_no;

// ----------------------------------------------------------------------------
// Variáveis globais

int n_linhas,		// No. de linhas e colunas do grid
	 n_colunas,
	 **dist,			// Matriz com distância da origem até cada célula do grid
	 distancia_min;	// Distância do caminho mínimo de origem a destino

t_celula origem,	// Células origem e destino no grid
			destino;

t_no *ini_fila,	// Ponteiros para início e fim da fila de células a serem tratadas (fila FIFO)
	  *fim_fila,
	  *ini_caminho ;	// Ponteiro para início do caminho encontrado

void inicializa(char* nome_arq_entrada);
void finaliza(char* nome_arq_saida);
void insere_fila(t_celula celula);
t_celula remove_fila();
void insere_caminho(t_celula celula);
bool expansao();
void traceback();
