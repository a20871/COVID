#include "top.h"

/// <summary>
/// Função para criar episódio de urgência
/// </summary>
void criaEpUrg() {

	processoClinico episodio[MAXURGENCIA];

	FILE* novaUrgencia = fopen("urgencias.txt", "w");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (novaUrgencia == NULL) {									/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}
	/*Variável para armazenar episódio de urgência.*/
	episodio->epUrg=1;

	while (1)
	{
		printf("Insira o número de SNS: ");
		scanf("%d", &episodio->sns);
		printf("Insira a data de entrada (dd-mm-aaaa):");
		scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
		printf("Insira o motivo de admissão:\nD-Doença\nC-Covid\nI-Isolamento\nT-inTensivos\n");
		scanf("%s", &episodio->estado);


		
		fprintf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%s\n",episodio->epUrg, episodio->sns, episodio->entrada.tm_mday, episodio->entrada.tm_mon, episodio->entrada.tm_year, episodio->estado);
		
		
		printf("Novo registo inserido com o episódio %d\n", episodio->epUrg);

		/*Necessário incrementar episódio de urgência para o próximo ciclo*/
		episodio->epUrg++;

		printf("Para novo registo prima enter, para sair prima espaço.\n");
		char ch = getch();
		if (ch == ' ') {
			break;
		}
	}
	
	fclose(novaUrgencia);

}

