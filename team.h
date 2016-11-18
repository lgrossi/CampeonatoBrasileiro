#ifndef TEAM_H_INCLUDED
#define TEAM_H_INCLUDED

#include "main.h"

typedef struct TOURNAMENT TOURNAMENT;
typedef struct TEAM TEAM;

/*
** Struct do tipo TEAM: representa um time do campeonato.
** name = nome do time
** wins = número de vitórias
** draws = número de empates
** goals_pro = gols feitos
** goals_con = gols sofridos
*/
struct TEAM {
    char name[25];
    int wins;
    int draws;
    int goals_pro;
    int goals_con;
};

/*
** Struct do tipo TOURNAMENT: representa o torneio
** hashSize = tamanho da hash table
** choosedSort = algorítmo de ordenação escolhido
** teamsNum = número de times
** roundsNum = número de rodadas
** gamesPerRound = número de jogos por rodada
** teams = times do campeonato
*/
struct TOURNAMENT {
    int hashSize;
    int choosedSort;
    int teamsNum;
    int roundsNum;
    int gamesPerRound;
    TEAM* teams;
};

TEAM initializeTeam(char *name);

TEAM* getTeamByName(char *name, TEAM *teams, int num);

void updateMatchData();

void printRound(FILE *f, int round, TOURNAMENT t);

int calculatePoints (TEAM team);

int calculateGoals (TEAM team);

void printTeam(FILE *f, TEAM team);

#endif // TEAM_H_INCLUDED
