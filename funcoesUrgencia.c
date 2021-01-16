#include "top.h"

/// <summary>
/// Fun��o para criar epis�dio de urg�ncia
/// </summary>
void criaEpUrg() {

	processoClinico episodio[MAXURGENCIA];

	FILE* novaUrgencia = fopen("urgencias.txt", "w");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (novaUrgencia == NULL) {									/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}
	/*Vari�vel para armazenar epis�dio de urg�ncia.*/
	episodio->epUrg=1;

	while (1)
	{
		printf("Insira o n�mero de SNS: ");
		scanf("%d", &episodio->sns);
		printf("Insira a data de entrada (dd-mm-aaaa):");
		scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
		printf("Insira o motivo de admiss�o:\nD-Doen�a\nC-Covid\nI-Isolamento\nT-inTensivos\n");
		scanf("%s", &episodio->estado);


		
		fprintf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%s\n",episodio->epUrg, episodio->sns, episodio->entrada.tm_mday, episodio->entrada.tm_mon, episodio->entrada.tm_year, episodio->estado);
		
		
		printf("Novo registo inserido com o epis�dio %d\n", episodio->epUrg);

		/*Necess�rio incrementar epis�dio de urg�ncia para o pr�ximo ciclo*/
		episodio->epUrg++;

		printf("Para novo registo prima enter, para sair prima espa�o.\n");
		char ch = getch();
		if (ch == ' ') {
			break;
		}
	}
	
	fclose(novaUrgencia);

}

/// <summary>
/// L� epis�dio de urg�ncia
/// </summary>
/// <returns> Array de epis�dios de urg�ncia.</returns>
int leUrgencia() {

	processoClinico episodio[MAXURGENCIA];
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i=1;
	while (!feof(leUrgencia)) {

		
		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year);

		i++;

	}

	fclose(leUrgencia);
}


