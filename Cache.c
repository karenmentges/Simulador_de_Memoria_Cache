#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int celula[8];
} Celula;

typedef struct {
    int rotulo[8];
    Celula celulas[4];
} Bloco;

typedef struct {
    Bloco Linhas[8];
} Cache;


Celula converteDB(int d){
    Celula aux = {0}, numbin = {0};
    int i=0, k=7;
    
    while(d > 0) {
		aux.celula[i] = d % 2;
		d = d / 2;
        i++;
	}
    for(int j = 0; j<8; j++){
        numbin.celula[k] = aux.celula[j];
        k--;
    }
    for(int l = k+1; l>=0; l--){
        numbin.celula[l] = 0;
    }

    return numbin;
}


void *inicializaMemoria(Bloco *MP){
    int num1 = 0;
    int num2 = 0;
    Celula numbin;
    for(int j=0; j<32; j++){
        numbin = converteDB(num1);
        for(int k=0; k<8; k++){
            MP[j].rotulo[k] = numbin.celula[k];
        }
        for(int i=0; i<4; i++){
            MP[j].celulas[i] = converteDB(num2);
            num2++;
        }
        num1++;
    }
}

int main(){

    Bloco MP[32] = {0};
    
    inicializaMemoria(MP);

    for(int j=0; j<32; j++){
        printf("Bloco %d\n", j);
        printf("\tRótulo: ");
        for(int i=0; i<8; i++){
            printf("%d", MP[j].rotulo[i]);
        }
        printf("\n");
        printf("\tCélulas: \n");
        for(int k=0; k<4; k++){
            printf("\t\tCélula %d: ", k);
            for(int l=0; l<8; l++){
                printf("%d", MP[j].celulas[k].celula[l]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;

}