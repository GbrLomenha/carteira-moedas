# Carteira de Moedas

Projeto para a disciplina de Linguagens de Programação (UFRJ, período 26.1). Implementa um sistema de gerenciamento de uma carteira de moedas de diferentes nacionalidades em C++ com um script externo em Python para operações auxiliares (por exemplo, atualização de taxas).

## Objetivo
- Gerenciar saldos em várias moedas.
- Converter valores entre moedas usando taxas externas.
- Perservar e carregar estado da carteira (arquivo JSON/CSV).
- Demonstrar integração entre C++ e Python.

## Estrutura do projeto (sugerida)
- /src — código-fonte C++
- /include — headers C++
- /bin — executáveis gerados
- /scripts — scripts Python (ex.: atualizar_taxas.py)
- /data — arquivos de exemplo (carteira.json, taxas.json)
- README.md, LICENSE

## Requisitos
- Compilador C++ compatível com C++17 (g++, clang++)
- CMake (opcional)
- Python 3.8+ para scripts auxiliares
- (opcional) requests ou outra biblioteca listada em scripts/requirements.txt

## Compilação e execução
1. Compilação direta com g++ (exemplo):
    g++ -std=c++17 -O2 -Iinclude -o bin/carteira src/*.cpp

2. Com CMake:
    mkdir -p build && cd build
    cmake ..
    cmake --build .

3. Executar:
    ./bin/carteira          # abre interface/CLI da carteira
    python3 scripts/atualizar_taxas.py  # atualiza taxas externas (requer internet)

## Uso (exemplo de comandos CLI)
- Inicializar carteira:
  ./bin/carteira init --file data/carteira.json
- Adicionar moeda:
  ./bin/carteira add --currency USD --amount 150.00
- Converter:
  ./bin/carteira convert --from USD --to BRL --amount 100
- Listar saldos:
  ./bin/carteira list

(Adaptar comandos à interface implementada.)

## Dados e persistência
- Arquivo de carteira em JSON/CSV em data/
- Script Python pode obter taxas de uma API e salvar em data/taxas.json

## Contribuição
- Abrir issues para bugs/funcionalidades.
- Enviar pull requests com código testado e descrições claras.

## Licença
- Escolher e indicar uma licença (ex.: MIT).

Contato: informações do repositório / do autor no cabeçalho do projeto.