/// <summary>
/// Lê episódio de urgência
/// </summary>
/// <returns> Array de episódios de urgência.</returns>
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
/// Função que cria novo episodio de urgência
/// </summary>
void novoEpUrg() {

	processoClinico episodio[MAXURGENCIA];

	FILE* urgAnt = fopen("urgencias.txt", "r");			
	if (urgAnt == NULL) {

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}

	/*Processo de busca do último episódio de urgência para acrescentar novo.*/
	int i=1;///< Variável que aramazena a posição do array apisodio[].
	while (!feof(urgAnt)) {
				
		fscanf(urgAnt, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		i++;

	}

	/*Necessidade de desincrementar o i, anulando o último incremento da função while*/
	i--;
	episodio->epUrg = episodio[i].epUrg;						/*Atribui o último valor de episódio de urgência à nova edição*/

	fclose(urgAnt);												/*Fecha o ficheiro no modo read*/


#pragma region leHospitais
/*Lê informação dos hospitais*/

	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
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


	
		/*Necessário incrementar episódio de urgência para o próximo ciclo*/
		episodio->epUrg++;
		printf("Insira o número de SNS: ");
		scanf("%d", &episodio->sns);
		printf("Insira a data de entrada (dd-mm-aaaa):");
		scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
		printf("Insira o motivo de admissão:\nD-Doença(outra)\nC-CovidInternamento\nI-Isolamento\nT-inTensivos\n");
		scanf("%s", &episodio->estado);

		int j = 1;///< Nova variável para armazenar a posição do array episodio[].

		int codigoH = 0;										/*Variável que armazena o código do h pretendido*/

		/*Procura o hospital*/
		while (!feof(novaUrgencia)) {


			fscanf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
			//printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);

			/*Cálculo de vagas em cada hospital, mediante o registo de urgências e doentes sem alta*/
			if (episodio[j].saida.tm_mday < 0) {						/*Procura hospitais cuja danta de saída seja <0, portanto, sem alta (ocupam vaga)*/
				codigoH = episodio[j].hospital;							/*Armazena o código do hospital que tem esse doente*/
				for (int f = 0; f < 4; f++) {							/*Ciclo para procurar qual o hospital que tem o código pretendido e para lhe retirar uma vaga*/
					if (codigoH == hospitais[f].codigo) {
						hospitais[f].maxDoentes = hospitais[f].maxDoentes - 1;						/*Retira uma vaga ao máximo de vagas*/
						
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

		/*Procura identificar o estado do doente com o serviço de saúde que o pode receber.*/
		if (episodio[j].estado == 'C' || episodio->estado == 'c' && hospitais[0].maxDoentes>0)
		{			
			episodio[j].hospital = hospitais[0].codigo;
			fprintf(fp, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", episodio[j].epUrg, episodio[j].sns, episodio[j].entrada.tm_mday, episodio[j].entrada.tm_mon, episodio[j].entrada.tm_year, episodio[j].estado, episodio[j].hospital, episodio[j].saida.tm_mday, episodio[j].saida.tm_mon, episodio[j].saida.tm_year);
			printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[0].nome, hospitais[0].maxDoentes);

		} else

			/*Caso não se verifique a condição de existência de vagas*/
			if (hospitais[0].maxDoentes <= 0)
			{
				printf("O hospital adequado para esse doente não tem vagas!\n");
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
				printf("O hospital adequado para esse doente não tem vagas!\n");

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
				printf("O hospital adequado para esse doente não tem vagas!\n");
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
				printf("O hospital adequado para esse doente não tem vagas!\n");
			}

		fclose(fp);
		

		printf("Novo registo inserido com o episódio %d\n", episodio->epUrg);
	
}

/// <summary>
/// Função que vai buscar procurar vaga nos hospitais para um doente de um determinado tipo
/// </summary>
void mostraHospital() {

	processoClinico episodio[MAXURGENCIA];

	FILE* urgAnt = fopen("urgencias.txt", "r");
	if (urgAnt == NULL) {

		printf("Erro ao encontrar ficheiro!");
		return 1;
	}

	/*Processo de busca do último episódio de urgência para acrescentar novo.*/
	int i = 1;///< Variável que aramazena a posição do array apisodio[].
	while (!feof(urgAnt)) {

		fscanf(urgAnt, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		
		i++;

	}

	/*Necessidade de desincrementar o i, anulando o último incremento da função while*/
	i--;
	episodio->epUrg = episodio[i].epUrg;						/*Atribui o último valor de episódio de urgência à nova edição*/

	fclose(urgAnt);												/*Fecha o ficheiro no modo read*/


#pragma region leHospitais
/*Lê informação dos hospitais*/
	unidadeSaude hospitais[4];

	FILE* hospitaisBase = fopen("hospitais.txt", "r");			/*Abre o ficheiro utentes.txt para adicionar registo*/

	if (hospitaisBase == NULL) {								/*Se o ficheiro não for encontrado, mostra mensagem de erro.*/

		printf("Ficheiro não encontrado!");
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
	/*Abre o ficheiro de urgências para ler registo*/
	FILE* novaUrgencia = fopen("urgencias.txt", "r");



	/*Necessário incrementar episódio de urgência para o próximo ciclo*/
	episodio->epUrg++;
	printf("Insira o número de SNS: ");
	scanf("%d", &episodio->sns);
	printf("Insira a data de entrada (dd-mm-aaaa):");
	scanf("%d-%d-%d", &episodio->entrada.tm_mday, &episodio->entrada.tm_mon, &episodio->entrada.tm_year);
	printf("Insira o motivo de admissão:\nD-Doença(outra)\nC-CovidInternamento\nI-Isolamento\nT-inTensivos\n");
	scanf("%s", &episodio->estado);

	int j = 1;///< Nova variável para armazenar a posição do array episodio[].

	int codigoH = 0;///<Variável que armazena o código do h pretendido*/

	/*Procura o hospital*/
	while (!feof(novaUrgencia)) {


		fscanf(novaUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[j].epUrg, &episodio[j].sns, &episodio[j].entrada.tm_mday, &episodio[j].entrada.tm_mon, &episodio[j].entrada.tm_year, &episodio[j].estado, &episodio[j].hospital, &episodio[j].saida.tm_mday, &episodio[j].saida.tm_mon, &episodio[j].saida.tm_year);
		
		/*Cálculo de vagas em cada hospital, mediante o registo de urgências e doentes sem alta*/
		if (episodio[j].saida.tm_mday < 0) {						/*Procura hospitais cuja danta de saída seja <0, portanto, sem alta (ocupam vaga)*/
			codigoH = episodio[j].hospital;							/*Armazena o código do hospital que tem esse doente*/
			for (int f = 0; f < 4; f++) {							/*Ciclo para procurar qual o hospital que tem o código pretendido e para lhe retirar uma vaga*/
				if (codigoH == hospitais[f].codigo) {
					hospitais[f].maxDoentes = hospitais[f].maxDoentes - 1;						/*Retira uma vaga ao máximo de vagas*/

				}
			}
		}

		j++;
	}


	/*Procura identificar o estado do doente com o serviço de saúde que o pode receber e mostra a informação de qual o hospital que tem vagas e é adequado ao estado do doente.*/
	j--;
	if (episodio[j].estado == 'C' || episodio->estado == 'c' && hospitais[0].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[0].nome, hospitais[0].maxDoentes);

	}
	else

		/*Caso não se verifique a condição de existência de vagas*/
		if (hospitais[0].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente não tem vagas!\n");
		}

	if (episodio[j].estado == 'T' || episodio->estado == 't' && hospitais[1].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[1].nome, hospitais[1].maxDoentes);
	}
	else
		if (hospitais[1].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente não tem vagas!\n");
		}


	if (episodio[j].estado == 'D' || episodio->estado == 'd' && hospitais[2].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[2].nome, hospitais[2].maxDoentes);
	}
	else
		if (hospitais[2].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente não tem vagas!\n");
		}

	if (episodio[j].estado == 'I' || episodio->estado == 'i' && hospitais[3].maxDoentes > 0)
	{
		
		printf("O utente %d vai para o %s que tem %d vagas\n", episodio->sns, hospitais[3].nome, hospitais[3].maxDoentes);
	}
	else
		if (hospitais[3].maxDoentes <= 0)
		{
			printf("O hospital adequado para esse doente não tem vagas!\n");
		}
	fclose(novaUrgencia);
	
}
