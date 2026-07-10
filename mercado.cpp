#include "Mercado.h"

using namespace std;

Mercado::Mercado() {

    //PROVISÓRIO -- Chamar aqui a api de listar moedas pra preencher o valor do atributo do mercado
    listarMoedas();
}

void Mercado::listarMoedas() {
    vector<Moeda> moedasDisponiveis = getMoedasDisponieveis(); //getMoedasDisponiveis é uma funcao do Python

    //Filtrar o resultados JSON ou Já retornar o resultado filtrado??

    if (moedasDisponiveis.empty()) {
        cout << "Nenhuma moeda disponível no mercado." << endl;
        return;
    }

    for (const Moeda& moeda : moedasDisponiveis) {
        moedasMercado.push_back(moeda);
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
}

//TROCAR DEPOIS DA API DE CONSULTAR CAMBIO
double Mercado::consultarCambio(Moeda moedaBase, Moeda moedaCambio) {

    return 2.0; 
}

Moeda Mercado::escolherMoeda(){
    while(true){
        this->listarMoedas();
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