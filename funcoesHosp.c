#include "top.h"

/// <summary>
/// Fun��o que l� e mostra a lista de hospitais do ficheiro "hospitais.txt".
/// </summary>
void mostraHospitais() {

	unidadeSaude hospitais[4];///>Op��o de n�mero fixo 4, n�o se prevendo abertura/encerramento do novas unidades de sa�de.

	/*Abre o ficheiro utentes.txt para adicionar registo*/
	FILE* hospitaisBase = fopen("hospitais.txt", "r");			

	/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/
	if (hospitaisBase == NULL) {								

		printf("Ficheiro n�o encontrado!");
		return 1;
	}


	/*Ciclo para leitura de cada linha do ficheiro dos hospitais carregando para o array hospitais[]*/
	while (!feof(hospitaisBase)) {

		int i = 0;
		fscanf(hospitaisBase, "%d\t%[^\t]\t\t%d\n", &hospitais[i].codigo, &hospitais[i].nome, &hospitais[i].maxDoentes);
		printf("%d\t%s\t\t%d\n", hospitais[i].codigo, hospitais[i].nome, hospitais[i].maxDoentes);
		i++;

		}
		fclose(hospitaisBase);
}


