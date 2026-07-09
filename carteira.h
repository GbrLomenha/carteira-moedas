#include <iostream>
#include <string>
#include <unordered_map>
#include "moeda.h"
#include "mercado.h"
using namespace std;

class Carteira{
    private:
        Moeda moedaPadrao;
        unordered_map<string, int> moedas;

        void imprimirPosicaoMoedaUnica(string moeda, int quantiade);
        void depositar(string codigo, int quantidade);
        bool sacar(string codigo, int quantidade);
        void exibirSaldoMoeda(string codigo);
        
    public:
        Carteira(Moeda moeda);
        bool carregarDados(string nomeArquivo, Mercado& mercadoAtivo);
        void salvarDados(string nomeArquivo);
        void definirMoedaPadrao(Moeda moeda);
        void listarPosicao();
        void consolidarCarteira();
        void movimentarSaldo(int tipoOperacao, string codigo, int quantidade);
};