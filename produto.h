#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include "entidades.h"

void salva_produto(Produto *p, FILE *out);
Produto *le_produto(FILE *in);
Produto *buscaSequencial(int chave, FILE *in, int *comps);
Produto *buscaBinaria(int chave, FILE *in, int inicio, int fim, int *comps);
FILE* gerar_base_teste(FILE *out, int quantidade);

#endif
