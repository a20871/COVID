#include "top.h"

#pragma region DOENTESCOVID
/**
 * C�lculo do total de doentes COVID isolados ou internados..
 * 
 * \return Total de doentes COVID
 */
int doentesCovid() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i = 1;
	int dCovid = 0;										/*Vari�vel que armazena doentes COVID*/
	
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital,&episodio[i].saida.tm_mday,&episodio[i].saida.tm_mon,&episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);
		

		/*Processo de incremento de uma unidade a cada doente Isolamento ou InternamentoCovid (I ou C)*/
		if (episodio[i].estado == 'C' || episodio[i].estado == 'c' || episodio[i].estado == 'I' || episodio[i].estado == 'i') {
			dCovid++;

		}

		i++;
		
	}

	fclose(leUrgencia);
	
	return dCovid;


}
#pragma endregion DOENTESCOVID

#pragma region NUMERODOENTESENTREDATAS
/**
 * Fun��o que devolve o n�mero de doentes que deram entrada num determinado hospital entre duas datas.
 * 
 * \param h ->C�digo do hospital pretendido
 * \param dEntrada ->data de in�cio
 * \param dSaida ->data de fim
 * \return ->n�mero de doentes no hospital h entre dEntrada e dSaida
 */
int doentesNesteH(int h, struct tm dEntrada, struct tm dSaida) {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Vari�veis*/
	int i = 1;

	int doentesNoH=0;										/*Vari�vel que armazena doentes*/

	/*Zeramos todas as vari�veis n�o utilizadas desta struct tm para utilizar a fun��o mktime*/
	dEntrada.tm_hour = 0;
	dEntrada.tm_min = 0;
	dEntrada.tm_sec = 0;
		
	time_t dEnt = mktime(&dEntrada);						/*� necess�rio converter estas "struct tm" para "time_t"
															para usar a fun��o de compara��o de datas "difftime"*/


	dSaida.tm_hour = 0;
	dSaida.tm_min = 0;
	dSaida.tm_sec = 0;
	
	time_t dSai = mktime(&dSaida);



	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		episodio[i].entrada.tm_hour = 0;
		episodio[i].entrada.tm_min = 0;
		episodio[i].entrada.tm_sec = 0;
		episodio[i].entrada.tm_year = (episodio[i].entrada.tm_year - 1900);
		episodio[i].entrada.tm_mon = (episodio[i].entrada.tm_mon - 1);
		time_t tEnt = mktime(&episodio[i].entrada);			/*Convers�o da data de entrada do doente*/
		

		double diffSecs1 = difftime(tEnt,dEnt);				/*Se diffSecs positivo, ent�o tEnt > dEnt, logo data de entrada do doente>entrada solicitada*/
		double diffSecs2 = difftime(dSai, tEnt);			/*Se diffSecs positivo, ent�o dSai > tEnt, logo data de entrada solicitada>entrada do doente*/



		/*Processo de incremento de uma unidade a cada doente internado em determinada unidade de saude entre determinadas datas*/
		if (episodio[i].hospital == h && diffSecs1>=0 && diffSecs2>=0) {
			doentesNoH++;

		}

		i++;

	}

	fclose(leUrgencia);

	return doentesNoH;

}
#pragma endregion NUMERODOENTESENTREDATAS

#pragma region ORDENATEMPOINTERNAMENTO
/**
 * Fun��o que permite ordenar os doentes por ordem crescente de tempo de internamento.
 * 
 * \return 
 */
