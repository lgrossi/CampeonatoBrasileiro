#include "sbb.h"

/*
** Cria uma estrutura do tipo GAME.
** @param info Informação inicial contida no GAME
** @param key Chave do registro
*/
GAME *createGame(char *info, int key) {
    GAME *game;
    game = (GAME *)malloc(sizeof(GAME));
    game->key = key;
    game->tam = 1;
    memcpy(game->info[0], info, strlen(info));
    return game;
}

/*
** As funções ee, dd, ed e de a seguir realizam as
** transformações da SBB afim de manter as características
** fundamentais exigidas no escopo e que definem a estrutura SBB.
** @param ptr Apontador para um nó da árvore.
*/
void ee(ArvoreSBB **ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *esq = no->esq;
    no->esq= esq->dir; // rotD(ptr)
    esq->dir= no;
    esq->esqtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr= esq;
}
void dd(ArvoreSBB **ptr) {
    ArvoreSBB *no = *ptr;
    ArvoreSBB *dir= no->dir;
    no->dir= dir->esq;// rotE(ptr)
    dir->esq= no;
    dir->dirtipo= SBB_VERTICAL;
    no->dirtipo= SBB_VERTICAL;
    *ptr= dir;
}
void ed(ArvoreSBB **ptr) {
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

/*
** Encontra o local adequado para inserir um dado elemento na árvore.
** @param reg Registro a ser inserido
** @param ptr Apontador para um nó da árvore.
** @param incli Inclinação do nó que conterá o registro que será inserido.
** @param fim Boolean que indica se chegou ou não ao fim de um ramo da árvore.
*/
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

/*
** Insere o registro no nó especificado.
** @param reg Registro a ser inserido
** @param ptr Apontador para o nó que vai receber o registro
** @param incli Inclinação do nó dado.
** @param fim Boolean que indica se chegou ou não ao fim de um ramo da árvore.
*/
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

/*
** Faz a chamada do processo de inserir um registro na árvore.
** @param raiz Raiz da árvore
** @param reg Registro a ser inserido
*/
void insereElementoSBB(ArvoreSBB **raiz, GAME *reg) {
    int fim = false;
    int inclinacao = SBB_VERTICAL;
    iInsere(reg, raiz, &inclinacao, &fim);
}

/*
** Inicializa uma árvore.
** @param raiz Raiz da árvore (nó 0)
*/
void inicializa(ArvoreSBB *raiz) {
    raiz = NULL;
}

/*
** Pesquisa um registro na árvore dada uma chave.
** @param p Raíz da árvore onde a busca será realizada
** @param key Chave do registro a ser buscado
** @return reg Registro encontrado, do tipo GAME.
*/
GAME *sbbPesquisa(ArvoreSBB **p, int key) {
    if (*p == NULL)
        return createGame("null", -1);
    if (key < (*p)->reg.key)
        return sbbPesquisa(&(*p)->esq, key);
    if (key > (*p)->reg.key)
        return sbbPesquisa(&(*p)->dir, key);
    return &(*p)->reg;
}

/*
** Libera memória da árvore.
** @param p Raíz da árvore a ser liberada
*/
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

/*
** Libera memória da tabela hash.
** @param hash Tabela hash a ser liberada
*/
void destroiHash(HASH *hash) {
    int i;
    for (i = 0; i < hash->tam; ++i) {
        destroiSbb(&hash->table[i]);
    }
    free(hash->table);
    free(hash);
}

/*
** Cria uma tabela hash.
** @param t Tamanho da tabela
** @return hash Tabela criada
*/
HASH *criaHash(int t) {
    int i;
    HASH *hash = (HASH *)malloc(sizeof(HASH));
    hash->tam = t;
    // Aloca a tabela do tamanho dado, onde cada index corresponde a uma árvore de busca.
    hash->table = malloc(t  *sizeof(ArvoreSBB));
    return hash;
}

/*
** Função feita para otimizar a busca na tabela hash, transformando a chave em um index
** O objetivo aqui é diminuir o número de colisões - uma vez que no trabalho proposto elas são inevitáveis
** Criou-se uma função afim de colocar o menor número de registros por indexes, possível
** Isso é, no mundo ideal, todos os indexes terem o mesmo número de registros.
** @param key Chave a ser transformada em index
** @param hash Tabela hash
** @return index Index da tabela correspondente a chave dada
*/
int funcaoHash(int key, HASH hash) {
    int dia, mes, ano;

    dia = key / 1000000;
    mes = (key - dia*1000000)/10000;
    ano = (key - dia*1000000 - mes*10000);

    return (dia + mes*DAYS + ano*MONTHS*DAYS)%hash.tam;
}

/*
** Chamada de inserção de um registro na tabela hash.
** @param h Tabela hash
** @param x Registro do tipo GAME
*/
void insereNaHash(HASH *h, GAME *x) {
    int posicao = funcaoHash(x->key, *h);
    insereElementoSBB(&h->table[posicao], x);
    GAME *game = sbbPesquisa(&h->table[posicao], x->key);
}

/*
** Chamada de pesquisa na tabela Hash.
** @param h Tabela hash
** @param key Chave do registro a ser buscado
** @return registro do tipo GAME encontrado
*/
GAME *pesquisaNaHash(HASH *h, int key) {
    int posicao = funcaoHash(key, *h);
    sbbPesquisa(&h->table[posicao], key);
}

/*
** Transforma uma data em chave do registro do tipo GAME.
** @param date Data
** @return key Chave do jogo
*/
int dateToKey(char date[25]) {
    int step, begin, i, key;
    for (i = step = begin = key = 0; i < strlen(date); ++i) {
        if (date[i] == '/') {
            key *= 100;
            key += atoi (date + begin);
            ++step;
            begin = i + 1;
        }
        else if (i == strlen(date) - 1) {
            key *= 10000;
            key += atoi (date + begin);
            ++step;
            begin = i + 1;
        }
    }
    return key;
}
