#include "log.h"
#include <stdio.h>

void salvar_log(const char *metodo, int comparacoes, double tempo) {
    FILE *log = fopen("log.txt", "a");
    if(log) {
        fprintf(log, "Metodo: %s - Comparacoes: %d - Tempo: %.4f ms\n", metodo, comparacoes, tempo);
        fclose(log);
    }
}
