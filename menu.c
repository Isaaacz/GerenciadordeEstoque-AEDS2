#include "menu.h"
#include "entidades.h"
#include "produto.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exibir_menu() {
    printf("\n======= SISTEMA DE ESTOQUE - AEDS 2 =======");
    printf("\n1. Cadastrar Produto");
    printf("\n2. Buscar Produto (Sequencial)");
    printf("\n3. Buscar Produto (Binaria)");
    printf("\n4. Listar todos os Produtos");
    printf("\n5. Gerar Base de Teste");
    printf("\n0. Sair");
    printf("\nEscolha uma opcao: ");
}

void interacao_entidades(Produto *p) {
    printf("\n--- Interacao entre Entidades ---");
    printf("\nO Produto '%s' e fornecido pelo Fornecedor ID: %d", p->nome, p->id_fornecedor);
    printf("\nO cadastro foi realizado pelo Funcionario ID: %d\n", p->id_funcionario);
}

void executar_menu(FILE **arq_produtos) {
    int opcao = -1;

    while (opcao != 0) {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1) {
            Produto p;
            printf("ID: "); scanf("%d", &p.id);
            printf("Nome: "); scanf("%s", p.nome);
            printf("Preco: "); scanf("%lf", &p.preco);
            printf("Qtd Estoque: "); scanf("%d", &p.qtd_estoque);
            printf("ID Fornecedor: "); scanf("%d", &p.id_fornecedor);
            printf("ID Funcionario: "); scanf("%d", &p.id_funcionario);

            fseek(*arq_produtos, 0, SEEK_END);
            salva_produto(&p, *arq_produtos);
            printf("Produto cadastrado com sucesso!\n");

        } else if (opcao == 2 || opcao == 3) {
            int chave, comps = 0;
            printf("Digite o ID para busca: ");
            if (scanf("%d", &chave) != 1) {
                while (getchar() != '\n');
                continue;
            }

            clock_t t = clock();
            Produto *res = NULL;

            if (opcao == 2) {
                res = buscaSequencial(chave, *arq_produtos, &comps);
            } else {
                fseek(*arq_produtos, 0, SEEK_END);
                long tamanho_arquivo = ftell(*arq_produtos);
                int total_reg = (int)(tamanho_arquivo / sizeof(Produto));
                res = buscaBinaria(chave, *arq_produtos, 0, total_reg - 1, &comps);
            }

            t = clock() - t;
            double tempo_ms = ((double)t) / CLOCKS_PER_SEC * 1000.0;
            
            salvar_log(opcao == 2 ? "Sequencial" : "Binaria", comps, tempo_ms);

            if (res) {
                printf("\n--- Produto Encontrado ---");
                printf("\nID: %d | Nome: %s | Preco: %.2f | Estoque: %d\n", res->id, res->nome, res->preco, res->qtd_estoque);
                interacao_entidades(res);
                free(res);
            } else {
                printf("\nProduto com ID %d nao encontrado.\n", chave);
            }

        } else if (opcao == 4) {
            rewind(*arq_produtos);
            Produto *p;
            printf("\n--- Lista de Produtos ---\n");
            int encontrou = 0;
            while ((p = le_produto(*arq_produtos)) != NULL) {
                printf("ID: %d | Nome: %s | Preco: %.2f\n", p->id, p->nome, p->preco);
                free(p);
                encontrou = 1;
            }
            if (!encontrou) printf("Nenhum produto cadastrado.\n");

        } else if (opcao == 5) {
            int qtd;
            printf("Quantidade de produtos para gerar: ");
            if (scanf("%d", &qtd) == 1) {
                *arq_produtos = gerar_base_teste(*arq_produtos, qtd);
                if (*arq_produtos) {
                    printf("%d produtos gerados com sucesso!\n", qtd);
                } else {
                    printf("Erro ao recriar a base de dados.\n");
                }
            } else {
                while (getchar() != '\n');
            }
        }
    }
}
