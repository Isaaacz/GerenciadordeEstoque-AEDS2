# Gerenciador de Estoque (AEDS II)

Sistema de estoque em C, feito para a disciplina de Algoritmos e Estruturas de Dados II na UFOP. Os produtos ficam gravados em um arquivo binário (`produtos.dat`), e o programa compara na prática a **busca sequencial** com a **busca binária** feitas direto no arquivo, registrando o número de comparações e o tempo de cada busca.

## Funcionalidades

- Cadastro de produtos (ID, nome, preço, estoque, fornecedor e funcionário responsável), gravados com `fwrite` no arquivo binário
- Busca por ID de duas formas:
  - **sequencial** (`buscaSequencial`): lê registro por registro desde o início
  - **binária** (`buscaBinaria`): usa `fseek` para pular direto para o registro do meio
- Geração de uma base de teste com N produtos ordenados por ID (`gerar_base_teste`)
- Log de desempenho em `log.txt` com o método, as comparações e o tempo em ms (`salvar_log`)
- Listagem de todos os produtos cadastrados

## Exemplo de resultado

Com uma base de 100.000 produtos, buscando o ID 90000:

```
Metodo: Sequencial - Comparacoes: 90000 - Tempo: 6.1320 ms
Metodo: Binaria - Comparacoes: 17 - Tempo: 0.0370 ms
```

A busca binária faz no máximo ⌈log₂ n⌉ comparações (17 para 100 mil registros), enquanto a sequencial cresce de forma linear com o tamanho da base.

> **Observação:** a busca binária só funciona se o arquivo estiver ordenado por ID. A base gerada pela opção 5 já sai ordenada, mas produtos cadastrados manualmente são gravados no fim do arquivo e podem quebrar essa ordem.

## Estrutura

| Arquivo | Responsabilidade |
|---|---|
| `entidades.h` | structs `Produto`, `Fornecedor` e `Funcionario` |
| `produto.c/.h` | leitura e escrita no arquivo binário, buscas e geração da base |
| `menu.c/.h` | menu interativo e medição de tempo com `clock()` |
| `log.c/.h` | gravação do log de desempenho |
| `main.c` | abre o arquivo de dados e inicia o menu |

O produto se relaciona com o fornecedor e com o funcionário pelos campos `id_fornecedor` e `id_funcionario`.

## Como compilar e rodar

Com CMake:

```bash
cmake -S . -B build
cmake --build build
./build/GerenciadordeEstoque
```

Ou direto com o gcc:

```bash
gcc -std=c11 -Wall main.c produto.c log.c menu.c -o estoque
./estoque
```

Os arquivos `produtos.dat` e `log.txt` são criados na pasta onde o programa for executado.

## O que aprendi

- Persistir structs em arquivo binário com `fwrite`/`fread` e acessar um registro específico com `fseek`
- Por que a busca binária exige dados ordenados, e o quanto isso compensa: 17 comparações contra 90 mil
- Medir o desempenho de um algoritmo (comparações e tempo) em vez de só confiar na teoria
- Organizar um projeto em C em módulos (`.h`/`.c`) e compilar com CMake
