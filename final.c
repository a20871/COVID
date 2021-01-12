#include "top.h"

void tabela() {

	processoClinico ep[MAXUTENTES];
	int nRegistos = 0;
	mostraUrgencia(ep);

	
	printf("total %d e o registo sns6 é %d com %d dias.\n", nRegistos, ep[6].sns, ep[6].tempoInterna);

}


/**
 * Função que mostra os registos da urgência pretendida.
 * 
 * \param episodio
 * \return 
 */
int mostraUrgencia(processoClinico episodio[]) {

	
	FILE* leUrgencia = fopen("urgencias.txt", "r");

	if (leUrgencia == NULL) {
		printf("Erro ao ler ficheiro.\n");
	}

	int i = 1;
	while (!feof(leUrgencia)) {


		fscanf(leUrgencia, "%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\n", &episodio[i].epUrg, &episodio[i].sns, &episodio[i].entrada.tm_mday, &episodio[i].entrada.tm_mon, &episodio[i].entrada.tm_year, &episodio[i].estado, &episodio[i].hospital, &episodio[i].saida.tm_mday, &episodio[i].saida.tm_mon, &episodio[i].saida.tm_year);
		converteTempo(episodio, i);
		encontraNome(episodio, i);
		encontraHospital(episodio, i);
		
		printf("%d\t%d\t%d-%d-%d\t%c\t%d\t%d-%d-%d\t%d\t%s\t%s\n", episodio[i].epUrg, episodio[i].sns, episodio[i].entrada.tm_mday, episodio[i].entrada.tm_mon, episodio[i].entrada.tm_year, episodio[i].estado, episodio[i].hospital, episodio[i].saida.tm_mday, episodio[i].saida.tm_mon, episodio[i].saida.tm_year, episodio[i].tempoInterna, episodio[i].nome, episodio[i].nomeHosp);
		
		
		
		i++;
		
	}
	
	

	fclose(leUrgencia);
	
}

/**
 * Função que calcula o tempo de internamento.
 * 
 * \param a array de processos clínicos
 * \param b constante do respetivo array.
 * \return 
 */
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
	
	double diffSecs = difftime(tSaida, tEntrada);		/*Cálculo do tempo de internamento*/
	double day = (diffSecs / 86400);
	int dias = (int)day;


	if (diffSecs < 0) {
		a[b].tempoInterna = 0;
	}
	else {
		a[b].tempoInterna = dias;
	}

	/*Reverte a data para o formato inicial*/
	a[b].entrada.tm_year = (a[b].entrada.tm_year + 1900);
	a[b].entrada.tm_mon = (a[b].entrada.tm_mon + 1);

	a[b].saida.tm_year = (a[b].saida.tm_year + 1900);
	a[b].saida.tm_mon = (a[b].saida.tm_mon + 1);


}

/**
 * Encontra o nome referente a um número sns da lista de utentes e copia-o para o registo da urgência.
 * 
 * \param a ->processo clínico da urgência
 * \param b ->indice do array
 */
void encontraNome(processoClinico a[], int b) {

	FILE* apf = fopen("utentes.txt", "r");
	utente doentRegistos[MAXUTENTES];

	int n = 0;
	while (!feof(apf)) {
		fscanf(apf, "%d\t%s\t%d\t%d",&doentRegistos[n].sns, &doentRegistos[n].nome, &doentRegistos[n].contacto, &doentRegistos[n].idade);
		n++;
	}

	

	int snsPretendido = 0;
	snsPretendido = a[b].sns;

	for (int m = 0; m < n - 1; m++) {
		if (snsPretendido == doentRegistos[m].sns) {
			strcpy(a[b].nome, doentRegistos[m].nome);
			}
		
	}
	
	fclose(apf);

}

void encontraHospital(processoClinico a[], int b) {

	FILE* aph = fopen("hospitais.txt", "r");
	unidadeSaude h[4];

	int n = 0;
	while (!feof(aph)) {
		fscanf(aph, "%d\t%[^\t]\t\t%d", &h[n].codigo, &h[n].nome, &h[n].maxDoentes);
		n++;
	}

	int codPretendido = 0;
	codPretendido = a[b].hospital;

	for (int m = 0; m < n - 1; m++) {
		if (codPretendido == h[m].codigo) {
			strcpy(a[b].nomeHosp, h[m].nome);
		}

	}


	fclose(aph);

}