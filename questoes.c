#include "top.h"

#pragma region DOENTESCOVID
/// <summary>
/// C�lculo total de doentes COVID que passaram ou est�o nestas unidades de sa�de
/// </summary>
/// <returns>N�mero total de doentes</returns>
int doentesCovid() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i = 1;
	int dCovid = 0;///<Vari�vel que armazena o total de doentes
	
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital,&episodio[i].saida.tm_mday,&episodio[i].saida.tm_mon,&episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);
		

		/*Processo de incremento de uma unidade a cada doente Isolamento ou InternamentoCovid (I ou C)*/
		if (episodio[i].estado == 'C' || episodio[i].estado == 'c' || episodio[i].estado == 'I' || episodio[i].estado == 'i') {
			dCovid++;///<Incrementa o n�mero de o seu estado foi 'C'-COVID ou 'I'-Internamento Covid
		}
		i++;
	}

	fclose(leUrgencia);
	
	return dCovid;


}
#pragma endregion DOENTESCOVID

#pragma region NUMERODOENTESENTREDATAS

/// <summary>
/// Fun��o que devolve o n�mero de doentes que deram entrada num determinado hospital entre duas datas.
/// </summary>
/// <param name="h">C�digo do hospital pretendido</param>
/// <param name="dEntrada">data de in�cio</param>
/// <param name="dSaida">data de fim</param>
/// <returns>n�mero de doentes no hospital h entre dEntrada e dSaida</returns>
int doentesNesteH(int h, struct tm dEntrada, struct tm dSaida) {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Vari�veis*/
	int i = 1;

	int doentesNoH=0;///<Vari�vel que armazena doentes

	/*Zeramos todas as vari�veis n�o utilizadas desta struct tm para utilizar a fun��o mktime*/
	dEntrada.tm_hour = 0;
	dEntrada.tm_min = 0;
	dEntrada.tm_sec = 0;
	

	/*� necess�rio converter estas "struct tm" para "time_t" para usar a fun��o de compara��o de datas "difftime"*/
	time_t dEnt = mktime(&dEntrada);						


	dSaida.tm_hour = 0;
	dSaida.tm_min = 0;
	dSaida.tm_sec = 0;
	
	time_t dSai = mktime(&dSaida);


	/*Ciclo de leitura do registo de urg�ncia, identificando se determinado hospital tem doentes em determinadas datas*/
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		episodio[i].entrada.tm_hour = 0;
		episodio[i].entrada.tm_min = 0;
		episodio[i].entrada.tm_sec = 0;
		episodio[i].entrada.tm_year = (episodio[i].entrada.tm_year - 1900);
		episodio[i].entrada.tm_mon = (episodio[i].entrada.tm_mon - 1);

		/*Convers�o da data de entrada do doente*/
		time_t tEnt = mktime(&episodio[i].entrada);			
		

		/*Se diffSecs positivo, ent�o tEnt > dEnt, logo data de entrada do doente>entrada solicitada*/
		double diffSecs1 = difftime(tEnt,dEnt);

		/*Se diffSecs positivo, ent�o dSai > tEnt, logo data de entrada solicitada>entrada do doente*/
		double diffSecs2 = difftime(dSai, tEnt);			

		/*Processo de incremento de uma unidade por cada doente internado em determinada unidade de saude entre determinadas datas*/
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
/// <summary>
/// Fun��o que permite ordenar os doentes por ordem crescente de tempo de internamento.
/// </summary>
/// <returns>Lista ordenada e print m�dia e doente h� mais tempo internado</returns>
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
		
	internamento listagem[MAXURGENCIA];///<Array listagem com os n�meros de SNS e dias de internamento

	int i = 1;
	int j = 0;///<Vari�vel com n�mero de doentes que est�o a ser contabilizados, para c�lculo final da m�dia
	
	/*Leitura dos registos da urg�ncia*/
	while (!feof(leUrgencia)) {

		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		
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

			/*C�lculo do tempo de internamento*/
			double diffSecs = difftime(tSaida, tEntrada);


			/*Covers�o do tempo de segundos para dias*/
			listagem[j].dias = (diffSecs / 86400);				
			j++;///<incrementa doente que ainda n�o teve alta
		}
		i++;
	}

	/*Processo de ordenamento da listagem de dias de internamento*/
	int a, c, temp;///<vari�veis para armazenameto de dias a serem trocados
	
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

	/*Leitura do array*/
	int b = 0;
	while (b < j) {
		printf("%d\t%d dias\n", listagem[b].sns, listagem[b].dias);
		b++;
	}


	/** C�lculo da m�dia de dias de internamento */
	float soma = 0;
	float media;
	int n = 0;

	/*Soma do total de dias*/
	while (n < j) {
		soma = soma + (float)listagem[n].dias;
		n++;
	}
	media = soma / j;

	printf("A m�dia de dias de internamento � %.1f dias.\n", media);

	/*Apresenta��o do doente que esteve mais dias internado. Neste caso ser� o �ltimo da lista de ordenamento (posi��o [b-1], devido ao �ltimo incremento de b na leitura do array)*/
	printf("O doente que esteve mais tempo internado foi o %d com %d dias.\n", listagem[b-1].sns, listagem[b-1].dias);

	fclose(leUrgencia);
}
#pragma endregion ORDENATEMPOINTERNAMENTO

#pragma region CALCULAVAGAS
/// <summary>
/// Fun��o para calcular vagas e orden�-las por ordem crescente.
/// </summary>
/// <returns>Print no ecr� da lista de vagas dispon�veis em cada unidade de sa�de</returns>
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

	int codigoH = 0;///<Vari�vel que armazena o c�digo do h pretendido


	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
		
		/*Procura registos cuja data de sa�da seja <0, (sem alta, ainda ocupa cama)*/
		if (episodio[j].saida.tm_mday < 0) {						
			codigoH = episodio[j].hospital;									/*Armazena o c�digo do hospital que tem esse doente*/
			for (int f = 0; f < 4; f++) {									/*Ciclo para procurar qual o hospital que tem o c�digo pretendido*/
				if (codigoH == hospitais[f].codigo) {
					hospitais[f].maxDoentes=hospitais[f].maxDoentes-1;		/*Retira uma vaga ao n�mero de vagas nesse hospital*/
				}
			}
		}
				
		j++;
	}

	fclose(leUrgencia);

	/*Ordena a listagem de vagas por ordem crestente*/
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
	
	/*Ciclo para apresenta��o da listagem de vagas*/
	int l = 0;
	while (l < 4) {
		printf("O %s tem %d vagas dispon�veis.\n", hospitais[l].nome, hospitais[l].maxDoentes);
		l++;
	}
}
#pragma endregion CALCULAVAGAS

#pragma region NOVOEPISODIO
/// <summary>
/// Fun��o que insere novo episodio de urg�ncia. Op��o de inserir novo registo de utente
/// </summary>
/// <returns></returns>
int insereDoente() {

	//acrescentaUtente();
	novoEpUrg();
	
}
#pragma endregion NOVOEPISODIO