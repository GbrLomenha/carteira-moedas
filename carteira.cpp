#include "carteira.h"
#include "moeda.h"
#include <iomanip>
#include <fstream>

using namespace std;

Carteira::Carteira(Moeda moeda) : moedaPadrao(moeda) {}

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
        
        for (const auto& par : moedas) {
            string sigla = par.first;
            double quantidade = par.second;

            if (sigla == "Desconhecida"){
                continue;
            }

            arquivo << sigla << " " << quantidade << endl;
        }
        
        arquivo.close();
    } else {
        cout << "Erro: Nao foi possivel abrir o arquivo para salvar os dados." << endl;
    }
}

void Carteira::definirMoedaPadrao(Moeda moeda){
    this->moedaPadrao = moeda;
    cout << "A nova moeda padrao eh '" << moedaPadrao.nome << "'." << endl;
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

    double quantidade;

    if (tipoOperacao == 1) {
        Moeda moeda = mercado.escolherMoeda();
        if (verificarMoedaDesconhecida(moeda)) {
            cout << "Operacao cancelada: moeda invalida." << endl;
            return;
        }
        cout << "Digite a quantidade: ";
        cin >> quantidade;
        this->depositar(moeda.codigo, quantidade);
    } else if (tipoOperacao == 2) {
        if (moedas.empty()){
            cout << "Sua carteira esta vazia. Nao ha o que sacar." << endl;
            return;
        }

        Moeda moeda = mercado.escolherMoeda(this);

        if (verificarMoedaDesconhecida(moeda)) {
            cout << "Operacao cancelada: moeda invalida." << endl;
            return;
        }
        cout << "Digite a quantidade: ";
        cin >> quantidade;
        this->sacar(moeda.codigo, quantidade);
    }
}

bool Carteira::verificarMoedaDesconhecida(const Moeda& moeda) {
    return moeda.codigo == "Desconhecida";
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

    for (const auto& par : moedas) {
        string nomeMoeda = par.first;
        double quantidade = par.second;

        imprimirPosicaoMoedaUnica(nomeMoeda, quantidade);
    }
}

void Carteira::comprarMoeda(Mercado& mercado) {
    cout << "\n--- COMPRAR MOEDA ---" << endl;
     if (moedas.empty()) {
        cout << "Sua carteira esta vazia. Ta duro dorme." << endl;
        return;
    }
    
    cout << "Escolha a moeda que voce deseja COMPRAR: ";
    Moeda moedaDestino = mercado.escolherMoeda();
     if (verificarMoedaDesconhecida(moedaDestino)) {
            cout << "Operacao cancelada: moeda invalida." << endl;
            return;
        }

    cout << "Escolha a moeda que voce vai USAR PARA PAGAR: ";
    Moeda moedaOrigem = mercado.escolherMoeda(this);
     if (verificarMoedaDesconhecida(moedaOrigem)) {
            cout << "Operacao cancelada: moeda invalida." << endl;
            return;
        }

    if (moedas.find(moedaOrigem.codigo) == moedas.end() || moedas[moedaOrigem.codigo] <= 0) {
        cout << "Erro: Voce nao possui saldo de " << moedaOrigem.nome << " para usar." << endl;
        return;
    }

    double taxa = mercado.consultarCambio(moedaOrigem, moedaDestino);

    int opcaoTroca;
    cout << endl << "Como voce deseja definir a conversao?" << endl;
    cout << "1 - Quero definir o valor exato de " << moedaOrigem.nome << " que vou GASTAR." << endl;
    cout << "2 - Quero definir o valor exato de " << moedaDestino.nome << " que vou OBTER." << endl;
    cout << "Escolha a opcao: ";
    cin >> opcaoTroca;

    int quantidadePaga = 0;
    int quantidadeRecebida = 0;

    if (opcaoTroca == 1) {
        cout << "Quanto de " << moedaOrigem.nome << " voce quer gastar? (Saldo atual: " << moedas[moedaOrigem.codigo] << "): ";
        cin >> quantidadePaga;
        
        quantidadeRecebida = quantidadePaga * taxa; 
        
    } else if (opcaoTroca == 2) {
        cout << "Quanto de " << moedaDestino.nome << " voce quer obter/comprar?: ";
        cin >> quantidadeRecebida;
        quantidadePaga = quantidadeRecebida / taxa;
        
    } else {
        cout << "Opcao invalida. Operacao cancelada." << endl;
        return;
    }

    if (quantidadePaga > moedas[moedaOrigem.codigo]) {
        cout << "Erro: Saldo insuficiente. A operacao exige " << quantidadePaga << " " << moedaOrigem.nome << ", mas voce so possui " << moedas[moedaOrigem.codigo] << "." << endl;
        return;
    }

    if (quantidadePaga <= 0 || quantidadeRecebida <= 0) {
        cout << "Erro: O valor resultante da conversao e zero ou invalido. Operacao cancelada." << endl;
        return;
    }

    cout << "\nResumo: Convertendo " << quantidadePaga << " " << moedaOrigem.nome << " para " << quantidadeRecebida << " " << moedaDestino.nome << " (Taxa: " << taxa << ")" << endl;

    this->sacar(moedaOrigem.codigo, quantidadePaga);
    this->depositar(moedaDestino.codigo, quantidadeRecebida);
}

void Carteira::consolidarCarteira(Mercado& mercado) {
    if (moedas.empty()) {
        cout << "Sua carteira esta vazia. Nao ha o que consolidar." << endl;
        return;
    }
    
    unordered_map<string, double> taxasDoMomento = mercado.compilarCambioMercado(moedaPadrao);
    
    // CALCULO PL
    double patrimonioLiquido = 0.0;
    unordered_map<string, double> valoresConvertidos; 

    for (const auto& par : moedas) {

        const string& codigo = par.first;
        double quantidade = par.second;

        if (taxasDoMomento.find(codigo) == taxasDoMomento.end()) {
            cout << "Aviso: Cotacao para " << codigo << " nao encontrada. O ativo sera zerado no PL." << endl;
            valoresConvertidos[codigo] = 0.0;
            continue;
        }

        double valorConvertido = quantidade / taxasDoMomento[codigo];
        valoresConvertidos[codigo] = valorConvertido;
        patrimonioLiquido += valorConvertido;
    }

    cout << endl << "==== CONSOLIDACAO DE PATRIMONIO ====" << endl;
    cout << "Moeda Padrao: " << moedaPadrao.nome << " (" << moedaPadrao.codigo << ")" << endl;
    cout << "Patrimonio Liquido (PL): " << fixed << setprecision(2) << patrimonioLiquido << " " << moedaPadrao.codigo << endl;
    cout << "------------------------------------------------------------" << endl;
    
    // CALCAULO EXPOSICAO
    cout << left << setw(10) << "Ativo" << right << setw(15) << "Quantidade" << setw(20) << "Valor (" + moedaPadrao.codigo + ")" << setw(15) << "Exposicao" << endl;

    for (const auto& par : moedas) {
        const string& codigo = par.first;
        double quantidade = par.second;

        double exposicao = 0.0;
        if (patrimonioLiquido > 0) {
            exposicao = (valoresConvertidos[codigo] / patrimonioLiquido) * 100.0;
        }

        cout << left << setw(10) << codigo << right << setw(15) << quantidade << setw(20) << valoresConvertidos[codigo] << setw(14) << exposicao << "%" << endl;
    }
    cout << "============================================================" << endl;
}

unordered_map<string, double> Carteira::getMoedas() {
    return moedas;
}