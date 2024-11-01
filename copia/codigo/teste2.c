#include <stdio.h>

#define TAMANHO 8192

int main(void) {
    char BUFFER[TAMANHO];
    FILE *entrada, *saida;

    entrada = fopen("arquivo_teste", "rb");
    saida = fopen("arquivo_saida", "wb");

    int qtd;
    qtd = fread(BUFFER, sizeof(char), TAMANHO, entrada);
    while(qtd > 0) {
        fwrite(BUFFER, sizeof(char), qtd, saida);
        qtd = fread(BUFFER, sizeof(char), TAMANHO, entrada);
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}