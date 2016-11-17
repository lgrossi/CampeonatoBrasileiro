#ifndef SBB_H_INCLUDED
#define SBB_H_INCLUDED

#include "team.h"

#define TRUE  1
#define FALSE 0
#define MAX 100
#define DAYS 31
#define MONTHS 12

typedef struct GAME GAME;

struct GAME {
    int key;
    int tam;
    char info[MAX][MAX];
};

typedef enum { SBB_VERTICAL, SBB_HORIZONTAL } TipoInclinacao;

typedef struct ArvoreSBB ArvoreSBB;
typedef struct ArvoreSBB {
    GAME reg;
    ArvoreSBB* esq, *dir;
    int esqtipo, dirtipo;
} ArvoreSBB;

typedef struct HASH HASH;
typedef struct HASH {
    int tam;
    ArvoreSBB *table;
} HASH;


GAME* createGame(char* info, int key);

HASH* criaHash(int t);

int funcaoHash(int key, HASH hash);

void destroiHash(HASH* hash);

void insereNaHash(HASH* h, GAME* x);

GAME* pesquisaNaHash(HASH* h, int key);


#endif // SBB_H_INCLUDED
