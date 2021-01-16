#include "top.h"


/// <summary>
/// Permite acrescentar novo utente � base de dados utentes.txt.
/// </summary>
void acrescentaUtente() {

	utente utentes[MAXUTENTES];									



	/*Ciclo de Registo individual de cada utente*/
	while (1) {
		printf("Insira o n�mero de SNS: ");
		scanf("%d", &utentes->sns);

		/*vai verificar se o SNS j� est� inserido para n�o haver duplica��es de utentes*/
		if (verificaSeExiste(utentes->sns) == 1) {
			printf("Utente j� existe.\n");
			break;
		};
		printf("Insira o primeiro nome: ");
		scanf("%s", &utentes->nome);
		printf("Insira o contacto: ");
		scanf("%d", &utentes->contacto);
		printf("Insira a idade: ");
		scanf("%d", &utentes->idade);

		FILE* registoUtente = fopen("utentes.txt", "a");			/*Abre o ficheiro utentes.txt para adicionar registo*/

		if (registoUtente == NULL) {								/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

			printf("Registo n�o inserido!");
			return 1;
		}

		fprintf(registoUtente, "%d\t%s\t\t%d\t%d\n", utentes->sns, utentes->nome, utentes->contacto, utentes->idade);


		printf("Novo utente registado.\nPressione qualquer tecla para novo registo ou espa�o para sair.\n");
		char ch = getch();
		if (ch == ' ') {
			break;
		}

		fclose(registoUtente);
		}
}

/// <summary>
/// L� os utentes armazenados no ficheiro utentes.txt. Abre no modo "read" e mostra no ecr�.
/// </summary>
/// <param name="u"> do tipo struct utente</param>
/// <param name="size"> do tipo int</param>
void mostraUtente(utente u[], int size) {

	
	/*Abre o ficheiro utentes.txt para ler registos*/
	FILE* registoUtente = fopen("utentes.txt", "r");


	/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/
	if (registoUtente == NULL) {								

		printf("Ficheiro n�o encontrado!");
		return 1;
	}

	
	/*Ciclo para leitura de cada linha do ficheiro de utentes carregando para o array utentes[]*/
	while (!feof(registoUtente)) {
		
		int i = 0;
		fscanf(registoUtente, "%d\t%s\t\t%d\t%d\n", &u[i].sns, &u[i].nome, &u[i].contacto, &u[i].idade);
		printf("%d\t%-10s\t%d\t%d\n", u[i].sns, u[i].nome, u[i].contacto, u[i].idade);
		i++;
		
		
		
	}

	fclose(registoUtente);
}

/// <summary>
/// Verifica se um determinado n�mero (sns) j� est� registado no ficheiro de utentes.
/// </summary>
/// <param name="sns"> do tipo inteiro, representando o n�mero inserido</param>
/// <returns>Devolve verdadeiro (1) se for cumprida a condi��o de igualdade</returns>
int verificaSeExiste(int sns) {

	utente u[MAXUTENTES];

	FILE *fp = fopen("utentes.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (fp == NULL) {								/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro n�o encontrado!");
		return 1;
	}
	/*Passa os registos do ficheiro para mem�ria*/
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d\t%s\t\t%d\t%d\n", &u[i].sns, &u[i].nome, &u[i].contacto, &u[i].idade);
		i++;
	}

	/*Ciclo de compara��o do n�mero sns inserido com os n�meros existentes no focheiro
	Em caso de encontrar n�mero coincidente, devolve 1*/
	for (int a = 0; a < i; a++) {
		if (sns == u[a].sns) {
			return 1;
		}
		
	}

	fclose(fp);

}