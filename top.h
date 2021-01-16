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
/// Definição dos tipos de dados associados a cada registo
/// </summary>
typedef struct utente {							/*Registo dos dados de cada utente*/
	unsigned int sns;///<Número de SNS
	char nome[20];///<Nome
	unsigned int contacto;///<Contacto
	unsigned int idade;///<Idade
} utente;

typedef struct unidadesSaude {					/*Registo das unidades de saúde*/
	int codigo;///<Código da unidade hospitalar
	char nome[50];///<Nome da unidade hospitalar
	int maxDoentes;///Número máximo de doentes suportado pelo serviço
}unidadeSaude;

typedef struct processoClinico {				/*Registo do processo clínico do utente*/
	int epUrg;///<Número de episódio de urgência
	int sns;///<Número de SNS do doente admitido
	struct tm entrada;///<Data de entrada
	char estado;///<Motivo de admissao na urgência
	struct tm saida;///<Data de saída
	int tempoInterna;///<Tempo de internamento total do doente
	int hospital;///<Códidgo do hospital onde o doente deu entrada
	char nome[50];///<Nome do doente
	char nomeHosp[50];///Nome do Hospital
}processoClinico;

/*FUNÇÔES UTILIZADAS*/
/** Utentes */


void acrescentaUtente();

void mostraUtente(utente u[], int size);


int verificaSeExiste(int sns);

/** Hospitais */

void mostraHospitais();

void mostraHospital();

/** Episódios de urgência */

void criaEpUrg();

int leUrgencia();

void novoEpUrg();

/*Exercícios*/

int doentesCovid(); /* Escercício 2*/

int doentesNesteH(int h, struct tm dEntrada, struct tm dSaida); /*Exercício 3*/

int internamentoCresc(); /*Exercício 4,5 e 6*/

int ordenaVagas();	/*Exercício 7*/

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

