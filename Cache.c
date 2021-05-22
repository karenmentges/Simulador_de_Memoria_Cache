#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int validade;
    int rotulo;
    int celula[4];
} Grade;


void inicializaMemoria(Grade B[], int x){
    int num1 = 0, num2 = 0;
    for(int j=0; j<x; j++){
        B[j].validade = 0;
        B[j].rotulo = num1;
        num1++;
        for(int i=0; i<4; i++){
            B[j].celula[i] = num2;
            num2++;
        }
    }
}

int main(){

    Grade BlocosMP[32] = {0};
    Grade LinhasCache[8] = {0};
    
    inicializaMemoria(BlocosMP, 32);
    inicializaMemoria(LinhasCache, 8);

    printf("\n");
    printf("Memória Principal:\n\n");
    printf("Bloco    Validade    Rotulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<32; j++){
        printf("0x%02x         %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", j, BlocosMP[j].validade, BlocosMP[j].rotulo, BlocosMP[j].celula[0], BlocosMP[j].celula[1], BlocosMP[j].celula[2], BlocosMP[j].celula[3]);
        printf("\n");
    }
    printf("\n");

    printf("\n");
    printf("Cache:\n\n");
    printf("Validade    Rotulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<8; j++){
        printf("    %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", LinhasCache[j].validade, LinhasCache[j].rotulo, LinhasCache[j].celula[0], LinhasCache[j].celula[1], LinhasCache[j].celula[2], LinhasCache[j].celula[3]);
        printf("\n");
    }
    printf("\n");


    return 0;

}