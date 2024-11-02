#include <stdio.h>

int main(void) {
    FILE *entrada, *saida;

    entrada = fopen("arquivo_teste", "rb");
    saida = fopen("arquivo_saida", "wb");

    int c;
    c = fgetc(entrada);
    while(c != EOF) {
        fputc(c, saida);
        c = fgetc(entrada);
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}