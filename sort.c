#include "sort.h"

void shellSort(TEAM* array, int elements) {
   int inner, outer;
   TEAM valueToInsert;
   int interval = 1;
   int i = 0;

   while(interval <= elements/3) {
      interval = interval*3 +1;
   }

   while(interval > 0) {
      for(outer = interval; outer < elements; outer++) {
         valueToInsert = array[outer];
         inner = outer;

         while(inner > interval -1 && sort_cmp(&array[inner - interval], &valueToInsert) >= 0) {
            array[inner] = array[inner - interval];
            inner -=interval;
         }

         array[inner] = valueToInsert;
      }

      interval = (interval -1) /3;
      i++;
   }
}

void particao (int Esq, int Dir, int *i, int *j, TEAM *A) {
        TEAM x, w;
        *i = Esq; *j = Dir;
        x = A[(*i + *j)/2]; /* obtem o pivo x */
    do {
        while (sort_cmp(&x, &A[*i]) > 0) (*i)++;
        while (sort_cmp(&x, &A[*j]) < 0) (*j)--;
        if (*i <= *j ) {
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void ordena(int Esq, int Dir , TEAM *A)
{
    int i, j;
    particao (Esq, Dir, &i, &j, A);
    if (Esq < j) ordena(Esq, j, A);
    if (i < Dir) ordena(i, Dir, A);
}

void quickSort(TEAM teams[], int len, int size) {
    ordena(0, len-1, teams);
}

/*
** Comparador dos algorítimos de sorting.
** Pontuação, número de vitórias, saldo de gols,
** gols pró, confronto direto, nome.
*/
int sort_cmp(TEAM *a, TEAM *b) {
    int cmp = calculatePoints(*b) - calculatePoints(*a);
    if (cmp != 0) { return cmp; }

    cmp = b->wins - a->wins;
    if (cmp != 0) { return cmp; }

    cmp = calculateGoals(*b) - calculateGoals(*a);
    if (cmp != 0) { return cmp; }

    cmp = b->goals_pro - a->goals_pro;
    if (cmp != 0) { return cmp; }


    return strcmp(a->name, b->name);
}
