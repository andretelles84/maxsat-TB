#include "maxsat.h"

int main() {

	clock_t begin, end;

	int X, Y;	//Total de variaveis "X" e total de clausulas "Y"
	int entrada, solucao;
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
	solucaoInicial();

	candidato = variaveisB;

	satClausulas();

	listaCandidatos();

	testaCandidatos();
	

	//Calcula tempo decorrido
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//Saídas

	cout << "Este problema tem " << X << " variaveis e " << Y << " clausulas." << endl;

	//imprimeMatriz();	//DEBUG
	//imprimeVariaveis();	//DEBUG
	//imprimeClausulas();	//DEBUG
	listaCandidatos();

	solucao = totalClausulasSatisfeitas();

	cout << "Clausulas satisfeitas: " << solucao << "." << endl;
	cout << "Tempo decorrido: " << elapsed_secs << "s." << endl;

	return 0;
		
}

// Calcula a solucao inicial, caso a variavel ocorra mais vezes 
void solucaoInicial(){
	int soma;

	//Contabiliza as ocorrencias da variavel
	for (int i = 0; i < matriz.size(); ++i){
		soma = 0;
		for (int j = 0; j < matriz[0].size(); ++j){
			soma += matriz[i][j];
		}
		if(soma > 0){
			variaveisB[i] = 1;
		}
		else{
			variaveisB[i] = 0;
		}
	}
}

//Verifica a satisfabilidade de todas as clausulas
void satClausulas(){
	//Descomente as linhas DEBUG para imprimir a operação OR
	for (int j = 0; j < matriz[0].size(); ++j){
		clausulasB[j] = 0;
		//cout << "Clausula: [" << j+1 << "] ";	//DEBUG
		for (int i = 0; i < matriz.size(); ++i){
			if(matriz[i][j] == 1) {
				//cout << " X[" << i+1 << "]:" << variaveisB[i] << " ";	//DEBUG
				clausulasB[j] = clausulasB[j] | candidato[i];
			}
			else if (matriz[i][j] == -1){
				//cout << " X~[" << i+1 << "]:" << variaveisB[i] << " ";	//DEBUG
				clausulasB[j] = clausulasB[j] | !candidato[i];
			}
		}
		//cout << " com valor: " << clausulas[j] << endl;	//DEBUG
	}
}

//Redimensiona Vetores e Matriz globais
void redimensiona(int n, int m){
	//variaveis.resize(n);
	//clausulas.resize(m);

	variaveisB.resize(n);
	clausulasB.resize(m);

	matriz.resize(n);
	for (int i = 0; i < n; ++i){
		matriz[i].resize(m);
	}
}

//Calcula o total de clausulas satisfeitas
int totalClausulasSatisfeitas(){
	int resposta = 0;
	for (int j = 0; j < clausulasB.size(); ++j){
		resposta += clausulasB[j];
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

	for (int i = 0; i < variaveisB.size(); ++i){
		cout << "Variavel [" << i+1 << "]:" << variaveisB[i] << endl;
		
	}
		
	cout << "Fim das variaveis" << endl;
}

// Imprime o valor armazenado nas Clausulas
void imprimeClausulas(){
	cout << "Valor das Clausulas" << endl;

	for (int j = 0; j < clausulasB.size(); ++j){
		cout << "Clausula [" << j+1 << "]:" << clausulasB[j] << endl;
		
	}
		
	cout << "Fim das clausulas" << endl;
}

//Gera a lista de variáveis pertencentes a clausulas de resultado 0
void listaCandidatos(){
	set<int>::iterator it;
	candidatos.clear();
	for (int j = 0; j < clausulasB.size(); ++j){
		if(clausulasB[j] == 0){
			//cout << "Clausula negada:" << j+1 << "vars:";	//DEBUG
			for (int i = 0; i < matriz.size(); ++i){
				if( (matriz[i][j] == 1) || (matriz[i][j] == -1) ){
					//cout << i+1 << " ";	//DEBUG
					candidatos.insert(i+1);
				}
			}
			//cout << endl;	//DEBUG
		}

	}
	//DEBUG
	/*for(it=candidatos.begin(); it!=candidatos.end(); ++it){
		cout << *it << " ";
	}*/
}

//Gera uma solução candidata a partir da atual solução, alterando APENAS uma variável
void geraCandidato(int var){
	candidato = variaveisB;
	candidato[var-1] = !candidato[var-1];
}

//Testa se o candidato é o melhor dos candidatos atuais
void testaCandidatos(){
	set<int>::iterator it;
	int solucao;

	int melhorSolucao = totalClausulasSatisfeitas();
	for(it=candidatos.begin(); it!=candidatos.end(); ++it){
		geraCandidato(*it);
		satClausulas();
		solucao = totalClausulasSatisfeitas();
		if(solucao > melhorSolucao){
			melhorCandidato = candidato;
			melhorSolucao = solucao;
			cout << "Solucao melhor: "<< melhorSolucao << endl;
		}
	}
	
}
