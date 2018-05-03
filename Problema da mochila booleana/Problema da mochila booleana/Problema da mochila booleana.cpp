// Problema da mochila booleana.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include<algorithm>

std::ifstream arquivo;

struct item {
	int peso;
	int valor;
};

struct calculo {
	int num;
	bool usa;
	int total;
};

std::vector<item> itens;
int numItens;
int tamMochila;

std::vector<std::vector<calculo>> tabelaOfi;

void iniTabela() {
	for (int i = 0; i <= numItens; i++) {
		tabelaOfi[i][0].num = 0;
		tabelaOfi[i][0].usa = 0;
		tabelaOfi[i][0].total = 0;
	}
	for (int i = 0; i <= tamMochila; i++) {
		tabelaOfi[numItens][i].num = 0;
		tabelaOfi[numItens][i].usa = 0;
		tabelaOfi[numItens][i].total = 0;

	}
}

void mochilaInteira() {
	for (int i = numItens - 1; i >= 0; i--) {
		for (int j = 1; j <= tamMochila; j++) {
			if (j - itens[i].peso < 0) {
				tabelaOfi[i][j].num = tabelaOfi[i + 1][j].num;
				tabelaOfi[i][j].usa = 0;
				tabelaOfi[i][j].total = tabelaOfi[i][j].num - tabelaOfi[i][j].usa;
			}
			else {
				if (tabelaOfi[i + 1][j].num > (tabelaOfi[i + 1][j - itens[i].peso].num + itens[i].valor)) {
					tabelaOfi[i][j].num = tabelaOfi[i + 1][j].num;
					tabelaOfi[i][j].usa = 0;
					tabelaOfi[i][j].total = tabelaOfi[i][j].num - tabelaOfi[i][j].usa;
				}
				else {
					tabelaOfi[i][j].num = tabelaOfi[i + 1][j - itens[i].peso].num + itens[i].valor;
					tabelaOfi[i][j].usa = 1;
					tabelaOfi[i][j].total = tabelaOfi[i][j].num - tabelaOfi[i][j].usa;

				}
			}
		}
	}
}

int main(){
	std::string arquivoname;
	std::cout << "Problema da Mochila:" << std::endl << "Digite o nome do arquivo(ex. exemplo.txt): ";
	std::cin >> arquivoname;

	arquivo.open(arquivoname.data());
	if (!arquivo.is_open()) {
		system("pause");
		return -1;
	}
	item aux;
	std::string stringer, aux1, aux2;
	std::stringstream a;
	std::getline(arquivo, stringer);
	a << stringer;
	a >> aux1 >> aux2;
	numItens = std::stoi(aux1);
	tamMochila = std::stoi(aux2);
	while (!arquivo.eof()) {
		std::stringstream b;
		std::getline(arquivo, stringer);
		b << stringer;
		b >> aux1 >> aux2;
		aux.peso = std::stoi(aux1);
		aux.valor = std::stoi(aux2);
		itens.push_back(aux);
	}

	tabelaOfi.resize(numItens+1);
	for (int i = 0; i <= numItens; i++) {
		tabelaOfi[i].resize(tamMochila+1);
	}
	iniTabela();
	mochilaInteira();

	std::cout << tabelaOfi[0][tamMochila].total << std::endl;
	system("pause");
	return 0;
}

