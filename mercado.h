#include "moeda.h"
#include <vector>
#include <unordered_map>

#ifndef MERCADO_H
#define MERCADO_H

using namespace std;

class Mercado {
    private:

        bool validarMoeda(string codigo); 
        void listarMoedas();
        
    public:
        vector<Moeda> moedasMercado; 
        
        Mercado();
        Moeda obterMoeda(string codigo);
        Moeda escolherMoeda();
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
        unordered_map<string, double> compilarCambioMercado(Moeda moedaBase);
};

#endif