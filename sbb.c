#include <stdio.h>
#include <stdlib.h>
#include "sbb.h"

GAME* createGame(char* info, int key) {
    GAME *game;
    game = (GAME *)malloc(sizeof(GAME));
    game->key = key;
    game->tam = 1;
    memcpy(game->info[0], info, strlen(info));
    return game;
}

void ee(ArvoreSBB** ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *esq = no->esq;
    no->esq= esq->dir; // rotD(ptr)
    esq->dir= no;
    esq->esqtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr= esq;
}

void dd(ArvoreSBB** ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *dir= no->dir;
    no->dir= dir->esq;// rotE(ptr)
    dir->esq= no;
    dir->dirtipo= SBB_VERTICAL;
    no->dirtipo= SBB_VERTICAL;
    *ptr= dir;
}

void ed(ArvoreSBB** ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *esq = no->esq;
    ArvoreSBB *dir = esq->dir;
    esq->dir = dir->esq; // rotE(&(no->esq))
    dir->esq = esq;
    no->esq= dir->dir;// rotD(ptr)
    dir->dir = no;
    esq->dirtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr= dir;
}

void de(ArvoreSBB **ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *dir= no->dir;
    ArvoreSBB *esq= dir->esq;
    dir->esq= esq->dir;// rotD(&(no->dir))
    esq->dir= dir;
    no->dir= esq->esq;// rotE(ptr)
    esq->esq= no;
    dir->esqtipo= SBB_VERTICAL;
    no->dirtipo= SBB_VERTICAL;
    *ptr= esq;
}

void iInsere(GAME *reg, ArvoreSBB **ptr, int *incli, bool *fim) {
    if(*ptr == NULL) {
        iInsereAqui(reg, ptr, incli, fim);
    }
    else if(reg->key < (*ptr)->reg.key) {
        iInsere(reg, &(*ptr)->esq, &(*ptr)->esqtipo, fim);
        if(*fim)
            return;
        if((*ptr)->esqtipo == SBB_VERTICAL) {
            *fim = true;
        }
        else if((*ptr)->esq->esqtipo == SBB_HORIZONTAL) {
            ee(ptr);
            *incli = SBB_HORIZONTAL;
            return;
        }
        else if((*ptr)->esq->dirtipo == SBB_HORIZONTAL) {
            ed(ptr);
            *incli = SBB_HORIZONTAL;
            return;
        }
        return;
    }
    else if(reg->key > (*ptr)->reg.key) {
        iInsere(reg, &((*ptr)->dir), &((*ptr)->dirtipo), fim);
        if(*fim)
            return;
        if((*ptr)->dirtipo == SBB_VERTICAL)  {
            *fim = true;
            return;
        }
        else if((*ptr)->dir->dirtipo== SBB_HORIZONTAL) {
            dd(ptr); *incli= SBB_HORIZONTAL;
            return;
        }
        else if((*ptr)->dir->esqtipo == SBB_HORIZONTAL) {
            de(ptr); *incli= SBB_HORIZONTAL;
            return;
        }
    }
    else if (reg->key == (*ptr)->reg.key) {
        memcpy((*ptr)->reg.info[(*ptr)->reg.tam], reg->info, strlen(reg->info));
        ++(*ptr)->reg.tam;
    }
    else {
        *fim = true;
    }
    return;
}

void iInsereAqui(GAME  *reg, ArvoreSBB **ptr, int *incli, int *fim) {
    ArvoreSBB *no = malloc(sizeof(ArvoreSBB));
    no->reg = *reg;
    no->esq = NULL;
    no->dir = NULL;
    no->esqtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = no;

    *incli = SBB_HORIZONTAL;
    *fim = false;
}

void insereElementoSBB(ArvoreSBB **raiz, GAME *reg) {
    int fim = false;
    int inclinacao = SBB_VERTICAL;
    iInsere(reg, raiz, &inclinacao, &fim);
}

void inicializa(ArvoreSBB *raiz) {
    raiz = NULL;
}

GAME* sbbPesquisa(ArvoreSBB **p, int key) {
    if (*p == NULL)
        return createGame("null", -1);
    if (key < (*p)->reg.key)
        return sbbPesquisa(&(*p)->esq, key);
    if (key > (*p)->reg.key)
        return sbbPesquisa(&(*p)->dir, key);
    return &(*p)->reg;
}

void destroiSbb(ArvoreSBB **p) {
    if (*p == NULL)
        return;
    if ((*p)->esq != NULL)
        return destroiSbb(&(*p)->esq);
    if ((*p)->dir != NULL)
        return destroiSbb(&(*p)->dir);

    free(&(*p)->reg);
    free(*p);
    return;
}

void destroiHash(HASH* hash) {
    int i;
    for (i = 0; i < hash->tam; ++i) {
        destroiSbb(&hash->table[i]);
    }
    free(hash->table);
    free(hash);
}

HASH* criaHash(int t) {
    int i;
    HASH* hash = (HASH *)malloc(sizeof(HASH));
    hash->tam = t;
    hash->table = malloc(t * sizeof(ArvoreSBB));
    return hash;
}

int funcaoHash(int key, HASH hash) {
    int dia, mes, ano;

    dia = key / 1000000;
    mes = (key - dia*1000000)/10000;
    ano = (key - dia*1000000 - mes*10000);

    return (dia + mes*DAYS + ano*MONTHS*DAYS)%hash.tam;
}

void insereNaHash(HASH* h, GAME* x) {
    int posicao = funcaoHash(x->key, *h);
    insereElementoSBB(&h->table[posicao], x);
    GAME* game = sbbPesquisa(&h->table[posicao], x->key);
}

GAME* pesquisaNaHash(HASH* h, int key) {
    int posicao = funcaoHash(key, *h);
    sbbPesquisa(&h->table[posicao], key);
}
