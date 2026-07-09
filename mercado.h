#include "moeda.h"
#include <vector>
using namespace std;

class Mercado {
    private:
        vector<Moeda> moedasMercado; 
        
    public:
        Mercado();
        void listarMoedas();
        bool validarMoeda(string codigo); 
        Moeda obterMoeda(string codigo);
        double consultarCambio(Moeda moedaBase, Moeda moedaCambio);
};