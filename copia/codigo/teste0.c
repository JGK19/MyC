#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

void randArray(int *, int);

int main(void) {

    int array[N];
    randArray(array, N);

    FILE *f = fopen("arquivo_teste", "wb");
    fwrite(array, sizeof(int), N, f);
    fclose(f);


    return 0;
}

void randArray(int array[], int n) {
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        array[i] = rand();
        printf("%i\n", array[i]);
    }
}
