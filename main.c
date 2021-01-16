/*****************************************************************//**
 * \file   main.c
 * \brief  Trabalho de PI.
 * 
 * Criação de solução para responder a problemas concretos em gestão de doentes que entram em unidades de saúde no âmbito da pandemia COVID19.
 * 
 * \author Sérgio Martins
 * \e-mail mailto:a20871@alunos.ipca.pt
 * \date   January 2021
 *********************************************************************/
#include "top.h"

/// <summary>
/// Função main para chamar e testar cada função do exercício.
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
	//printf("\nO total de doentes COVID que passaram por estas unidades de saúde é: %d\n", doentesCovid());


#pragma endregion Questao2

#pragma region Questao 3

	//
	//int hosp = 1;///<Definição do código que o utilizador pretende

	//struct tm dEntrada;///<Definição da data de entrada que o utilizador pretende
	//dEntrada.tm_mday = 27;
	//dEntrada.tm_mon = 12;
	//dEntrada.tm_year = 2020;

	///*Conversão da data de Entrada*/
	//dEntrada.tm_mon = (dEntrada.tm_mon - 1);
	//dEntrada.tm_year = (dEntrada.tm_year-1900);

	//struct tm dSaida;///<Definição da data de saída que o utilizador pretende
	//dSaida.tm_mday = 31;
	//dSaida.tm_mon = 1;
	//dSaida.tm_year = 2021;

	///*Conversão da data de Saida*/
	//dSaida.tm_mon = (dSaida.tm_mon - 1);
	//dSaida.tm_year = (dSaida.tm_year - 1900);

	///*Variável que vai armazenar o número de doentes acumulados*/
	//int nDoentes =	doentesNesteH(hosp, dEntrada, dSaida);

	//printf("Doentes que deram entrada no Hospital de Barcelos entre %d-%d-%d e %d-%d-%d é %d.\n", dEntrada.tm_mday, dEntrada.tm_mon+1, dEntrada.tm_year+1900, dSaida.tm_mday, dSaida.tm_mon+1, dSaida.tm_year+1900, nDoentes);

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

