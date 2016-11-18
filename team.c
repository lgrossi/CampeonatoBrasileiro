#include "team.h"

/*
** Inicializa um time.
** @param name Nome do time
** @return team Time criado
*/
TEAM initializeTeam(char *name) {
    TEAM team;
    memcpy(team.name, name, strlen(name));
    team.name[strlen(name)] = '\0';
    team.wins = 0;
    team.draws = 0;
    team.goals_pro = 0;
    team.goals_con = 0;

    return team;
}

/*
** Escreve um time no arquivo.
** @param f Arquivo.
** @param team Time
*/
void printTeam(FILE *f, TEAM team) {
    fprintf(f, "%s %i %i %i %i\n", team.name, calculatePoints(team), team.wins, calculateGoals(team), team.goals_pro);
}

/*
** Recupera um time pelo nome.
** @param name Nome do time
** @param teams Times
** @return num Numero de Times
*/
TEAM *getTeamByName(char *name, TEAM *teams, int num) {
    int i;
    for (i = 0; i < num; ++i) {
        if (!strcmp(teams[i].name, name)) return &teams[i];
    }
    return NULL;
}

/*
** Escreve a rodada de um torneio no arquivo.
** @param f Arquivo.
** @param round Numero da rodada.
** @param t Torneio
*/
void printRound(FILE *f, int round, TOURNAMENT t) {
    int i;
    fprintf( f, "%d\n", round);
    for (i = 0; i < t.teamsNum; ++i) { printTeam(f, t.teams[i]); }
}

/*
** Calcula os pontos de um time.
** @param team Time
** @return pontos do time
*/
int calculatePoints (TEAM team) { return team.wins * WIN_POINTS + team.draws; };

/*
** Calcula o saldo de gols de um time.
** @param team Time
** @return saldo de gols do time
*/
int calculateGoals (TEAM team) { return team.goals_pro - team.goals_con; };

