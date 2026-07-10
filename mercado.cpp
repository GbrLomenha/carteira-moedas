#include "mercado.h"
#include "carteira.h"
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

bool Mercado::validarMoeda(string codigoPassado, Carteira* carteira) {

    if (carteira != nullptr) {
        for (const auto& par : carteira->getMoedas()) {
            const string& codigo = par.first;
            if (codigo == codigoPassado) {
                return true;
            }
        }
    }

    else{
        for (const auto& moeda : moedasMercado) {
            if (moeda.codigo == codigoPassado) { 
                return true;
            }
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

//TROCAR DEPOIS DA API DE CONSULTAR CAMBIO
double Mercado::consultarCambio(Moeda moedaBase, Moeda moedaCambio) {

    string comando = "python api.py getCambio " + moedaBase.codigo + " " + moedaCambio.codigo;

    // abre um pipe para ler a saida do python
    //abre um fork child sendo o processo do python e o processo pai continua a execucao do programa (c++)
    // Usando _popen para abrir no windows, se fosse linux seria so popen
    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) {
        cout << "Erro ao abrir o script de integracao externo." << endl;
        return 0.0; 
    }

    char buffer[256];
    double taxaCambio = 0.0;
    
    // le a saida do python linha por linha
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        string linha(buffer);
        
        // remove a quebra de linha do final se existir
        if (!linha.empty() && linha.back() == '\n') {
            linha.pop_back();
        }
        taxaCambio = stod(linha);
    }
    // fecha o pipe 
    _pclose(pipe);

    return taxaCambio;

}

Moeda Mercado::escolherMoeda(Carteira* carteira) {

    while(true){
        // listar moedas disponiveis para o usuario escolher
if (carteira == nullptr) {
    cout << "Moedas disponiveis no mercado:" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    
    int colunas = 5; // define o numero de colunas paralelas
    int contador = 0;
    
    for (const Moeda& moeda : moedasMercado) {
        // limita o tamanho do nome exibido para nao estourar a coluna
        string nomeExibicao = moeda.nome.substr(0, 18);
        string item = "[" + moeda.codigo + "] " + nomeExibicao;
        
        // deixa cada coluna com exatamente 26 caracteres de largura
        cout << left << setw(26) << item;
        
        contador++;
        // se atingiu o limite de colunas, quebra a linha
        if (contador % colunas == 0) {
            cout << endl;
        }
    }
    // garante uma quebra de linha no final se a ultima linha nao completou as colunas
    if (contador % colunas != 0) {
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}
else if (carteira != nullptr) {
    cout << "Moedas disponiveis na sua carteira:" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    
    int colunas = 5;
    int contador = 0;
    
    for (const auto& par : carteira->getMoedas()) {
        const string& codigo = par.first;
        string nomeExibicao = obterMoeda(codigo).nome.substr(0, 18);
        string item = "[" + codigo + "] " + nomeExibicao;
        
        cout << left << setw(26) << item;
        
        contador++;
        if (contador % colunas == 0) {
            cout << endl;
        }
    }
    if (contador % colunas != 0) {
        cout << endl;
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}

        string codigo;
        cout << "Digite o codigo da moeda (ex: BRL, USD): ";
        cin >> codigo;
        for (auto & c: codigo) c = toupper(c);

        if (!this->validarMoeda(codigo, carteira)) {
            cout << "Erro: A moeda '" << codigo << "' nao e suportada." << endl;
            cout << "Por favor, tente novamente." << endl;
            continue;
        }

        return obterMoeda(codigo);
    }
}

unordered_map<string, double> Mercado::compilarCambioMercado(Moeda moedaBase) {

    unordered_map<string, double> resposta;

   // comando para rodar o python passando o argumento listar
    //No Windows utilizar apenas python e no Linux utilizar python3
    string comando = "python api.py getCambioBase " + moedaBase.codigo;
    
    FILE* pipe = _popen(comando.c_str(), "r");
    
    if (!pipe) {
        cout << "erro ao abrir o script de integracao externo." << endl;
        return resposta;
    }
    
    char buffer[256];
    // le a saida do python linha por linha
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        string linha = buffer;

        // remove a quebra de linha do final se existir
        if (!linha.empty() && linha.back() == '\n') {
            linha.pop_back();
        }
        
        // divide a string usando o caractere , como separador
        stringstream ss(linha);
        string codigo;
        string taxa;
        
        if (getline(ss, codigo, ',') && getline(ss, taxa, ',')) {
            resposta[codigo] = stod(taxa);
        }
    }
    
    // fecha o pipe 
    _pclose(pipe);

    return resposta;
}