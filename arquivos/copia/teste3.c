#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *entrada, *saida;

    entrada = fopen("arquivo_teste", "rb");
    saida = fopen("arquivo_saida", "wb");

    fseek(entrada, 0, SEEK_END);
    int tamanho = ftell(entrada);
    rewind(entrada); // fseek(entrada, 0, SEEK_SET);

    int qtd = (tamanho/sizeof(char)); // sizeof(char) == 1 -> qtd = tamanho 

    char *BUFFER = (char *)malloc(tamanho); // mudei de int pra char mas continua errado
    fread(BUFFER, sizeof(char), qtd, entrada);
    fwrite(BUFFER, sizeof(char), qtd, saida);

    free(BUFFER);
    fclose(entrada);
    fclose(saida);
    
    return 0;
}