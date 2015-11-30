Max-SAT com Busca Tabu

Projeto da disciplina de Otimização Combinatória - 2015/2
Prof. Marcus Ritt


Comando para compilar:
g++ maxsat.cpp -o maxsat

Exemplo de comando para rodar o programa:
./maxsat < ./teste/uf175-053.cnf > teste.out
[programa < arquivo de entrada > arquivo de saida]

TODO
Pseudo-Código da Busca Tabu:

s ← s0
sBest ← s
tabuList ← []
while (not stoppingCondition())
	candidateList ← []
	bestCandidate ← null
	for (sCandidate in sNeighborhood)
		if ( (not tabuList.contains(sCandidate)) and (fitness(sCandidate) > fitness(bestCandidate)) )
			bestCandidate ← sCandidate
		end
	end
	s ← bestCandidate
	if (fitness(bestCandidate) > fitness(sBest))
		sBest ← bestCandidate
	end
	tabuList.push(bestCandidate);
	if (tabuList.size > maxTabuSize)
		tabuList.removeFirst()
	end
end
return sBest
