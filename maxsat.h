#include <iostream>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <ctype.h>
#include <ctime>
#include <set>

using namespace std;

void solucaoInicial();
void satClausulas();
void redimensiona(int n, int m);
int totalClausulasSatisfeitas();

//Debug
void imprimeMatriz();
void imprimeVariaveis();
void imprimeClausulas();

//Tabu
void listaCandidatos();
void geraCandidato(int var);
void testaCandidatos();


//Variaveis Globais
//vector<int> variaveis;		//Vetor de variaveis
//vector<int> clausulas;		//Vetor de clausulas

vector<bool> variaveisB;	//Vetor booleano de variaveis
vector<bool> clausulasB;	//Vetor booleano de clausulas

vector<bool> candidato;		//Vetor de variaveis do candidato em análise
vector<bool> melhorCandidato;	//Vetor de variaveis do melhor candidato
vector<bool> melhor;		//Vetor de variaveis do melhor caso

set<int> candidatos;		//Conjunto de variáveis pertencentes às clausulas não satisfeitas (candidatas a troca de valor)

//Matriz de pertencimento das variáveis às clausulas
vector<vector<int> > matriz;
