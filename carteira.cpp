#include "carteira.h"
#include "moeda.h"
#include <iomanip>
#include <fstream>

using namespace std;

Carteira::Carteira(Moeda moeda) : moedaPadrao(moeda) {}

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
    ofstream arquivo(nomeArquivo);
    
    if (arquivo.is_open()) {
        arquivo << moedaPadrao.codigo << endl;
        
        for (const auto& [sigla, quantidade] : moedas) {
            arquivo << sigla << " " << quantidade << endl;
        }
        
        arquivo.close();
    } else {
        cout << "Erro: Nao foi possivel abrir o arquivo para salvar os dados." << endl;
    }
}

void Carteira::definirMoedaPadrao(Moeda moeda){
    this->moedaPadrao = moeda;
}

void Carteira::depositar(string codigo, int quantidade) {
    moedas[codigo] += quantidade;
    cout << "Deposito realizado com sucesso!" << endl;
    this->exibirSaldoMoeda(codigo);
}

bool Carteira::sacar(string codigo, int quantidade) {
    if (moedas.find(codigo) == moedas.end()) {
        cout << "Erro: Voce nao possui a moeda " << codigo << " na carteira." << endl;
        return false;
    }

    if (moedas[codigo] < quantidade) {
        cout << "Erro: Saldo insuficiente. Saldo atual: " << moedas[codigo] << " " << codigo << endl;
        return false;
    }

    moedas[codigo] -= quantidade;
    
    if (moedas[codigo] == 0) {
        moedas.erase(codigo);
        cout << "O saldo de " << codigo << " foi zerado. Moeda removida da carteira." << endl;
    } else {
        cout << "Saque realizado com sucesso!" << endl;
        this->exibirSaldoMoeda(codigo);
    }

    return true;
}

void Carteira:: exibirSaldoMoeda(string codigo){
    cout << "Saldo atualizado: " << moedas[codigo] << " " << codigo << endl;
}

void Carteira:: imprimirPosicaoMoedaUnica(string moeda, int quantidade){
    cout << left << setw(10) << moeda << right << setw(15) << quantidade << endl;
}

void Carteira:: listarPosicao() {
    cout << "====LISTANDO POSICOES NA CARTEIRA====" << endl;
    cout << left << setw(10) << "Ativo" << right << setw(15) << "Quantidade" << endl;

    for (const auto&[nomeMoeda, quantidade]: moedas){
        imprimirPosicaoMoedaUnica(nomeMoeda, quantidade);
    }   
}