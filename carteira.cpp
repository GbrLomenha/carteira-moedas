#include "carteira.h"
#include "moeda.h"
#include <iomanip>
#include <fstream>

using namespace std;

bool Carteira::carregarDados(string nomeArquivo, Mercado& mercado) {
    ifstream arquivo(nomeArquivo); 
    
    if (arquivo.is_open()) {
        string siglaPadrao;
        
        if (arquivo >> siglaPadrao) {
            this->definirMoedaPadrao(mercado.obterMoeda(siglaPadrao));
        }
        
        string sigla;
        double quantidade;
        while (arquivo >> sigla >> quantidade) {
            moedas[sigla] = quantidade;
        }
        
        arquivo.close();
        return true; 
    }
    
    return false; 
}

void Carteira::salvarDados(string nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    
    if (arquivo.is_open()) {
        arquivo << moedaPadrao.codigo << endl;
        
        for (const auto& [sigla, quantidade] : moedas) {
            arquivo << sigla << " " << quantidade << endl;
        }
        
        arquivo.close();
    } else {
        cout << "Erro: Nao foi possivel abrir o arquivo para salvar os dados." << endl;
    }
}

void Carteira::definirMoedaPadrao(Moeda moeda){
    this->moedaPadrao = moeda;
}

void Carteira::depositar(string codigo, double quantidade) {
    moedas[codigo] += quantidade;
    cout << "Deposito realizado com sucesso!" << endl;
    this->exibirSaldoMoeda(codigo);
}

bool Carteira::sacar(string codigo, double quantidade) {
    if (moedas.find(codigo) == moedas.end()) {
        cout << "Erro: Voce nao possui a moeda " << codigo << " na carteira." << endl;
        return false;
    }

    if (moedas[codigo] < quantidade) {
        cout << "Erro: Saldo insuficiente. Saldo atual: " << moedas[codigo] << " " << codigo << endl;
        return false;
    }

    moedas[codigo] -= quantidade;
    
    if (moedas[codigo] == 0) {
        moedas.erase(codigo);
        cout << "O saldo de " << codigo << " foi zerado. Moeda removida da carteira." << endl;
    } else {
        cout << "Saque realizado com sucesso!" << endl;
        this->exibirSaldoMoeda(codigo);
    }

    return true;
}

void Carteira::movimentarSaldo(Mercado& mercado) {
    double tipoOperacao;
    cout << "Escolha a operacao:" << endl;
    cout << "1 - Depositar" << endl;
    cout << "2 - Sacar" << endl;
    cin >> tipoOperacao;

    if (tipoOperacao != 1 && tipoOperacao != 2) {
        cout << "Operacao invalida. Nenhuma movimentacao foi realizada." << endl;
        return;
    }

    string codigo;
    cout << "Digite o codigo da moeda (ex: BRL, USD): ";
    cin >> codigo;
    for (auto & c: codigo) c = toupper(c);

    if (!mercado.validarMoeda(codigo)) {
        cout << "Erro: A moeda '" << codigo << "' nao e suportada pelo mercado." << endl;
        return;
    }

    double quantidade;
    cout << "Digite a quantidade: ";
    cin >> quantidade;

    if (tipoOperacao == 1) {
        this->depositar(codigo, quantidade);
    } else if (tipoOperacao == 2) {
        this->sacar(codigo, quantidade);
    }
}

void Carteira:: exibirSaldoMoeda(string codigo){
    cout << "Saldo atualizado: " << moedas[codigo] << " " << codigo << endl;
}

void Carteira:: imprimirPosicaoMoedaUnica(string moeda, double quantidade){
    cout << left << setw(10) << moeda << right << setw(15) << quantidade << endl;
}

void Carteira:: listarPosicoes() {
    cout << "====LISTANDO POSICOES NA CARTEIRA====" << endl;
    cout << left << setw(10) << "Ativo" << right << setw(15) << "Quantidade" << endl;

    for (const auto&[nomeMoeda, quantidade]: moedas){
        imprimirPosicaoMoedaUnica(nomeMoeda, quantidade);
    }   
}

void Carteira::comprarMoeda(Mercado& mercado) {
    cout << "\n--- COMPRAR MOEDA ---" << endl;

    //Listar moedas aqui para mostrar opções
    
    string codigoDestino;
    cout << "Digite o codigo da moeda que voce deseja COMPRAR (ex: USD): ";
    cin >> codigoDestino;
    for (auto & c: codigoDestino) c = toupper(c);

    if (!mercado.validarMoeda(codigoDestino)) {
        cout << "Erro: A moeda '" << codigoDestino << "' nao e suportada pelo mercado." << endl;
        return;
    }

    string codigoOrigem;
    cout << "Digite o codigo da moeda que voce vai USAR PARA PAGAR (ex: BRL): ";
    cin >> codigoOrigem;
    for (auto & c: codigoOrigem) c = toupper(c);

    if (moedas.find(codigoOrigem) == moedas.end() || moedas[codigoOrigem] <= 0) {
        cout << "Erro: Voce nao possui saldo de " << codigoOrigem << " para usar." << endl;
        return;
    }

    Moeda origem = mercado.obterMoeda(codigoOrigem);
    Moeda destino = mercado.obterMoeda(codigoDestino);
    double taxa = mercado.consultarCambio(origem, destino);

    int opcaoTroca;
    cout << endl << "Como voce deseja definir a conversao?" << endl;
    cout << "1 - Quero definir o valor exato de " << codigoOrigem << " que vou GASTAR." << endl;
    cout << "2 - Quero definir o valor exato de " << codigoDestino << " que vou OBTER." << endl;
    cout << "Escolha a opcao: ";
    cin >> opcaoTroca;

    int quantidadePaga = 0;
    int quantidadeRecebida = 0;

    if (opcaoTroca == 1) {
        cout << "Quanto de " << codigoOrigem << " voce quer gastar? (Saldo atual: " << moedas[codigoOrigem] << "): ";
        cin >> quantidadePaga;
        
        quantidadeRecebida = quantidadePaga * taxa; 
        
    } else if (opcaoTroca == 2) {
        cout << "Quanto de " << codigoDestino << " voce quer obter/comprar?: ";
        cin >> quantidadeRecebida;
        quantidadePaga = quantidadeRecebida / taxa;
        
    } else {
        cout << "Opcao invalida. Operacao cancelada." << endl;
        return;
    }

    if (quantidadePaga > moedas[codigoOrigem]) {
        cout << "Erro: Saldo insuficiente. A operacao exige " << quantidadePaga << " " << codigoOrigem << ", mas voce so possui " << moedas[codigoOrigem] << "." << endl;
        return;
    }

    if (quantidadePaga <= 0 || quantidadeRecebida <= 0) {
        cout << "Erro: O valor resultante da conversao e zero ou invalido. Operacao cancelada." << endl;
        return;
    }

    cout << "\nResumo: Convertendo " << quantidadePaga << " " << codigoOrigem << " para " << quantidadeRecebida << " " << codigoDestino << " (Taxa: " << taxa << ")" << endl;

    this->sacar(codigoOrigem, quantidadePaga);
    this->depositar(codigoDestino, quantidadeRecebida);
}