/// <summary>
/// Fun��o que cria novo episodio de urg�ncia
/// </summary>
void novoEpUrg() {

	processoClinico episodio[MAXURGENCIA];

	FILE* urgAnt = fopen("urgencias.txt", "r");			
	if (urgAnt == NULL) {

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}

	/*Processo de busca do �ltimo epis�dio de urg�ncia para acrescentar novo.*/
	int i=1;///< Vari�vel que aramazena a posi��o do array apisodio[].
	while (!feof(urgAnt)) {
				
		fscanf(urgAnt, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		i++;

	}

	/*Necessidade de desincrementar o i, anulando o �ltimo incremento da fun��o while*/
	i--;
	episodio->epUrg = episodio[i].epUrg;						/*Atribui o �ltimo valor de epis�dio de urg�ncia � nova edi��o*/

	fclose(urgAnt);												/*Fecha o ficheiro no modo read*/


#pragma region leHospitais
/*L� informa��o dos hospitais*/

	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro n�o encontrado!");
		return 1;
	}

	int z = 0;
	/*Ciclo para leitura de cada linha do ficheiro dos hospitais carregando para o array hospitais[]*/
	while (!feof(hospitaisBase)) {

		
		fscanf(hospitaisBase, "%d\t%[^\t]\t\t%d\n", &hospitais[z].codigo, &hospitais[z].nome, &hospitais[z].maxDoentes);
		//printf("%d\t%s\t\t%d\n", hospitais[z].codigo, hospitais[z].nome, hospitais[z].maxDoentes);
		z++;

	}
	fclose(hospitaisBase);
#pragma endregion leHospitais

	FILE* novaUrgencia = fopen("urgencias.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/


	
		/*Necess�rio incrementar epis�dio de urg�ncia para o pr�ximo ciclo*/
		episodio->epUrg++;
		printf("Insira o n�mero de SNS: ");
		scanf("%d", &episodio->sns);
		printf("Insira a data de entrada (dd-mm-aaaa):");
		scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
		printf("Insira o motivo de admiss�o:\nD-Doen�a(outra)\nC-CovidInternamento\nI-Isolamento\nT-inTensivos\n");
		scanf("%s", &episodio->estado);

		int j = 1;///< Nova vari�vel para armazenar a posi��o do array episodio[].

		int codigoH = 0;										/*Vari�vel que armazena o c�digo do h pretendido*/

		/*Procura o hospital*/
		while (!feof(novaUrgencia)) {


			fscanf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
			//printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);

			/*C�lculo de vagas em cada hospital, mediante o registo de urg�ncias e doentes sem alta*/
			if (episodio[j].saida.tm_mday < 0) {						/*Procura hospitais cuja danta de sa�da seja <0, portanto, sem alta (ocupam vaga)*/
				codigoH = episodio[j].hospital;							/*Armazena o c�digo do hospital que tem esse doente*/
				for (int f = 0; f < 4; f++) {							/*Ciclo para procurar qual o hospital que tem o c�digo pretendido e para lhe retirar uma vaga*/
					if (codigoH == hospitais[f].codigo) {
						hospitais[f].maxDoentes = hospitais[f].maxDoentes - 1;						/*Retira uma vaga ao m�ximo de vagas*/
						
					}
				}
			}

			j++;
		}
		
		fclose(novaUrgencia);


		/*Reabre o ficheiro urgencias para lhe acrescentar registo*/
		FILE* fp = fopen("urgencias.txt", "a");

		episodio[j].epUrg = episodio->epUrg;
		episodio[j].sns = episodio->sns;
		episodio[j].entrada.tm_mday = episodio->entrada.tm_mday;
		episodio[j].entrada.tm_mon = episodio->entrada.tm_mon;
		episodio[j].entrada.tm_year = episodio->entrada.tm_year;
		
		episodio[j].estado = episodio->estado;
		episodio[j].saida.tm_mday = -1;
		episodio[j].saida.tm_mon = -1;
		episodio[j].saida.tm_year = -1;

		/*Procura identificar o estado do doente com o servi�o de sa�de que o pode receber.*/
		if (episodio[j].estado == 'C' || episodio->estado == 'c' && hospitais[0].maxDoentes>0)
		{			
			episodio[j].hospital = hospitais[0].codigo;
			fprintf(fp, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);
			printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[0].nome, hospitais[0].maxDoentes);

		} else

			/*Caso n�o se verifique a condi��o de exist�ncia de vagas*/
			if (hospitais[0].maxDoentes <= 0)
			{
				printf("O hospital adequado para esse doente n�o tem vagas!\n");
			}

		if (episodio[j].estado == 'T' || episodio->estado == 't' && hospitais[1].maxDoentes > 0)
		{
			episodio[j].hospital = hospitais[1].codigo;
			fprintf(fp, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);
			printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[1].nome, hospitais[1].maxDoentes);
		}
		else
			if (hospitais[1].maxDoentes <= 0)
			{
				printf("O hospital adequado para esse doente n�o tem vagas!\n");

			}


		if (episodio[j].estado == 'D' || episodio->estado == 'd' && hospitais[2].maxDoentes > 0)
		{
			episodio[j].hospital = hospitais[2].codigo;
			fprintf(fp, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);
			printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[2].nome, hospitais[2].maxDoentes);
		}
		else
			if (hospitais[2].maxDoentes <= 0)
			{
				printf("O hospital adequado para esse doente n�o tem vagas!\n");
			}

		if (episodio[j].estado == 'I' || episodio->estado == 'i' && hospitais[3].maxDoentes > 0)
		{
			episodio[j].hospital = hospitais[3].codigo;
			fprintf(fp, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);
			printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[3].nome, hospitais[3].maxDoentes);
		}
		else
			if (hospitais[3].maxDoentes <= 0)
			{
				printf("O hospital adequado para esse doente n�o tem vagas!\n");
			}

		fclose(fp);
		

		printf("Novo registo inserido com o epis�dio %d\n", episodio->epUrg);
	
}

