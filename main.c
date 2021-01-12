/*****************************************************************//**
 * \file   main.c
 * \brief  
 * 
 * \author martins
 * \date   January 2021
 *********************************************************************/
#include "top.h"

int main() {

	setlocale(LC_ALL, "");

	utente utentes[MAXUTENTES];

	int size = MAXUTENTES;

	//novoUtente();
	//acrescentaUtente();






	//mostraUtente(utentes, size);

	//mostraHospitais();


	//criaEpUrg();
	//leUrgencia();
	//novoEpUrg();



#pragma region Questao2


	/*Questão 2-Apresenta doentes COVID*/
	//printf("Doentes COVID: %d\n", doentesCovid());


#pragma endregion Questao2
#pragma region Questao 3
	//
	///*Questão 3 - Números de doentes que deram entrada num determinado hospital entre determinada data*/
	//int hosp = 1; /*Hospital de Barcelos*/

	//struct tm dEntrada;
	//dEntrada.tm_mday = 27;
	//dEntrada.tm_mon = 12;
	//dEntrada.tm_year = 2020;

	///*Conversão da data*/
	//dEntrada.tm_mon = (dEntrada.tm_mon - 1);
	//dEntrada.tm_year = (dEntrada.tm_year-1900);

	//struct tm dSaida;
	//dSaida.tm_mday = 31;
	//dSaida.tm_mon = 1;
	//dSaida.tm_year = 2021;

	///*Conversão da data*/
	//dSaida.tm_mon = (dSaida.tm_mon - 1);
	//dSaida.tm_year = (dSaida.tm_year - 1900);

	//int nDoentes =	doentesNesteH(hosp, dEntrada, dSaida);

	//printf("Doentes que deram entrada no Hospital de Barcelos entre %d-%d-%d e %d-%d-%d é %d.\n", dEntrada.tm_mday, dEntrada.tm_mon+1, dEntrada.tm_year+1900, dSaida.tm_mday, dSaida.tm_mon+1, dSaida.tm_year+1900, nDoentes);
#pragma endregion Questao3
#pragma region Questao456

	/*Questão 4,5 e 6- Listagem de doentes, ordenada por ordem decrescente de tempo (de internamento?) desde o momento em que deu entrada até que teve alta;
	* Cálculo da média de dias de internamento.
	* Apresentação do doente que esteve mais tempo internado*/

	//internamentoCresc();
#pragma endregion Questao456
#pragma region Questao7
	/*Questão 7 - Listagem de vagsa disponíveis em cada hospital por ordem crescente*/
	//ordenaVagas();
#pragma endregion Questao7
#pragma region Questao8
	//insereDoente();

#pragma endregion Questao8

	//acrescentaUtente();

	tabela();
}

