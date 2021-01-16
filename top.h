#ifndef A
#define A

#define MAXUTENTES 300
#define MAXURGENCIA 350

#include<stdio.h>
#include<time.h>
#include<locale.h>
#include <string.h>

#pragma warning (disable:4996)					/*Desativar erro "security warning"*/

/// <summary>
/// Defini��o dos tipos de dados associados a cada registo
/// </summary>
typedef struct utente {							/*Registo dos dados de cada utente*/
	unsigned int sns;///<N�mero de SNS
	char nome[20];///<Nome
	unsigned int contacto;///<Contacto
	unsigned int idade;///<Idade
} utente;

typedef struct unidadesSaude {					/*Registo das unidades de sa�de*/
	int codigo;///<C�digo da unidade hospitalar
	char nome[50];///<Nome da unidade hospitalar
	int maxDoentes;///N�mero m�ximo de doentes suportado pelo servi�o
}unidadeSaude;

typedef struct processoClinico {				/*Registo do processo cl�nico do utente*/
	int epUrg;///<N�mero de epis�dio de urg�ncia
	int sns;///<N�mero de SNS do doente admitido
	struct tm entrada;///<Data de entrada
	char estado;///<Motivo de admissao na urg�ncia
	struct tm saida;///<Data de sa�da
	int tempoInterna;///<Tempo de internamento total do doente
	int hospital;///<C�didgo do hospital onde o doente deu entrada
	char nome[50];///<Nome do doente
	char nomeHosp[50];///Nome do Hospital
}processoClinico;

/*FUN��ES UTILIZADAS*/
/** Utentes */


void acrescentaUtente();

void mostraUtente(utente u[], int size);


int verificaSeExiste(int sns);

/** Hospitais */

void mostraHospitais();

void mostraHospital();

/** Epis�dios de urg�ncia */

void criaEpUrg();

int leUrgencia();

void novoEpUrg();

/*Exerc�cios*/

int doentesCovid(); /* Escerc�cio 2*/

int doentesNesteH(int h, struct tm dEntrada, struct tm dSaida); /*Exerc�cio 3*/

int internamentoCresc(); /*Exerc�cio 4,5 e 6*/

int ordenaVagas();	/*Exerc�cio 7*/

int insereDoente();

/*Final*/
void tabela();

int mostraUrgencia(processoClinico episodio[]);

int converteTempo(processoClinico a[], int b);

void encontraNome(processoClinico a[], int b);

void encontraHospital(processoClinico a[], int b);

int contaEpisodios(processoClinico a[], int b);

void gravaBinario(processoClinico a[], int total);

#endif // !A

