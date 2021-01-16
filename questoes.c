#include "top.h"

#pragma region DOENTESCOVID
/// <summary>
/// Cálculo total de doentes COVID que passaram ou estão nestas unidades de saúde
/// </summary>
/// <returns>Número total de doentes</returns>
int doentesCovid() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i = 1;
	int dCovid = 0;///<Variável que armazena o total de doentes
	
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital,&episodio[i].saida.tm_mday,&episodio[i].saida.tm_mon,&episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);
		

		/*Processo de incremento de uma unidade a cada doente Isolamento ou InternamentoCovid (I ou C)*/
		if (episodio[i].estado == 'C' || episodio[i].estado == 'c' || episodio[i].estado == 'I' || episodio[i].estado == 'i') {
			dCovid++;///<Incrementa o número de o seu estado foi 'C'-COVID ou 'I'-Internamento Covid
		}
		i++;
	}

	fclose(leUrgencia);
	
	return dCovid;


}
#pragma endregion DOENTESCOVID

#pragma region NUMERODOENTESENTREDATAS

/// <summary>
/// Função que devolve o número de doentes que deram entrada num determinado hospital entre duas datas.
/// </summary>
/// <param name="h">Código do hospital pretendido</param>
/// <param name="dEntrada">data de início</param>
/// <param name="dSaida">data de fim</param>
/// <returns>número de doentes no hospital h entre dEntrada e dSaida</returns>
int doentesNesteH(int h, struct tm dEntrada, struct tm dSaida) {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Variáveis*/
	int i = 1;

	int doentesNoH=0;///<Variável que armazena doentes

	/*Zeramos todas as variáveis não utilizadas desta struct tm para utilizar a função mktime*/
	dEntrada.tm_hour = 0;
	dEntrada.tm_min = 0;
	dEntrada.tm_sec = 0;
	

	/*É necessário converter estas "struct tm" para "time_t" para usar a função de comparação de datas "difftime"*/
	time_t dEnt = mktime(&dEntrada);						


	dSaida.tm_hour = 0;
	dSaida.tm_min = 0;
	dSaida.tm_sec = 0;
	
	time_t dSai = mktime(&dSaida);


	/*Ciclo de leitura do registo de urgência, identificando se determinado hospital tem doentes em determinadas datas*/
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		episodio[i].entrada.tm_hour = 0;
		episodio[i].entrada.tm_min = 0;
		episodio[i].entrada.tm_sec = 0;
		episodio[i].entrada.tm_year = (episodio[i].entrada.tm_year - 1900);
		episodio[i].entrada.tm_mon = (episodio[i].entrada.tm_mon - 1);

		/*Conversão da data de entrada do doente*/
		time_t tEnt = mktime(&episodio[i].entrada);			
		

		/*Se diffSecs positivo, então tEnt > dEnt, logo data de entrada do doente>entrada solicitada*/
		double diffSecs1 = difftime(tEnt,dEnt);

		/*Se diffSecs positivo, então dSai > tEnt, logo data de entrada solicitada>entrada do doente*/
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
/// Função que permite ordenar os doentes por ordem crescente de tempo de internamento.
/// </summary>
/// <returns>Lista ordenada e print média e doente há mais tempo internado</returns>
int internamentoCresc() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Struct para armazenar nº SNS do utente e respetivo tempo de internamento*/
	typedef struct internamento {
		int sns;
		int dias;
	}internamento;
		
	internamento listagem[MAXURGENCIA];///<Array listagem com os números de SNS e dias de internamento

	int i = 1;
	int j = 0;///<Variável com número de doentes que estão a ser contabilizados, para cálculo final da média
	
	/*Leitura dos registos da urgência*/
	while (!feof(leUrgencia)) {

		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		
		/*Exclusão de doentes que ainda não tiveram alta*/
		if (episodio[i].saida.tm_mday > 0) {

			
			listagem[j].sns = episodio[i].sns;

			/*Conversão da data de entrada do doente*/
			episodio[i].entrada.tm_hour = 0;
			episodio[i].entrada.tm_min = 0;
			episodio[i].entrada.tm_sec = 0;
			episodio[i].entrada.tm_year = (episodio[i].entrada.tm_year - 1900);
			episodio[i].entrada.tm_mon = (episodio[i].entrada.tm_mon - 1);
			time_t tEntrada = mktime(&episodio[i].entrada);

			/*Conversão da data de saida do doente*/
			episodio[i].saida.tm_hour = 0;
			episodio[i].saida.tm_min = 0;
			episodio[i].saida.tm_sec = 0;
			episodio[i].saida.tm_year = (episodio[i].saida.tm_year - 1900);
			episodio[i].saida.tm_mon = (episodio[i].saida.tm_mon - 1);
			time_t tSaida = mktime(&episodio[i].saida);

			/*Cálculo do tempo de internamento*/
			double diffSecs = difftime(tSaida, tEntrada);


			/*Coversão do tempo de segundos para dias*/
			listagem[j].dias = (diffSecs / 86400);				
			j++;///<incrementa doente que ainda não teve alta
		}
		i++;
	}

	/*Processo de ordenamento da listagem de dias de internamento*/
	int a, c, temp;///<variáveis para armazenameto de dias a serem trocados
	
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


	/** Cálculo da média de dias de internamento */
	float soma = 0;
	float media;
	int n = 0;

	/*Soma do total de dias*/
	while (n < j) {
		soma = soma + (float)listagem[n].dias;
		n++;
	}
	media = soma / j;

	printf("A média de dias de internamento é %.1f dias.\n", media);

	/*Apresentação do doente que esteve mais dias internado. Neste caso será o último da lista de ordenamento (posição [b-1], devido ao último incremento de b na leitura do array)*/
	printf("O doente que esteve mais tempo internado foi o %d com %d dias.\n", listagem[b-1].sns, listagem[b-1].dias);

	fclose(leUrgencia);
}
#pragma endregion ORDENATEMPOINTERNAMENTO

