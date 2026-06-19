#include "moeda.h"
#include <vector>
using namespace std;

class Mercado{
    public:
        Mercado();
        vector<Moeda> listarMoedas();
        double consultarCambio(Moeda moeda1, Moeda moeda2);
};