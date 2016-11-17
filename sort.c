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

void quickSort(TEAM teams[], int len, int size) {
    qsort(teams, len, size, sort_cmp);
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
