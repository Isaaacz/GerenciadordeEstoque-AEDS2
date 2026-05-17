#ifndef ENTIDADES_H
#define ENTIDADES_H

typedef struct {
    int id;
    char nome[50];
    char cnpj[20];
} Fornecedor;

typedef struct {
    int id;
    char nome[50];
    char cargo[30];
} Funcionario;

typedef struct {
    int id;
    char nome[50];
    double preco;
    int qtd_estoque;
    int id_fornecedor;
    int id_funcionario;
} Produto;

#endif