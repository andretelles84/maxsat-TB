#include <iostream>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <ctype.h>
#include <ctime>

using namespace std;

void solucaoInicial(int X, int Y);
void redimensiona(int X, int Y);
void satClausulas(int n, int m);
int totalClausulasSatisfeitas();

//Debug
void imprimeMatriz();
void imprimeVariaveis();
void imprimeClausulas();

vector<int> variaveis;	//Vetor de variaveis
vector<int> clausulas;	//Vetor de clausulas

//Matriz de pertencimento das variáveis às clausulas
vector<vector<int> > matriz;
