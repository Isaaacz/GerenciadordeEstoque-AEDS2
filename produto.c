#include "produto.h"
#include <stdlib.h>

void salva_produto(Produto *p, FILE *out) {
    fwrite(p, sizeof(Produto), 1, out);
}

Produto *le_produto(FILE *in) {
    Produto *p = malloc(sizeof(Produto));
    if (fread(p, sizeof(Produto), 1, in) <= 0) {
        free(p);
        return NULL;
    }
    return p;
}

Produto *buscaSequencial(int chave, FILE *in, int *comps) {
    rewind(in);
    Produto *p;
    *comps = 0;
    while ((p = le_produto(in)) != NULL) {
        (*comps)++;
        if (p->id == chave) return p;
        free(p);
    }
    return NULL;
}

Produto *buscaBinaria(int chave, FILE *in, int inicio, int fim, int *comps) {
    *comps = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        fseek(in, meio * sizeof(Produto), SEEK_SET);
        Produto *p = le_produto(in);
        if (p) {
            (*comps)++;
            if (p->id == chave) return p;
            if (p->id > chave) fim = meio - 1;
            else inicio = meio + 1;
            free(p);
        } else break;
    }
    return NULL;
}

FILE* gerar_base_teste(FILE *out, int quantidade) {
    fclose(out);
    out = fopen("produtos.dat", "w+b");
    if (!out) return NULL;

    for (int i = 1; i <= quantidade; i++) {
        Produto p;
        p.id = i;
        sprintf(p.nome, "Produto_%d", i);
        p.preco = (double)(rand() % 1000) / 10.0;
        p.qtd_estoque = rand() % 100;
        p.id_fornecedor = (i % 5) + 1;
        p.id_funcionario = (i % 3) + 1;
        fwrite(&p, sizeof(Produto), 1, out);
    }
    fflush(out);
    return out;
}
