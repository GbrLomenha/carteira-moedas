# Gerenciador de Carteira de Moedas e Análise Cambial

## Descrição

Sistema desenvolvido em C++ com integração em Python para gerenciamento de carteira de investimentos e análise de exposição cambial em tempo real. 

O programa utiliza a API externa *ExchangeRate-API* para coletar as taxas de câmbio globais atualizadas. 

---

## Estrutura do Projeto

### Arquivos Separados

* **main.cpp**: Contém o loop principal do menu interativo e coordena o fluxo de chamadas do sistema.
* **api.py**: Script em Python responsável por se conectar à API, extrair os dados em JSON e filtrar as informações para o C++.

### Classes (C++)

#### Moeda
* `nome`: Nome completo da moeda (ex: *Brazilian Real*).
* `codigo`: Sigla internacional de três letras (ex: *BRL*).

#### Mercado
* `moedasMercado`: Vetor que armazena todas as moedas validadas da API.
* `listarMoedas()`: Executa o script Python para alimentar o mercado.
* `consultarCambio()`: Obtém a taxa de conversão entre duas moedas específicas.
* `compilarCambioMercado()`: Coleta todas as cotações em relação a uma moeda base.

#### Carteira
* `moedaPadrao`: Moeda base utilizada para exibir o saldo consolidated.
* `moedas`: Mapa dinâmico (`unordered_map`) que vincula o código da moeda à sua quantidade de saldo.
* `carregarDados()` / `salvarDados()`: Gerenciam a leitura e escrita no arquivo local.
* `comprarMoeda()`: Realiza a troca de ativos deduzindo o saldo de origem e alimentando o destino.
* `consolidarCarteira()`: Calcula o valor total do patrimônio e a exposição de risco.

---

## Formato do Arquivo de Dados (`carteira.txt`)

O arquivo de persistência local segue uma estrutura estrita de leitura:
* **Linha 1**: Código da moeda padrão do sistema.
* **Linhas seguintes**: Código da moeda possuída e a quantidade de saldo separada por espaço.

### Funcionalidades
O sistema possui as seguintes opções disponíveis no menu:

# 1. Definir moeda padrão
Altera a moeda de referência do sistema. Toda a consolidação de saldo e relatórios de exposição passarão a usar esta moeda como base.

# 2. Fazer depósito ou saque na carteira
Permite movimentar os saldos internos de forma manual, adicionando fundos ou retirando valores de moedas específicas da carteira.

# 3. Comprar moeda
Simula e executa uma operação de câmbio. O usuário escolhe a moeda que quer comprar e qual ativo da sua carteira usará para pagar. O sistema consulta a taxa de conversão em tempo real e atualiza ambos os saldos se houver fundos suficientes.

# 4. Listar posição da carteira
Exibe de forma direta um extrato simples contendo os saldos absolutos de cada moeda armazenada pelo usuário.

# 5. Consolidar patrimônio e exposições
Gera o relatório financeiro. Converte todos os saldos para a moeda padrão escolhida, soma o patrimônio líquido total e exibe uma tabela com a exposição percentual que cada ativo representa no portfólio.

# 0. Sair
Salva as alterações atuais de saldo de volta no arquivo carteira.txt e encerra o programa.

### Requisitos e Solução de Problemas

Compilador G++

Interpretador Python 3 (com suporte a variáveis de ambiente/PATH ativo no sistema)

Biblioteca requests do Python instalada

### Correção de erros comuns de ambiente:
Erro de comando Python não reconhecido: Certifique-se de reinstalar o Python marcando a caixinha "Add Python to PATH".

Erro ModuleNotFoundError: No module named 'requests': Abra o terminal da máquina e instale a dependência de rede rodando o comando:

Bash
pip install requests

## Compilação e Execução
### Compilação (Windows)
No terminal, utilize o arquivo automatizado executando:

mingw32-make
Execução
Após gerar o binário compilado:

.\main.exe
Limpeza
Para remover os arquivos temporários de objetos e o executável:

mingw32-make clean

Observação: Caso pretenda rodar em ambiente Linux, abra o arquivo Makefile e faça a alteração indicada na linha 1 para ajustar as chaves do compilador.

### Autores

Gabriel Lomenha

Roberto Ceschini