#pragma region CALCULAVAGAS
/// <summary>
/// Função para calcular vagas e ordená-las por ordem crescente.
/// </summary>
/// <returns>Print no ecrã da lista de vagas disponíveis em cada unidade de saúde</returns>
int ordenaVagas() {


	/*Leitura de ficheiro com informação dos hospitais*/
	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
		return 1;
	}

	int i = 0;

	/*Ciclo para leitura de cada linha do ficheiro dos hospitais carregando para o array hospitais[]*/
	while (!feof(hospitaisBase)) {
				
		fscanf(hospitaisBase, "%d\t%[^\t]\t\t%d\n", &hospitais[i].codigo, &hospitais[i].nome, &hospitais[i].maxDoentes);
		i++;
	}
	fclose(hospitaisBase);


	/*Leitura da informação de urgências*/
	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	/*Variáveis*/
	int j = 1;

	int codigoH = 0;///<Variável que armazena o código do h pretendido


	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
		
		/*Procura registos cuja data de saída seja <0, (sem alta, ainda ocupa cama)*/
		if (episodio[j].saida.tm_mday < 0) {						
			codigoH = episodio[j].hospital;									/*Armazena o código do hospital que tem esse doente*/
			for (int f = 0; f < 4; f++) {									/*Ciclo para procurar qual o hospital que tem o código pretendido*/
				if (codigoH == hospitais[f].codigo) {
					hospitais[f].maxDoentes=hospitais[f].maxDoentes-1;		/*Retira uma vaga ao número de vagas nesse hospital*/
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
	
	/*Ciclo para apresentação da listagem de vagas*/
	int l = 0;
	while (l < 4) {
		printf("O %s tem %d vagas disponíveis.\n", hospitais[l].nome, hospitais[l].maxDoentes);
		l++;
	}
}
#pragma endregion CALCULAVAGAS

#pragma region NOVOEPISODIO
/// <summary>
/// Função que insere novo episodio de urgência. Opção de inserir novo registo de utente
/// </summary>
/// <returns></returns>
int insereDoente() {

	//acrescentaUtente();
	novoEpUrg();
	
}
#pragma endregion NOVOEPISODIO