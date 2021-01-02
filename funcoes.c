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
 * Esta função acresenta novos utentes lista inicial do ficheiro texto.
 * 
 */
void acrescentaUtente() {

	utente utentes[MAXUTENTES];									/*criado array de utentes para registo de cada utente*/

	FILE* registoUtente = fopen("utentes.txt", "a");			/*Cria registo de utentes no ficheiro utentes.txt*/

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