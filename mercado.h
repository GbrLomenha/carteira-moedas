#include "moeda.h"
#include <vector>
#include <unordered_map>

#ifndef MERCADO_H
#define MERCADO_H

using namespace std;

class Mercado {
    private:
        vector<Moeda> moedasMercado; 

        bool validarMoeda(string codigo); 
        void listarMoedas();
        
    public:
        Mercado();
        Moeda obterMoeda(string codigo);
        Moeda escolherMoeda();
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
        unordered_map<string, double> compilarCambioMercado(Moeda moedaBase);
};

#endif