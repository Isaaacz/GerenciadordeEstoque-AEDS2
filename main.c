#include <stdio.h>
#include "menu.h"

int main() {
    FILE *arq_produtos = fopen("produtos.dat", "a+b");

    if (!arq_produtos) {
        perror("Erro ao abrir arquivo de produtos");
        return 1;
    }

    executar_menu(&arq_produtos);

    fclose(arq_produtos);
    return 0;
}
