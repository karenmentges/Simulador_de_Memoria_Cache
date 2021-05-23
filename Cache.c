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
    int num;
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
                if(l->FIFO == 7){
                    l->FIFO = 0;
                }
                else{
                    l->FIFO++;
                }
                break; 
            }
        }            
    }
}

// Função que escreve em um endereço na Memória
void escreveEndereco(Grade *MP, Grade *MC, int endereco, int valor, Cont *e){
    int contaux;
    int endbinbloco, endbincelula;
    int enddecbloco, enddeccelula;
    int valordec;

    endbinbloco = floor(endereco / 100);
    enddecbloco = converteBD(endbinbloco);

    endbincelula = endereco % 100;
    enddeccelula = converteBD(endbincelula);

    valordec = converteBD(valor);

    for(int i=0; i<8; i++){
        if(MC[i].rotulo == enddecbloco){
            MC[i].validade = 1;
            MC[i].celula[enddeccelula] = valordec;
            MP[enddecbloco] = MC[i];
            printf("\nValidade    Rótulo    Célula %d\n", enddeccelula);
            printf("    %d        0x%02x       0x%02x ", MC[i].validade, MC[i].rotulo, MC[i].celula[enddeccelula]);
            printf("\n");
            e->hit++;
            contaux = 0;
            break; 
        }
        else{
            contaux = 1;
        }
    }

    if(contaux == 1){
        e->miss++;
        for(int i=0; i<32; i++){
            if(MP[i].rotulo == enddecbloco){
                MC[e->FIFO] = MP[i];
                MC[e->FIFO].validade = 1;
                MC[e->FIFO].celula[enddeccelula] = valordec;
                MP[i] = MC[e->FIFO];
                printf("\nValidade    Rótulo    Célula %d\n", enddeccelula);
                printf("    %d        0x%02x       0x%02x ", MC[e->FIFO].validade, MC[e->FIFO].rotulo, MC[e->FIFO].celula[enddeccelula]);
                printf("\n");
                if(e->FIFO == 7){
                    e->FIFO = 0;
                }
                else{
                    e->FIFO++;
                }
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

void imprimeEstatisticas(Cont *l, Cont *e){
    double n1=l->num, n2=e->num, h1=l->hit, h2=e->hit, m1=l->miss, m2=e->miss;
    double res1, res2, res3, res4, res5;

    res1 = (h1/n1)*100;
    res2 = (m1/n1)*100;

    printf("\n");
    printf("Leitura\n");
    printf("______________________________\n\n");
    printf("Acessos:  %d\n", l->num);
    printf("Hit:      %d    %.2f%%\n", l->hit, res1);
    printf("Miss:     %d    %.2f%%\n", l->miss, res2);
    printf("\n");

    res1 = (h2/n2)*100;
    res2 = (m2/n2)*100;

    printf("\n");
    printf("Escrita\n");
    printf("______________________________\n\n");
    printf("Acessos:  %d\n", e->num);
    printf("Hit:      %d    %.2f%%\n", e->hit, res1);
    printf("Miss:     %d    %.2f%%\n", e->miss, res2);
    printf("\n");

    res1 = h1+h2;
    res2 = m1+m2;
    res3 = n1+n2;
    res4 = (res1/res3)*100;
    res5 = (res2/res3)*100;

    printf("\n");
    printf("Geral\n");
    printf("______________________________\n\n");
    printf("Acessos:  %d\n", l->num+e->num);
    printf("Hit:      %d    %.2f%%\n", l->hit+e->hit, res4);
    printf("Miss:     %d    %.2f%%\n", l->miss+e->miss, res5);
    printf("\n\n");
}

int main(){

    int op, cont=0, endereco, valor;
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
                l.num++;
                break;
            
            case 2:
                printf("Insira o endereço da memória em binário: ");
                scanf("%d", &endereco);
                printf("Insira o valor em binário: ");
                scanf("%d", &valor);
                escreveEndereco(BlocosMP, LinhasMC, endereco, valor, &e);
                l.FIFO = e.FIFO;
                e.num++;
                break;

            case 3:
                imprimeMP(BlocosMP);
                break;

            case 4:
                imprimeMC(LinhasMC);
                break;

            case 5:
                imprimeEstatisticas(&l, &e);
                break;
    
            default:
                break;

        }   
    }
        
    return 0;

}