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
	unsigned int sns;
	char nome[20];
	unsigned int contacto;
	unsigned int idade;
} utente;

typedef struct unidadesSaude {					/*Registo das unidades de sa�de*/
	int codigo;
	char nome[50];
	int maxDoentes;

}unidadeSaude;

typedef struct processoClinico {				/*Registo do processo cl�nico do utente*/
	int epUrg;
	int sns;
	struct tm entrada;
	char estado;
	struct tm saida;
	int tempoInterna;
	int hospital;
	char nome[50];
	char nomeHosp;

}processoClinico;



/*FUN��ES UTILIZADAS*/
/** Utentes */
void novoUtente();

void acrescentaUtente();

void mostraUtente(utente u[], int size);

void acrescentaNovoUtente(utente u);

int verificaSeExiste(int sns);

/** Hospitais */

int mostraHospitais();


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

#endif // !A

