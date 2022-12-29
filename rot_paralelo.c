// Aluno: Matheus Vieira de Souza    RGA: 2021.1904.048-3
// Disciplina: Programação Paralela
// Roteamento usando algoritmo de Lee
// Para compilar: gcc rot_paralelo.c funcoes_fila.c funcoes_rot.c funcoes.h -o rot_paralelo -Wall -fopenmp
// Para executar: ./rot_paralelo <arquivo_entrada.txt> <arquivo_saida.txt>
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "funcoes.h"

int main(int argc, char** argv)
{	
	double x, tfin, tini;	
	
	char nome_arq_entrada[100], nome_arq_saida[100];
	bool achou ;

	if(argc != 3)
	{
		printf("O programa foi executado com argumentos incorretos.\n") ;
		printf("Uso: ./rot_seq <nome arquivo entrada> <nome arquivo saída>\n") ;
		exit(1) ;
	}

	strcpy(nome_arq_entrada, argv[1]) ;
	strcpy(nome_arq_saida, argv[2]) ;
	inicializa(nome_arq_entrada);
	tini = omp_get_wtime();
	// Fase de expansão: calcula distância da origem até demais células do grid
	achou = expansao();
	// Se não encontrou caminho de origem até destino
	if (! achou)
		distancia_min = -1 ;
	else
	{
		// Obtém distância do caminho mínimo da origem até destino
		distancia_min = dist[destino.i][destino.j] ;
		// Fase de traceback: obtém caminho mínimo
		traceback();
	}
	
	// Finaliza e escreve arquivo de saida
	finaliza(nome_arq_saida) ;
	// Calcula o tempo de execução
	tfin = omp_get_wtime();
	x = tfin - tini;
	printf("Tempo de execucao: %lf", x);
	return 0;
}