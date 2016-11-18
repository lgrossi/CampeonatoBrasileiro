#include "sort.h"

/*
** Ordena o array via shellsort.
** @param array Array de times
** @param elements numero de times
*/
void shellSort(TEAM *array, int elements) {
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

/*
** Particiona o Array em sub-arrays.
** @param esq Index do elemento mais a esquerda.
** @param dir Index do elemento mais a direita.
** @param i Index que varre o subarray esquerdo.
** @param j Index que varre o subarray direito.
** @param array Array de times
*/
void particao (int esq, int dir, int *i, int *j, TEAM *array) {
        TEAM x, w;
        *i = esq; *j = dir;
        x = array[(*i + *j)/2]; /* obtem o pivo x */
    do {
        while (sort_cmp(&x, &array[*i]) > 0) (*i)++;
        while (sort_cmp(&x, &array[*j]) < 0) (*j)--;
        if (*i <= *j ) {
            w = array[*i];
            array[*i] = array[*j];
            array[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

/*
** Ordena o Array usando quicksort.
** @param esq Index do elemento mais a esquerda.
** @param dir Index do elemento mais a direita.
** @param array Array de times
*/
void ordena(int esq, int dir , TEAM *array)
{
    int i, j;
    particao (esq, dir, &i, &j, array);
    if (esq < j) ordena(esq, j, array);
    if (i < dir) ordena(i, dir, array);
}

/*
** Chama a ordenação via quicksort
** @param teams Array de times
** @param len Quantidade de times
*/
void quickSort(TEAM *teams, int len) {
    ordena(0, len-1, teams);
}

/*
** Comparador dos algorítimos de sorting.
** Pontuação, número de vitórias, saldo de gols,
** gols pró, nome.
** @param a Primeiro time
** @param b Segundo time
** @return 1 se a > b, 0 se a = b, -1 se a < b
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