/// <summary>
/// Fun��o que vai buscar procurar vaga nos hospitais para um doente de um determinado tipo
/// </summary>
void mostraHospital() {

	processoClinico episodio[MAXURGENCIA];

	FILE* urgAnt = fopen("urgencias.txt", "r");
	if (urgAnt == NULL) {

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}

	/*Processo de busca do �ltimo epis�dio de urg�ncia para acrescentar novo.*/
	int i = 1;///< Vari�vel que aramazena a posi��o do array apisodio[].
	while (!feof(urgAnt)) {

		fscanf(urgAnt, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		
		i++;

	}

	/*Necessidade de desincrementar o i, anulando o �ltimo incremento da fun��o while*/
	i--;
	episodio->epUrg = episodio[i].epUrg;						/*Atribui o �ltimo valor de epis�dio de urg�ncia � nova edi��o*/

	fclose(urgAnt);												/*Fecha o ficheiro no modo read*/


#pragma region leHospitais
/*L� informa��o dos hospitais*/
	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro n�o for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro n�o encontrado!");
		return 1;
	}

	int z = 0;
	/*Ciclo para leitura de cada linha do ficheiro dos hospitais carregando para o array hospitais[]*/
	while (!feof(hospitaisBase)) {

		fscanf(hospitaisBase, "%d\t%[^\t]\t\t%d\n", &hospitais[z].codigo, &hospitais[z].nome, &hospitais[z].maxDoentes);		
		z++;

	}
	fclose(hospitaisBase);

#pragma endregion leHospitais
	/*Abre o ficheiro de urg�ncias para ler registo*/
	FILE* novaUrgencia = fopen("urgencias.txt", "r");



	/*Necess�rio incrementar epis�dio de urg�ncia para o pr�ximo ciclo*/
	episodio->epUrg++;
	printf("Insira o n�mero de SNS: ");
	scanf("%d", &episodio->sns);
	printf("Insira a data de entrada (dd-mm-aaaa):");
	scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
	printf("Insira o motivo de admiss�o:\nD-Doen�a(outra)\nC-CovidInternamento\nI-Isolamento\nT-inTensivos\n");
	scanf("%s", &episodio->estado);

	int j = 1;///< Nova vari�vel para armazenar a posi��o do array episodio[].

	int codigoH = 0;///<Vari�vel que armazena o c�digo do h pretendido*/

	/*Procura o hospital*/
	while (!feof(novaUrgencia)) {


		fscanf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
		
		/*C�lculo de vagas em cada hospital, mediante o registo de urg�ncias e doentes sem alta*/
		if (episodio[j].saida.tm_mday < 0) {						/*Procura hospitais cuja danta de sa�da seja <0, portanto, sem alta (ocupam vaga)*/
			codigoH = episodio[j].hospital;							/*Armazena o c�digo do hospital que tem esse doente*/
			for (int f = 0; f < 4; f++) {							/*Ciclo para procurar qual o hospital que tem o c�digo pretendido e para lhe retirar uma vaga*/
				if (codigoH == hospitais[f].codigo) {
					hospitais[f].maxDoentes = hospitais[f].maxDoentes - 1;						/*Retira uma vaga ao m�ximo de vagas*/

				}
			}
		}

		j++;
	}


	/*Procura identificar o estado do doente com o servi�o de sa�de que o pode receber e mostra a informa��o de qual o hospital que tem vagas e � adequado ao estado do doente.*/
	j--;
	if (episodio[j].estado == 'C' || episodio->estado == 'c' && hospitais[0].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[0].nome, hospitais[0].maxDoentes);

	}
	else

		/*Caso n�o se verifique a condi��o de exist�ncia de vagas*/
		if (hospitais[0].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente n�o tem vagas!\n");
		}

	if (episodio[j].estado == 'T' || episodio->estado == 't' && hospitais[1].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[1].nome, hospitais[1].maxDoentes);
	}
	else
		if (hospitais[1].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente n�o tem vagas!\n");
		}


	if (episodio[j].estado == 'D' || episodio->estado == 'd' && hospitais[2].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[2].nome, hospitais[2].maxDoentes);
	}
	else
		if (hospitais[2].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente n�o tem vagas!\n");
		}

	if (episodio[j].estado == 'I' || episodio->estado == 'i' && hospitais[3].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[3].nome, hospitais[3].maxDoentes);
	}
	else
		if (hospitais[3].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente n�o tem vagas!\n");
		}
	fclose(novaUrgencia);
	
}
