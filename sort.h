#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "team.h"

enum sorting_t { QUICK_SORT = 1, SHELL_SORT };

int sort_cmp(TEAM *a, TEAM *b);

void shellSort(TEAM* array, int elements);

void quickSort(TEAM teams[], int len, int size);

#endif // SORT_H_INCLUDED
