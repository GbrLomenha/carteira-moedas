#include <iostream>
#include <string>
#include <unordered_map>
#include "moeda.h"
using namespace std;

class Carteira{
    private:
        Moeda moedaPadrao;
        unordered_map<Moeda, double> moedas;
        
    public:
        Carteira(Moeda moeda);
        void definirMoedaPadrao(Moeda moeda);
        void consolidarCarteira()
};