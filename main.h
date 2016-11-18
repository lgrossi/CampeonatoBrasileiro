#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#define __USE_C99_MATH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WIN_POINTS 3
#define TRUE  1
#define FALSE 0
#define MAX 100
#define DAYS 31
#define MONTHS 12

#include "sort.h"
#include "team.h"
#include "sbb.h"
#include "file.h"

/* Enum que representa a inclinação dos nós da SBB. */
enum TipoInclinacao { SBB_VERTICAL, SBB_HORIZONTAL };
/* Enum que representa os algorítmos de ordenação. */
enum sorting_t { QUICK_SORT = 1, SHELL_SORT };
/* Enum que representa os elementos de um jogo (data, time 1, gols do time 1, time 2 e gols do time 2). */
enum game { DATE, TEAM1, GOAL1, TEAM2, GOAL2 };

#endif // MAIN_H_INCLUDED
