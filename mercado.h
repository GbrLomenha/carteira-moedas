#include "moeda.h"
#include <vector>

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
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
        Moeda escolherMoeda();
};

#endif