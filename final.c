#include "top.h"

/// <summary>
/// Fun��o que vai gerar uma tabela com informa��o dos registos de cada epis�dio de urgenciacom nome do doente, hospital onde deu entrada e tempo total de internamento.
/// </summary>
void tabela() {

	processoClinico ep[MAXUTENTES];
	int nRegistos = 0;
	mostraUrgencia(ep, nRegistos);


}





/// <summary>
/// un��o que mostra os registos de epis�dios de urg�ncia:
/// N�mero de epis�dio de urg�ncia,
/// SNS do doente
/// Tipo de cuidado necess�rio / doen�a
/// C�digo do Hospital onde deu entrada
/// Data de entrada na urg�ncia
/// Tempo Total de internamento dos doentes que j� tiveram alta
/// Nome do doente
/// Nome do hospital em que o doente deu entrada
/// </summary>
/// <param name="episodio"> processoClinico das urg�ncias</param>
/// <returns>Tabela de episodios de urgencia com a informa��o solicitada</returns>
int mostraUrgencia(processoClinico episodio[]) {

	
	
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i = 1;
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		
		/*Para cada registo vai procurar e acrescentar ao array a informa��o em falta */
		converteTempo(episodio, i);
		encontraNome(episodio, i);
		encontraHospital(episodio, i);

		/*Apresenta a informa��o total de cada processo*/
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\t%d\t%-12s\t%s\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year, episodio[i].tempoInterna, episodio[i].nome, episodio[i].nomeHosp);
			
		i++;
	}
	
	fclose(leUrgencia);

	/*Contagem do total de epis�dios para gravar a informa��o no ficheiro bin�rio*/
	int ce = contaEpisodios(episodio, i);

	gravaBinario(episodio, ce);
	
}

/// <summary>
/// Fun��o que calcula o tempo de internamento.
/// </summary>
/// <param name="a">Processo clinico</param>
/// <param name="b">n� processo cl�nico</param>
/// <returns>Tempo de internamento neste processo e acrescenta ao processo</returns>
int converteTempo(processoClinico a[], int b) {
	
	a[b].entrada.tm_hour = 0;
	a[b].entrada.tm_min = 0;
	a[b].entrada.tm_sec = 0;
	a[b].entrada.tm_year = (a[b].entrada.tm_year - 1900);
	a[b].entrada.tm_mon = (a[b].entrada.tm_mon - 1);
	time_t tEntrada = mktime(&a[b].entrada);

	a[b].saida.tm_hour = 0;
	a[b].saida.tm_min = 0;
	a[b].saida.tm_sec = 0;
	a[b].saida.tm_year = (a[b].saida.tm_year - 1900);
	a[b].saida.tm_mon = (a[b].saida.tm_mon - 1);
	time_t tSaida = mktime(&a[b].saida);
	
	double diffSecs = difftime(tSaida, tEntrada);		/*C�lculo do tempo de internamento*/
	double day = (diffSecs / 86400);
	int dias = (int)day;

	/*Anula o tempo de internamento caso n�o tenha havido alta*/
	if (diffSecs < 0) {
		a[b].tempoInterna = 0;
	}
	else {
		a[b].tempoInterna = dias;
	}

	/*Reverte a data para o formato inicial para que posso ser imprimido em conformidade com a data real*/
	a[b].entrada.tm_year = (a[b].entrada.tm_year + 1900);
	a[b].entrada.tm_mon = (a[b].entrada.tm_mon + 1);

	a[b].saida.tm_year = (a[b].saida.tm_year + 1900);
	a[b].saida.tm_mon = (a[b].saida.tm_mon + 1);


}

