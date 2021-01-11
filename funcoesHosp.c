#include "top.h"

/// <summary>
/// Função para leitura do ficheiro de hospitais e cópia para o array hospitais
/// </summary>
int mostraHospitais() {

	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
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


