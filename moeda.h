#include <string>
#include <iostream>

#ifndef MOEDA_H
#define MOEDA_H

using namespace std;

class Moeda{
    public:
        string nome;
        string codigo;
        Moeda(string, string);
};
#endif