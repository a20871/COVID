#include "top.h"

/// <summary>
/// Função que lê e mostra a lista de hospitais do ficheiro "hospitais.txt".
/// </summary>
void mostraHospitais() {

	unidadeSaude hospitais[4];///>Opção de número fixo 4, não se prevendo abertura/encerramento do novas unidades de saúde.

	/*Abre o ficheiro utentes.txt para adicionar registo*/
	FILE* hospitaisBase = fopen("hospitais.txt", "r");			

	/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/
	if (hospitaisBase == NULL) {								

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


