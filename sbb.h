#ifndef SBB_H_INCLUDED
#define SBB_H_INCLUDED

#include "main.h"

typedef struct HASH HASH;
typedef struct ArvoreSBB ArvoreSBB;
typedef struct GAME GAME;

/*
** Struct do tipo GAME: representa um conjunto de jogos, registro da SBB.
** key = chave do registro
** tam = tamanho do registro, n�mero de jogos que ele possui
** info = jogos
*/
struct GAME {
    int key;
    int tam;
    char info[MAX][MAX];
};

/*
** Struct do tipo ArvoreSBB: representa um n� da �rvore SBB.
** reg = registro que o n� armazena
** esq = apontador para o n� a esquerda
** dir = apontador para o n� a direita
** esqtipo = inclina��o do n� a esquerda
** dirtipo = inclina��o do n� a direita
*/
typedef struct ArvoreSBB {
    GAME reg;
    ArvoreSBB *esq, *dir;
    int esqtipo, dirtipo;
} ArvoreSBB;

/*
** Struct do tipo HASH: representa a tabela hash.
** tam = tamanho da tabela
** table = tabela de arvores SBB, onde os registros ser�o armazenados
*/
typedef struct HASH {
    int tam;
    ArvoreSBB *table;
} HASH;

GAME* createGame(char *info, int key);

HASH* criaHash(int t);

int funcaoHash(int key, HASH hash);

void destroiHash(HASH* hash);

void insereNaHash(HASH *h, GAME *x);

GAME* pesquisaNaHash(HASH* h, int key);

int dateToKey (char *date);

#endif // SBB_H_INCLUDED
