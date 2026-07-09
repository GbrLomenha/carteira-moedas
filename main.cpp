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

        //Listar aqui os códigos de moedas disponíveis para selecionar a moeda padrão da carteira 

        string codigoMoedaPadrao;
        while (true){
            cout << "Digite a sigla da sua Moeda Padrao (ex: BRL, USD): ";
            cin >> codigoMoedaPadrao;
            for (auto & c: codigoMoedaPadrao) c = toupper(c);
            if(mercadoAtivo.validarMoeda(codigoMoedaPadrao)){
                break;
            }
            cout << "Erro: Moeda com código '" << codigoMoedaPadrao << "' nao encontrada no mercado." << endl;
            cout << "Por favor, tente novamente." << endl;
        };

        Moeda moedaPadrao = mercadoAtivo.obterMoeda(codigoMoedaPadrao); 
        minhaCarteira.definirMoedaPadrao(moedaPadrao);
        
        cout << "Carteira iniciada com sucesso!" << endl;
    };

    cout << "Dados carregados com sucesso de " << arquivoCarteira << "!" << endl;

    int opcao;
    do {
        cout << endl;
        cout << "1 - Definir moeda padrao" << endl;
        cout << "2 - Fazer deposito ou saque na carteira" << endl;
        cout << "3 - Comprar moeda" << endl;
        cout << "4 - Listar posicaoo da carteira" << endl;
        cout << "5 - Consolidar padtrimônio e exposicoes" << endl;
        cout << "0 - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        };
    }while(opcao != 0);

    return 0;
}