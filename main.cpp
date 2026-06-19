#include <iostream>
#include "carteira.h"
#include "moeda.h"

using namespace std;

int main() {
    int opcao;
    do{
        cout << endl;
        cout << "1 - Definir moeda padrao" << endl;
        cout << "2 - Fazer deposito ou saque na carteira" << endl;
        cout << "3 - Comprar moeda" << endl;
        cout << "4 - Listar posicaoo da carteira" << endl;
        cout << "5 - Consolidar padtrimônio e exposicoes" << endl;
        cout << "0 - Sair" << endl;
        cin >> opcao;

        switch (opcao)
        {
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
        case 6:
            break;
        default:
            break;
        }
    }while(opcao != 0);

    return 0;
}