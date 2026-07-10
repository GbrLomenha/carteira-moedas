#include "moeda.h"
#include <vector>
#include <unordered_map>

#ifndef MERCADO_H
#define MERCADO_H

using namespace std;

class Carteira;

class Mercado {
    private:

        bool validarMoeda(string codigo, Carteira* carteira=nullptr); 
        void listarMoedas();
        
    public:
        vector<Moeda> moedasMercado; 
        
        Mercado();
        Moeda obterMoeda(string codigo);
        Moeda escolherMoeda(Carteira* carteira=nullptr);
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
        unordered_map<string, double> compilarCambioMercado(Moeda moedaBase);
};

#endif