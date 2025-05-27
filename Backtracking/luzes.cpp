#include <bits/stdc++.h>
using namespace std;


int main() 
{
    int max, num, holofote, qntd;
    vector<bitset<32>> padroes_distintos;

    cin >> max >> num;  // max de holofotes e números de casos
    cin >> holofote;


    for (int i = 0; i < num; i++) 
    {
        cin >> qntd; 

        bitset<32> padrao_atual;    // cria um sequência binária para cada linha 
        for(int j = 0; j < qntd; j++) 
        {            
            int ligado;
            cin >> ligado; 
            padrao_atual[ligado] = 1;   // baseado em uma sequência binária, marca aquele bit como válido
        }
        padroes_distintos.push_back(padrao_atual);  // adiciona a sequência no vetor
    }

    // ordena o vetor para podermos excluir depois com o iterador retornado pelo método unique, porém,
    // o compilador está dando uma sobrecarga quando é usado a comparação "< operador", então quando eu tentava usar um
    // set para gerar conjuntos distintos, dava erro, mudei a abordagem para usar vector e depois o erro continuou em sort,
    // foi quando entendi que o problema era na questão do "< operadoruma", para arrumar e ser possível fazer a ordenação
    // usei uma lambda (função anônima) para reformular a função sort. Agora ele converte os bitsets para string e faz a comparação. 
    sort(padroes_distintos.begin(), padroes_distintos.end(),
        [](bitset<32>& a, bitset<32>& b) 
        {
            return a.to_string() < b.to_string();
        }
    );

    // a função unique, retorna o iterador para o "novo fim" da lista, ele coloca os valores distintos nos primeiros índices 
    // da lista e retorna o iterador que aponta para o começo das duplicatas.  
    auto it_novo_fim = unique(padroes_distintos.begin(), padroes_distintos.end());

    // como eu sei onde começa as duplicatas, eu apago daquele iterador até o iterador de fim da lista.
    padroes_distintos.erase(it_novo_fim, padroes_distintos.end());

    cout << "Número de padrões distintos: " << padroes_distintos.size() << "\n";
    
    int cont = 0;
    
    for(auto &luz : padroes_distintos)
    {
        if(luz[holofote] == 1) cont++;
    }

    cout << "Quantidade de ocorrências do holofote " << holofote << ": " << cont << "\n";

    bitset<32> padrao_maior;
    int maior = 0;

    for(auto &luzes : padroes_distintos)
    {
        if(luzes.count() > maior) 
        {
            maior = luzes.count();
            padrao_maior = luzes; 
        }
    }


    for(int i = 0; i < 32; i++) 
    {
        if(padrao_maior[i] == 1) cout << i << " ";
    
    }
    cout << "\n";
    return 0;
}