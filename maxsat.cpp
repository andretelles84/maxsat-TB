#include "maxsat.h"

int main() {

	clock_t begin, end;

	int X, Y;	//Total de variaveis "X" e total de clausulas "Y"
	int entrada;
	string linha, descarte;
	double elapsed_secs;

	begin = clock();

	//Laço para ler os valores
	while (getline(cin,linha)) {
		if (linha[0] == 'p'){
			istringstream iss(linha);
			iss >> descarte >> descarte >> X >> Y;
			break;
			
		}
	}

	//Redimensiona os vetores e a matriz
	redimensiona(X,Y);

	//Le o restante do arquivo para popular a matriz
	for (int j = 0; j < Y; ++j){
		getline(cin,linha);
		istringstream iss(linha);
		while(iss >> entrada){
			if(entrada == 0){
			 break;
			}
			matriz[abs(entrada)-1][j] = entrada/abs(entrada);
		}
	}


	//Solução Inicial para o valor das clausulas
	solucaoInicial(X,Y);

	satClausulas(X,Y);
	

	//Calcula tempo decorrido
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//Saídas

	cout << "Este problema tem " << X << " variaveis e " << Y << " clausulas." << endl;

	//imprimeMatriz();	//DEBUG
	//imprimeVariaveis();	//DEBUG
	//imprimeClausulas();	//DEBUG

	cout << "Clausulas satisfeitas: " << totalClausulasSatisfeitas() << "." << endl;
	cout << "Tempo decorrido: " << elapsed_secs << "s." << endl;

	return 0;
		
}

// Calcula a solucao inicial, caso a variavel ocorra mais vezes 
void solucaoInicial(int n, int m){
	//Contabiliza as ocorrencias da variavel
	for (int i = 0; i < n; ++i){
		variaveis[i] = 0;
		for (int j = 0; j < m; ++j){
			variaveis[i] += matriz[i][j];
		}
		if(variaveis[i] > 0){
			variaveis[i] = 1;
		}
		else{
			variaveis[i] = 0;
		}
	}
}

//Verifica a satisfabilidade de todas as clausulas
void satClausulas(int n, int m){
	//Descomente as linhas DEBUG para imprimir a operação OR
	for (int j = 0; j < m; ++j){
		clausulas[j] = 0;
		//cout << "Clausula: [" << j+1 << "] ";	//DEBUG
		for (int i = 0; i < n; ++i){
			if(matriz[i][j] == 1) {
				//cout << " X[" << i+1 << "]:" << variaveis[i] << " ";	//DEBUG
				clausulas[j] |= variaveis[i];
			}
			else if (matriz[i][j] == -1){
				//cout << " X~[" << i+1 << "]:" << variaveis[i] << " ";	//DEBUG
				clausulas[j] |= (1-variaveis[i]);
			}
		}
		//cout << " com valor: " << clausulas[j] << endl;	//DEBUG
	}
}

//Redimensiona Vetores e Matriz globais
void redimensiona(int n, int m){
	variaveis.resize(n);
	clausulas.resize(m);
	matriz.resize(n);
	for (int i = 0; i < n; ++i){
		matriz[i].resize(m);
	}
}

//Calcula o total de clausulas satisfeitas
int totalClausulasSatisfeitas(){
	int resposta = 0;
	for (int j = 0; j < clausulas.size(); ++j){
		resposta += clausulas[j];
	}
	return resposta;
}

//Imprime a matriz de pertencimento
void imprimeMatriz(){
	cout << "Representacao em matriz das entradas " << endl;

	for (int j = 0; j < matriz[0].size(); ++j){
		for (int i = 0; i < matriz.size(); ++i){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Fim da matriz" << endl;
}

// Imprime o valor armazenado nas variáveis
void imprimeVariaveis(){
	cout << "Valor das variaveis" << endl;

	for (int i = 0; i < variaveis.size(); ++i){
		cout << "Variavel [" << i+1 << "]:" << variaveis[i] << endl;
		
	}
		
	cout << "Fim das variaveis" << endl;
}

// Imprime o valor armazenado nas Clausulas
void imprimeClausulas(){
	cout << "Valor das Clausulas" << endl;

	for (int j = 0; j < clausulas.size(); ++j){
		cout << "Clausula [" << j+1 << "]:" << clausulas[j] << endl;
		
	}
		
	cout << "Fim das clausulas" << endl;
}