int internamentoCresc() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Struct para armazenar n� SNS do utente e respetivo tempo de internamento*/
	typedef struct internamento {
		int sns;
		int dias;
	}internamento;
		
	internamento listagem[MAXURGENCIA];



	int i = 1;
	int j = 0;										 /*Vari�vel com n�mero de doentes que est�o a ser contabilizados
													 Desta forma ser� poss�vel criar um array
													 apenas com os doentes internado que tiveram alta e respetivos tempos de internamento*/

	while (!feof(leUrgencia)) {

		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		/*Cria��o de uma nova lista de doentes com os tempos de internamento*/
		/*Exclus�o de doentes que ainda n�o tiveram alta*/
		if (episodio[i].saida.tm_mday > 0) {

			
			listagem[j].sns = episodio[i].sns;

			/*Convers�o da data de entrada do doente*/

			episodio[i].entrada.tm_hour = 0;
			episodio[i].entrada.tm_min = 0;
			episodio[i].entrada.tm_sec = 0;
			episodio[i].entrada.tm_year = (episodio[i].entrada.tm_year - 1900);
			episodio[i].entrada.tm_mon = (episodio[i].entrada.tm_mon - 1);
			time_t tEntrada = mktime(&episodio[i].entrada);

			/*Convers�o da data de saida do doente*/

			episodio[i].saida.tm_hour = 0;
			episodio[i].saida.tm_min = 0;
			episodio[i].saida.tm_sec = 0;
			episodio[i].saida.tm_year = (episodio[i].saida.tm_year - 1900);
			episodio[i].saida.tm_mon = (episodio[i].saida.tm_mon - 1);
			time_t tSaida = mktime(&episodio[i].saida);

			double diffSecs = difftime(tSaida, tEntrada);		/*C�lculo do tempo de internamento*/
			listagem[j].dias = (diffSecs / 86400);				/*Covers�o do tempo de segundos para dias*/
			j++;
		}
		i++;
	}

	/*Processo de ordenamento da listagem de dias de internamento*/
	
	int a, c, temp;
	
	for (a = 0; a < j-1; ++a) 
	{
		for (c = 0; c < j - 1 - a; ++c)
		{
			if (listagem[c].dias > listagem[c + 1].dias)
			{
				temp = listagem[c + 1].dias;
				listagem[c + 1].dias = listagem[c].dias;
				listagem[c].dias = temp;
			}
		}
	}

	int b = 0;
	while (b < j) {
		printf("%d\t%d dias\n", listagem[b].sns, listagem[b].dias);
		b++;
	}


	/** C�lculo da m�dia de dias de internamento */

	float soma = 0;
	float media;
	int n = 0;

	while (n < j) {
		soma = soma + (float)listagem[n].dias;
		n++;
	}
	media = soma / j;

	printf("A m�dia de dias de internamento � %.1f dias.\n", media);


	/** Apresenta��o do doente que esteve mais dias internado */

	printf("O doente que esteve mais tempo internado foi o %d com %d dias.\n", listagem[b-1].sns, listagem[b-1].dias);

	fclose(leUrgencia);
}
#pragma endregion ORDENATEMPOINTERNAMENTO

#pragma region CALCULAVAGAS
/**
 * Fun��o para calcular vagas e orden�-las por ordem crescente.
 * 
 * \return 
 */
int ordenaVagas() {


	/*Leitura de ficheiro com informa��o dos hospitais*/
	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro n�o encontrado!");
		return 1;
	}

	int i = 0;
	/*Ciclo para leitura de cada linha do ficheiro dos hospitais carregando para o array hospitais[]*/
	while (!feof(hospitaisBase)) {

		
		fscanf(hospitaisBase, "%d\t%[^\t]\t\t%d\n", &hospitais[i].codigo, &hospitais[i].nome, &hospitais[i].maxDoentes);
		printf("%d\t%s\t\t%d\n", hospitais[i].codigo, hospitais[i].nome, hospitais[i].maxDoentes);
		i++;

	}
	fclose(hospitaisBase);




	/*Leitura da informa��o de urg�ncias*/
	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Vari�veis*/
	int j = 1;

	int codigoH = 0;										/*Vari�vel que armazena o c�digo do h pretendido*/


	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
		//printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);

		
		if (episodio[j].saida.tm_mday < 0) {						/*Procura hospitais cuja danta de sa�da seja <0*/
			codigoH = episodio[j].hospital;							/*Armazena o c�digo do hospital que tem esse doente*/
			for (int f = 0; f < 4; f++) {							/*Ciclo para procurar qual o hospital que tem o c�digo pretendido*/
				if (codigoH == hospitais[f].codigo) {
					hospitais[f].maxDoentes=hospitais[f].maxDoentes-1;						/*Retira uma vaga ao m�ximo de vagas*/
				}
			}
		}
				
		j++;
	}

	fclose(leUrgencia);

	/*int k = 0;
	while (k < 4) {
		printf("O %s tem %d vagas dispon�veis.\n", hospitais[k].nome, hospitais[k].maxDoentes);
		k++;
	}*/
	
	
	int m, n, temp;
		for (m = 0; m < 4; ++m)
		{
			for (n = 0; n < 4 - 1 - m; ++n)
			{
				if (hospitais[n].maxDoentes < hospitais[n + 1].maxDoentes)
				{
					temp = hospitais[n + 1].maxDoentes;
					hospitais[n + 1].maxDoentes = hospitais[n].maxDoentes;
					hospitais[n].maxDoentes = temp;
				}
			}
		}
	

	int l = 0;
	while (l < 4) {
		printf("O %s tem %d vagas dispon�veis.\n", hospitais[l].nome, hospitais[l].maxDoentes);
		l++;
	}
}
#pragma endregion CALCULAVAGAS

int insereDoente() {

	//acrescentaUtente();
	novoEpUrg();
	
}