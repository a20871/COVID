#include "top.h"

/// <summary>
/// Esta função permite criar um ficheiro txt para registo de utentes, não requerendo qualqer parâmetro.
/// </summary>
void novoUtente() {

	utente utentes[MAXUTENTES];									/*criado array de utentes para registo de cada utente*/

	FILE* registoUtente = fopen("utentes.txt", "w+");			/*Cria registo de utentes no ficheiro utentes.txt*/

	if (registoUtente == NULL) {								/*Se o ficheiro não for criado, mostra mensagem de erro.*/

		printf("Registo não inserido!");
		return 1;
	}


	/*Ciclo para registo individual de cada utente*/
	while (1) {
		printf("Insira o número de SNS: ");
		scanf("%d", &utentes->sns);
		printf("Insira o primeiro nome: ");
		scanf("%s", &utentes->nome);
		printf("Insira o contacto: ");
		scanf("%d", &utentes->contacto);
		printf("Insira a idade: ");
		scanf("%d", &utentes->idade);

		fprintf(registoUtente, "%d\t%s\t\t%d\t%d\n", utentes->sns, utentes->nome, utentes->contacto, utentes->idade);
		
		printf("Novo utente registado.\nPressione qualquer tecla para novo registo ou espaço para sair.\n");
		char ch = getch();
		if (ch == ' ') {
			break;
		} 
	}
	
	
	fclose(registoUtente);


}


/**
 * Acresenta novos utentes lista inicial do ficheiro texto.
 * 
 */
void acrescentaUtente() {

	utente utentes[MAXUTENTES];									



	/*Registo egisto individual de cada utente*/
	
		printf("Insira o número de SNS: ");
		scanf("%d", &utentes->sns);

		if (verificaSeExiste(utentes->sns) == 0) {
			printf("utente já existe");
		};
		printf("Insira o primeiro nome: ");
		scanf("%s", &utentes->nome);
		printf("Insira o contacto: ");
		scanf("%d", &utentes->contacto);
		printf("Insira a idade: ");
		scanf("%d", &utentes->idade);

		FILE* registoUtente = fopen("utentes.txt", "a");			/*Abre o ficheiro utentes.txt para adicionar registo*/

		if (registoUtente == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

			printf("Registo não inserido!");
			return 1;
		}

		fprintf(registoUtente, "%d\t%s\t\t%d\t%d\n", utentes->sns, utentes->nome, utentes->contacto, utentes->idade);

		printf("Novo utente registado.\n");
	


	fclose(registoUtente);


}

/**
 * Permite mostrar os utentes armazenados no ficheiro.
 * 
 */
void mostraUtente(utente u[], int size) {

	

	FILE* registoUtente = fopen("utentes.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (registoUtente == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
		return 1;
	}

	
	/*Ciclo para leitura de cada linha do ficheiro de utentes carregando para o array utentes[]*/
	while (!feof(registoUtente)) {
		
		int i = 0;
		fscanf(registoUtente, "%d\t%s\t\t%d\t%d\n", &u[i].sns, &u[i].nome, &u[i].contacto, &u[i].idade);
		printf("%d\t%s\t\t%d\t%d\n", u[i].sns, u[i].nome, u[i].contacto, u[i].idade);
		i++;
		
		
		
	}

	fclose(registoUtente);
}



void acrescentaNovoUtente(utente u) {

	

	FILE* registoUtente = fopen("utentes.txt", "a");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (registoUtente == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Registo não inserido!");
		return 1;
	}

	
	fprintf(registoUtente, "%d\t%s\t\t%d\t%d\n", u.sns, u.nome, u.contacto, u.idade);

	printf("Novo utente registado.\n");
	printf("%d\t%s\t\t%d\t%d\n", u.sns, u.nome, u.contacto, u.idade);
	


	fclose(registoUtente);


}

int verificaSeExiste(int sns) {

	utente u[MAXUTENTES];

	FILE *fp = fopen("utentes.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (fp == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
		return 1;
	}

	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d\t%s\t\t%d\t%d\n", &u[i].sns, &u[i].nome, &u[i].contacto, &u[i].idade);
		i++;
	}

	for (int a = 0; a < i; a++) {
		if (sns == u[a].sns) {
			return -1;
		}
		else {
			return 0;

		}
	}

	fclose(fp);

}