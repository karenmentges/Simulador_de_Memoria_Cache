#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT 10

typedef struct {
    int validade;
    int rotulo;
    int celula[4];
} Grade;

typedef struct {
    int FIFO;
    int miss;
    int hit;
} Cont;


// Função de Menu para a aplicação
int menu() {
    int op=0;

    printf("\n ________________________________________________\n");
    printf("\n  Menu                  \n");
    printf("\n  1 Ler um endereço da Memória\n");
    printf("  2 Escrever em um endereço da Memória\n");
    printf("  3 Apresentar conteúdo da Memória Principal\n");
    printf("  4 Apresentar conteúdo da Memória Cache\n");
    printf("  5 Apresentar Estatísticas\n");
    printf("\n  %d Encerar Programa\n", EXIT);
    printf("\n ________________________________________________\n\n");
    scanf("%d", &op);

    return op;
}


// Função que inicializa os dados da Memória
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

// Função que converte binário para decimal
int converteBD(int endbin){
    int enddec = 0;
    for(int i = 0; endbin > 0; i++) {
        enddec = enddec + (endbin % 10) * pow(2, i);
        endbin = endbin / 10;
    }
    return enddec;
}

// Função que busca um endereço na Memória
void buscaEndereco(Grade *MP, Grade *MC, int endereco, Cont *l){
    int contaux;
    int endbinbloco, endbincelula;
    int enddecbloco, enddeccelula;

    endbinbloco = floor(endereco / 100);
    enddecbloco = converteBD(endbinbloco);

    endbincelula = endereco % 100;
    enddeccelula = converteBD(endbincelula);

    for(int i=0; i<8; i++){
        if(MC[i].rotulo == enddecbloco){
            printf("\nValidade    Rótulo    Célula %d\n", enddeccelula);
            printf("    %d        0x%02x       0x%02x ", MC[i].validade, MC[i].rotulo, MC[i].celula[enddeccelula]);
            printf("\n");
            l->hit++;
            contaux = 0;
            break; 
        }
        else{
            contaux = 1;
        }
    }

    if(contaux == 1){
        l->miss++;
        for(int i=0; i<32; i++){
            if(MP[i].rotulo == enddecbloco){
                MC[l->FIFO] = MP[i];
                printf("\nValidade    Rótulo    Célula %d\n", enddeccelula);
                printf("    %d        0x%02x       0x%02x ", MC[l->FIFO].validade, MC[l->FIFO].rotulo, MC[l->FIFO].celula[enddeccelula]);
                printf("\n");
                l->FIFO++;
                break; 
            }
        }            
    }
}

// Função que imprime os dados da Memória Principal
void imprimeMP(Grade *MP){
    printf("\n");
    printf("Memória Principal:\n\n");
    printf("Bloco    Validade    Rótulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<32; j++){
        printf("0x%02x         %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", j, MP[j].validade, MP[j].rotulo, MP[j].celula[0], MP[j].celula[1], MP[j].celula[2], MP[j].celula[3]);
        printf("\n");
    }
    printf("\n");
}

// Função que imprime os dados da Memória Cache
void imprimeMC(Grade *MC){
    printf("\n");
    printf("Memória Cache:\n\n");
    printf("Validade    Rótulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<8; j++){
        printf("    %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", MC[j].validade, MC[j].rotulo, MC[j].celula[0], MC[j].celula[1], MC[j].celula[2], MC[j].celula[3]);
        printf("\n");
    }
    printf("\n");
}

int main(){

    int op, cont=0, endereco;
    Cont l = {0}, e = {0};
    Grade BlocosMP[32] = {0};
    Grade LinhasMC[8] = {0};

    // Inicialização da Memória Principal e da Memória Cache    
    inicializaMemoria(BlocosMP, 32);
    inicializaMemoria(LinhasMC, 8);

    // Impressão da Memória Principal e da Memória Cache
    imprimeMP(BlocosMP);
    imprimeMC(LinhasMC);
   

    while(op!=EXIT){
        op = menu();

        switch (op) {
            case 1:
                printf("Insira o endereço da memória em binário: ");
                scanf("%d", &endereco);
                buscaEndereco(BlocosMP, LinhasMC, endereco, &l);
                e.FIFO = l.FIFO;
                printf("\ncontmiss: %d\n", l.miss);
                printf("conthit: %d\n", l.hit);
                break;
            
            case 2:
                
                break;

            case 3:
                imprimeMP(BlocosMP);
                break;

            case 4:
                imprimeMC(LinhasMC);
                break;

            case 5:
                
                break;
    
            default:
                break;

        }   
    }
        

    return 0;

}