#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *entrada, *saida;

    entrada = fopen("arquivo_teste", "rb");
    saida = fopen("arquivo_saida", "wb");

    fseek(entrada, 0, SEEK_END);
    int tamanho = ftell(entrada);

    int qtd = (tamanho/sizeof(char)); // sizeof(char) == 1 -> qtd = tamanho 

    int *BUFFER = (int *)malloc(tamanho); 
    fread(BUFFER, sizeof(char), qtd, entrada);
    fwrite(BUFFER, sizeof(char), qtd, saida);

    free(BUFFER);
    fclose(entrada);
    fclose(saida);
    return 0;
}