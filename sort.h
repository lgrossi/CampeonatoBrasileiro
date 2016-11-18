#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "main.h"

typedef struct TEAM TEAM;

int sort_cmp(TEAM *a, TEAM *b);

void shellSort(TEAM *array, int elements);

void quickSort(TEAM *teams, int len);

#endif // SORT_H_INCLUDED
