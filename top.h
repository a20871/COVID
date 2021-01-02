#ifndef A
#define A

#define MAXUTENTES 300

#include<stdio.h>
#include<time.h>
#include<locale.h>

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
	char codigo[3];
	char nome[50];
	int maxDoentes;

}unidadeSaude;

typedef struct processoClinico {				/*Registo do processo cl�nico do utente*/
	int epUrg;
	int sns;
	char estado[2];
	int entrada;
	int saida;
	int tempoInterna;

}processoClinico;

/*FUN��ES UTILIZADAS*/

void novoUtente();


void acrescentaUtente();

#endif // !A

