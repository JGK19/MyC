#include <stdio.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

void printEndereco(Endereco e) {
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
}

int main(void) {
    FILE *entrada;

    entrada = fopen("cep_ordenado.dat", "rb");

    fseek(entrada, 0, SEEK_END);
    int tamanho = ftell(entrada);
    rewind(entrada); // fseek(entrada, 0, SEEK_SET);

    int qtd = tamanho / sizeof(Endereco);

    Endereco *BUFFER = (Endereco *)malloc(tamanho);

    fread(BUFFER, sizeof(Endereco), qtd, entrada);

    printEndereco(BUFFER[370345]);

    free(BUFFER);
    fclose(entrada);

    return 0;
}