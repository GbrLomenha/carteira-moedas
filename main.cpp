#include <iostream>
#include "carteira.h"
#include "moeda.h"
#include "mercado.h"

using namespace std;

int main() {
    Mercado mercadoAtivo;
    Moeda moedaTemp("TEMP", "TMP"); 
    Carteira minhaCarteira(moedaTemp);

    string arquivoCarteira = "carteira.txt";

    if (!minhaCarteira.carregarDados(arquivoCarteira, mercadoAtivo)) {
        cout << "=== BEM-VINDO AO GERENCIADOR DE CARTEIRA ===" << endl;

        minhaCarteira.definirMoedaPadrao(mercadoAtivo.escolherMoeda());
        
        cout << "Carteira iniciada com sucesso!" << endl;
    }
    else{
        cout << "Dados carregados com sucesso de " << arquivoCarteira << "!" << endl;
    }

    int opcao;
    do {
        cout << endl;
        cout << "1 - Definir moeda padrao" << endl;
        cout << "2 - Fazer deposito ou saque na carteira" << endl;
        cout << "3 - Comprar moeda" << endl;
        cout << "4 - Listar posicaoo da carteira" << endl;
        cout << "5 - Consolidar padtrimonio e exposicoes" << endl;
        cout << "0 - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                minhaCarteira.definirMoedaPadrao(mercadoAtivo.escolherMoeda());
                break;
            case 2:
                minhaCarteira.movimentarSaldo(mercadoAtivo);
                break;
            case 3:
                minhaCarteira.comprarMoeda(mercadoAtivo);
                break;
            case 4:
                minhaCarteira.listarPosicoes();
                break;
            case 5:
                minhaCarteira.consolidarCarteira(mercadoAtivo);
                break;
            default:
                break;
        };
    }while(opcao != 0);

    cout << "Salvando dados da carteira..." << endl;
    minhaCarteira.salvarDados(arquivoCarteira);
    cout << "Programa encerrado." << endl;

    return 0;
}