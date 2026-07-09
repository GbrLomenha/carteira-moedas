#include "Mercado.h"

using namespace std;

Mercado::Mercado() {

    //PROVISÓRIO -- Chamar aqui a api de listar moedas pra preencher o valor do atributo do mercado
    moedasMercado.push_back(Moeda("Real", "BRL"));
    moedasMercado.push_back(Moeda("Dolar", "USD"));
    moedasMercado.push_back(Moeda("Euro", "EUR"));
}

vector<Moeda> Mercado::listarMoedas() {
    return moedasMercado;
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