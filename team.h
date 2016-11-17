#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED
#define __USE_C99_MATH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WIN_POINTS 3


enum game { DATE, TEAM1, GOAL1, TEAM2, GOAL2 };

typedef struct TEAM TEAM;
typedef struct TOURNAMENT TOURNAMENT;

struct TEAM {
    int id;
    char name[25];
    int wins;
    int draws;
    int goals_pro;
    int goals_con;
};

struct TOURNAMENT {
    int hashSize;
    int choosedSort;
    int teamsNum;
    int roundsNum;
    int gamesPerRound;
    TEAM* teams;
};

TEAM initializeTeam(char* name, int id, int teamsNum);

TEAM* getTeamByName(char* name, TEAM* teams, int num);

void updateMatchData();

void printRound(FILE* f, int round, TOURNAMENT t);

int calculatePoints (TEAM team);

int calculateGoals (TEAM team);

void copyTeam (TEAM* a, TEAM* b);

void printTeam(FILE* f, TEAM team);

int dateToKey (char* date);

#endif // TEAM_H_INCLUDED
