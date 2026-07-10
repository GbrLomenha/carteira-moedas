#include "moeda.h"
#include <vector>
using namespace std;

class Mercado {
    private:
        vector<Moeda> moedasMercado; 

        bool validarMoeda(string codigo); 
        void listarMoedas();
        
    public:
        Mercado();
        Moeda obterMoeda(string codigo);
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
        Moeda escolherMoeda();
};