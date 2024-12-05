#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_CEP 8

typedef struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[TAMANHO_CEP];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
}Endereco;

int comparaCep(const void*, const void*);

int main(void) {
    
    FILE *entrada, *saida;
    entrada = fopen("cep.dat", "rb");
    
    fseek(entrada, 0, SEEK_END);
    long tamanho = ftell(entrada);
    long qt = (tamanho / sizeof(Endereco));
    rewind(entrada);

    Endereco *buffer = (Endereco *)malloc(tamanho);
    fread(buffer, sizeof(Endereco), qt, entrada);
    fclose(entrada);

    qsort(buffer, qt, sizeof(Endereco), comparaCep);
    saida = fopen("meuCepOrdenado.dat", "wb");

    fwrite(buffer, sizeof(Endereco), qt, saida);
    fclose(saida);

    return 0;
}

int comparaCep(const void *e1, const void *e2) {
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, TAMANHO_CEP);
}