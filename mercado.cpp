#include "mercado.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>

using namespace std;

Mercado::Mercado() {

    //PROVISÓRIO -- Chamar aqui a api de listar moedas pra preencher o valor do atributo do mercado
    listarMoedas();
}

void Mercado::listarMoedas() {
    // limpa o vetor antes de preencher caso seja chamado mais de uma vez
    moedasMercado.clear();

    // comando para rodar o python passando o argumento listar
    //No Windows utilizar apenas python e no Linux utilizar python3
    string comando = "python api.py getMoedasDisponiveis";
    
    // abre um pipe para ler a saida do python
    //abre um fork child sendo o processo do python e o processo pai continua a execucao do programa (c++)
    // Usando _popen para abrir no windows, se fosse linux seria so popen
    FILE* pipe = _popen(comando.c_str(), "r");
    
    if (!pipe) {
        cout << "erro ao abrir o script de integracao externo." << endl;
        return;
    }
    
    char buffer[256];
    // le a saida do python linha por linha
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        string linha(buffer);
        
        // remove a quebra de linha do final se existir
        if (!linha.empty() && linha.back() == '\n') {
            linha.pop_back();
        }
        
        // divide a string usando o caractere , como separador
        stringstream ss(linha);
        string codigo;
        string nome;
        
        if (getline(ss, codigo, ',') && getline(ss, nome, ',')) {
            // criamos a moeda com valor inicial zero pois a listagem nao contem preco
            Moeda novaMoeda(nome, codigo);
            moedasMercado.push_back(novaMoeda);
        }
    }
    
    // fecha o pipe 
    _pclose(pipe);
    
    if (moedasMercado.empty()) {
        cout << "nenhuma moeda disponivel no mercado ou erro de conexao." << endl;
    }
}

bool Mercado::validarMoeda(string codigoPassado) {
    for (const auto& moeda : moedasMercado) {
        if (moeda.codigo == codigoPassado) { 
            return true;
        }
    }
    return false;
}

Moeda Mercado::obterMoeda(string codigoPassado) {
    for (const auto& moeda : moedasMercado) {
        if (moeda.codigo == codigoPassado) {
            return moeda;
        }
    }
    return Moeda("Desconhecida", codigoPassado);
}

Moeda Mercado::escolherMoeda(){

    while(true){
        //Listar moedas disponíveis para o usuário escolher
        cout << "Moedas disponiveis no mercado:" << endl;
        for (const Moeda& moeda : moedasMercado) {
            cout << "Codigo: " << moeda.codigo <<"     "<< moeda.nome << endl;
        }
        string codigo;
        cout << "Digite o codigo da moeda (ex: BRL, USD): ";
        cin >> codigo;
        for (auto & c: codigo) c = toupper(c);
        
        if (!this->validarMoeda(codigo)) {
            cout << "Erro: A moeda '" << codigo << "' nao e suportada pelo mercado." << endl;
            cout << "Por favor, tente novamente." << endl;
        }
        return obterMoeda(codigo);
    }
}

//TROCAR DEPOIS DA API DE CONSULTAR CAMBIO
double Mercado::consultarCambio(Moeda moedaBase, Moeda moedaCambio) {

    return 2.0; 
}

unordered_map<string, double> Mercado::compilarCambioMercado(Moeda moedaBase){
    cout << "Consultando cotacoes no mercado..." << endl;
    unordered_map<string, double> taxasDoMomento = ;//chama a api aqui bebeto

    if (taxasDoMomento.empty()) {
        cout << "Erro: Nao foi possivel obter as cotacoes do mercado." << endl;
        return;
    }

    return taxasDoMomento;
}