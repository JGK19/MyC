#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_CEP 8
typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[TAMANHO_CEP];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int buscaLinear(char *, FILE *);
int buscaBinaria(char *, FILE *);
void printEndereco(Endereco);

int main(int argc, char **argv) {
    FILE *entrada;
    char cep[8];
    strcpy(cep, argv[1]);

    entrada = fopen("cep_ordenado.dat", "rb");

    int contador = buscaLinear(cep, entrada);
    int contador2 = buscaBinaria(cep, entrada);

    printf("total lido linear: %i\n", contador);
    printf("total lido binaria: %i\n", contador2);
    fclose(entrada);

    return 0;
}

void printEndereco(Endereco e) {
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
}

int buscaLinear(char *cep, FILE *file) {
    int contador = 0;
    Endereco endereco;

    int qtd = fread(&endereco, sizeof(Endereco), 1, file);
    while (qtd > 0) {
        contador++;
        if (strncmp(endereco.cep, cep, TAMANHO_CEP) == 0) {
            printEndereco(endereco);
            break;
        }
        qtd = fread(&endereco, sizeof(Endereco), 1, file);
    }

    return contador;
}

int buscaBinaria(char *cep, FILE *file) {
    int contador = 0;
    Endereco endereco;

    fseek(file, 0, SEEK_END);
    int tamanho = ftell(file);
    rewind(file);

    int inicio = 0;
    int fim = (tamanho / sizeof(Endereco)) - 1;
    int meio = (inicio + fim)/2;

    fseek(file, meio * sizeof(Endereco), SEEK_SET);
    fread(&endereco, sizeof(endereco), 1, file);

    while (inicio <= fim) {
        contador++;
        if (strncmp(endereco.cep, cep, TAMANHO_CEP) == 0) {
            printEndereco(endereco);
            return contador;
        } else if (strncmp(cep, endereco.cep, TAMANHO_CEP) < 0) {
            fim = meio - 1;
            meio = (inicio + fim)/2;
        } else if (strncmp(cep, endereco.cep, TAMANHO_CEP) > 0) {
            inicio = meio + 1;
            meio = (inicio + fim)/2;
        }
        fseek(file, meio * sizeof(Endereco), SEEK_SET);
        fread(&endereco, sizeof(endereco), 1, file);
    }

    return -1;

}