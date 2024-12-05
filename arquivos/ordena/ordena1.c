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
void intercala(FILE *, FILE *, char *);

int main(void) {
    
    FILE *entrada, *saida_primeira, *saida_segunda;
    entrada = fopen("cep.dat", "rb");
    
    fseek(entrada, 0, SEEK_END);
    long tamanho = ftell(entrada);
    long qt = (tamanho / sizeof(Endereco));
    rewind(entrada);

    // calcula quantidade de elementos de cada metade do arquivo
    long metade = tamanho/2;
    long qt_primeiro = metade/sizeof(Endereco);
    long qt_segundo = (tamanho - metade)/sizeof(Endereco);

    // aloca memoria para cada arquivo
    Endereco *buffer_primeiro = (Endereco *)malloc(metade);
    Endereco *buffer_segundo = (Endereco *)malloc(tamanho - metade);

    // le cada metade do arquivo orginal
    fread(buffer_primeiro, sizeof(Endereco), qt_primeiro, entrada);
    fread(buffer_segundo, sizeof(Endereco), qt_segundo, entrada);
    fclose(entrada);

    // ordena cada metade dos arquivos
    qsort(buffer_primeiro, qt_primeiro, sizeof(Endereco), comparaCep);
    qsort(buffer_segundo, qt_segundo, sizeof(Endereco), comparaCep);

    saida_primeira = fopen("primeiraMetade.dat", "wb");
    saida_segunda = fopen("segundaMetade.dat", "wb");

    // escreve cada metade ordenada
    fwrite(buffer_primeiro, sizeof(Endereco), qt_primeiro, saida_primeira);
    fwrite(buffer_segundo, sizeof(Endereco), qt_segundo, saida_segunda);

    // fecha arquivos e libera memoria alocada
    fclose(saida_primeira);
    fclose(saida_segunda);
    free(buffer_primeiro);
    free(buffer_segundo);

    FILE *arquivo1, *arquivo2;

    arquivo1 = fopen("primeiraMetade.dat", "rb");
    arquivo2 = fopen("segundaMetade.dat", "rb");

    intercala(arquivo1, arquivo2, "mergeCepOrdenado.dat");

    return 0;
}

int comparaCep(const void *e1, const void *e2) {
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, TAMANHO_CEP);
}

void intercala(FILE *arquivo1, FILE *arquivo2, char *nome) {
    
}