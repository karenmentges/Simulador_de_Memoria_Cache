typedef struct {
    unsigned char celula[8];
} Celula;

typedef struct {
    int rotulo;
    Celula celulas[4];
} Bloco;

typedef struct {
    Bloco Linhas[8];
} Cache;

typedef struct {
    Bloco bloco[32];
} MemoriaPrincipal;
