#include <iostream>
#include <string>
#include <unordered_map>
#include "moeda.h"
#include "mercado.h"
using namespace std;

class Carteira{
    
    private:
        Moeda moedaPadrao;
        unordered_map<string, double> moedas;

        void imprimirPosicaoMoedaUnica(string moeda, double quantiade);
        void depositar(string codigo, double quantidade);
        bool sacar(string codigo, double quantidade);
        void exibirSaldoMoeda(string codigo);

    public:
        Carteira(Moeda moeda);

        bool carregarDados(string nomeArquivo, Mercado& mercadoAtivo);
        void salvarDados(string nomeArquivo);

        void definirMoedaPadrao(Moeda moeda);

        void listarPosicoes();

        void consolidarCarteira();

        void movimentarSaldo(Mercado& mercadoAtivo);

        void comprarMoeda(Mercado& mercadoAtivo);

        void consolidarCarteira(Mercado& mercadoAtivo);
};