/*****************************************************************//**
 * \file   main.c
 * \brief  Trabalho de PI.
 * 
 * Cria��o de solu��o para responder a problemas concretos em gest�o de doentes que entram em unidades de sa�de no �mbito da pandemia COVID19.
 * 
 * \author S�rgio Martins
 * \e-mail mailto:a20871@alunos.ipca.pt
 * \date   January 2021
 *********************************************************************/
#include "top.h"

/// <summary>
/// Fun��o main para chamar e testar cada fun��o do exerc�cio.
/// </summary>
int main() {

	setlocale(LC_ALL, "");

	utente utentes[MAXUTENTES];

	int size = MAXUTENTES;

#pragma region Questao1
	//mostraUtente(utentes, size);

	//acrescentaUtente();

	//mostraHospitais();

	//leUrgencia();
#pragma endregion Questao1

#pragma region Questao2

	//
	//printf("\nO total de doentes COVID que passaram por estas unidades de sa�de �: %d\n", doentesCovid());


#pragma endregion Questao2

#pragma region Questao 3

	//
	//int hosp = 1;///<Defini��o do c�digo que o utilizador pretende

	//struct tm dEntrada;///<Defini��o da data de entrada que o utilizador pretende
	//dEntrada.tm_mday = 27;
	//dEntrada.tm_mon = 12;
	//dEntrada.tm_year = 2020;

	///*Convers�o da data de Entrada*/
	//dEntrada.tm_mon = (dEntrada.tm_mon - 1);
	//dEntrada.tm_year = (dEntrada.tm_year-1900);

	//struct tm dSaida;///<Defini��o da data de sa�da que o utilizador pretende
	//dSaida.tm_mday = 31;
	//dSaida.tm_mon = 1;
	//dSaida.tm_year = 2021;

	///*Convers�o da data de Saida*/
	//dSaida.tm_mon = (dSaida.tm_mon - 1);
	//dSaida.tm_year = (dSaida.tm_year - 1900);

	///*Vari�vel que vai armazenar o n�mero de doentes acumulados*/
	//int nDoentes =	doentesNesteH(hosp, dEntrada, dSaida);

	//printf("Doentes que deram entrada no Hospital de Barcelos entre %d-%d-%d e %d-%d-%d � %d.\n", dEntrada.tm_mday, dEntrada.tm_mon+1, dEntrada.tm_year+1900, dSaida.tm_mday, dSaida.tm_mon+1, dSaida.tm_year+1900, nDoentes);

#pragma endregion Questao3

#pragma region Questao456
	//internamentoCresc();
#pragma endregion Questao456

#pragma region Questao7
	//ordenaVagas();
#pragma endregion Questao7

#pragma region Questao8	
	//mostraHospital();
#pragma endregion Questao8

#pragma region Questao9
	//tabela();
#pragma endregion Questao9

#pragma region Questao10
	insereDoente();
#pragma endregion Questao10
}