/// <summary>
/// Encontra o nome referente a um n�mero sns da lista de utentes e copia-o para o registo da urg�ncia.
/// </summary>
/// <param name="a">processo cl�nico da urg�ncia</param>
/// <param name="b">indice do array</param>
void encontraNome(processoClinico a[], int b) {

	FILE* apf = fopen("utentes.txt", "r");
	utente doentRegistos[MAXUTENTES];


	int n = 0;
	while (!feof(apf)) {
		fscanf(apf, "%d\t%s\t%d\t%d",&doentRegistos[n].sns, &doentRegistos[n].nome, &doentRegistos[n].contacto, &doentRegistos[n].idade);
		n++;
	}

	

	int snsPretendido = 0;///<vari�vel armazena n� sns pretendido
	snsPretendido = a[b].sns;

	/*Procura o numero de sns nos utentes e copia-o para o novo array*/
	for (int m = 0; m < n - 1; m++) {
		if (snsPretendido == doentRegistos[m].sns) {
			strcpy(a[b].nome, doentRegistos[m].nome);
			break;
			}
		
	}
	
	fclose(apf);

}

/// <summary>
/// Encontra o hospital referente ao c�digo inserido na urg�ncia.
/// </summary>
/// <param name="a">processo cl�nico pretendido</param>
/// <param name="b">�ndice do processo pretendido</param>
void encontraHospital(processoClinico a[], int b) {

	FILE* aph = fopen("hospitais.txt", "r");
	unidadeSaude h[4];

	int n = 0;
	while (!feof(aph)) {
		fscanf(aph, "%d\t%[^\t]\t\t%d", &h[n].codigo, &h[n].nome, &h[n].maxDoentes);
		n++;
	}

	int codPretendido = 0;///<Vari�vel que armazena o c�digo do hospital
	codPretendido = a[b].hospital;

	/*Encontra o c�digo e copia o nome do hospital*/
	for (int m = 0; m < n; m++) {
		if (codPretendido == h[m].codigo) {
			strcpy(a[b].nomeHosp, h[m].nome);
			break;

		}

	}


	fclose(aph);

}

/// <summary>
/// Fun��o que permite contar eo total de epis�dios.
/// </summary>
/// <param name="a">processoClinico</param>
/// <param name="b">indice do processo</param>
/// <returns>Devolve o �ltimo n�mero do epis�dio de urg�ncia, correspondente ao total de epis�dios</returns>
int contaEpisodios(processoClinico a[], int b) {

	FILE* leEpisodios = fopen("urgencias.txt", "r");

	if (leEpisodios == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}
	int s = 0;///>Vari�vel que armazena o total de epis�dios de urg�ncia
	int i = 1;
	while (!feof(leEpisodios)) {


		fscanf(leEpisodios, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &a[i].epUrg, &a[i].sns, &a[i].entrada.tm_mday, &a[i].entrada.tm_mon, &a[i].entrada.tm_year, &a[i].estado, &a[i].hospital, &a[i].saida.tm_mday, &a[i].saida.tm_mon, &a[i].saida.tm_year);
		i++;
	}

	s = a[i-1].epUrg;
	fclose(leEpisodios);
	return s;
}

/// <summary>
/// Grava em ficheiro bin�rio e abre novamente de seguida e l� para teste
/// </summary>
/// <param name="a"></param>
/// <param name="total"></param>
void gravaBinario(processoClinico a[], int total) {

	FILE* fbin = fopen("urgen.dat", "wb");

	if (fbin == NULL) {

		printf("Ficheiro n�o encontrado!");
		return 1;
	}

	fwrite(&total, sizeof(total), 1, fbin);
	fwrite(a, sizeof(processoClinico), total, fbin);

	fclose(fbin);

	/*Esta parte foi criada para ler o ficheiro, de forma a testar a grava��o em bin�rio*/
	FILE* fr = fopen("urgen.dat", "rb");

	if (fr == NULL) {

		printf("Ficheiro n�o encontrado!");
		return 1;
	}
	fread(&total, sizeof(total), 1, fr);
	fread(a, sizeof(processoClinico), total, fr);

	for (int i = 1; i <= total; i++) {									/*Necess�rio colocar i a iniciar em 1, uma vez que a primeira posi��o est� ocupada. Vai at� ao limite "total"*/
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\t%d\t%-12s\t%s\n", a[i].epUrg, a[i].sns, a[i].entrada.tm_mday, a[i].entrada.tm_mon, a[i].entrada.tm_year, a[i].estado, a[i].hospital, a[i].saida.tm_mday, a[i].saida.tm_mon, a[i].saida.tm_year, a[i].tempoInterna, a[i].nome, a[i].nomeHosp);
	}

	fclose(fr);
}