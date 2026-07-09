#include "carteira.h"
#include "moeda.h"
#include <iomanip>
#include <fstream>

using namespace std;

bool Carteira::carregarDados(string nomeArquivo, Mercado& mercado) {
    ifstream arquivo(nomeArquivo); 
    
    if (arquivo.is_open()) {
        string siglaPadrao;
        
        if (arquivo >> siglaPadrao) {
            this->definirMoedaPadrao(mercado.obterMoeda(siglaPadrao));
        }
        
        string sigla;
        int quantidade;
        while (arquivo >> sigla >> quantidade) {
            moedas[sigla] = quantidade;
        }
        
        arquivo.close();
        return true; 
    }
    
    return false; 
}

void Carteira::salvarDados(string nomeArquivo) {
    ofstream arquivo(nomeArquivo); // Abre o arquivo para escrita (cria se não existir)
    
    if (arquivo.is_open()) {
        // 1. Salva a moeda padrão na primeira linha
        arquivo << moedaPadrao.nome << endl;
        
        // 2. Salva as moedas da carteira (Sigla e Quantidade separadas por espaço)
        for (const auto& [sigla, quantidade] : moedas) {
            arquivo << sigla << " " << quantidade << endl;
        }
        
        arquivo.close();
    } else {
        cout << "Erro: Nao foi possivel abrir o arquivo para salvar os dados." << endl;
    }
}

void Carteira:: definirMoedaPadrao(Moeda moedaPadrao){
    moedaPadrao = moedaPadrao;
};

void Carteira:: imprimirPosicaoMoedaUnica(string moeda, int quantidade){
    cout << left << setw(10) << moeda << right << setw(15) << quantidade << endl;
};

void Carteira:: listarPosicao() {
    cout << "====LISTANDO POSICOES NA CARTEIRA====" << endl;
    cout << left << setw(10) << "Ativo" << right << setw(15) << "Quantidade" << endl;

    for (const auto&[nomeMoeda, quantidade]: moedas){
        imprimirPosicaoMoedaUnica(nomeMoeda, quantidade);
    }   
};