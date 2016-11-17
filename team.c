#include "team.h"
#include "sort.h"

TEAM initializeTeam(char* name, int id, int teamsNum) {
    TEAM team;
    int i;
    team.id = id;
    memcpy(team.name, name, strlen(name));
    team.name[strlen(name)] = '\0';
    team.wins = 0;
    team.draws = 0;
    team.goals_pro = 0;
    team.goals_con = 0;

    return team;
}

void printTeam(FILE* f, TEAM team) {
    fprintf(f, "%s %i %i %i %i\n", team.name, calculatePoints(team), team.wins, calculateGoals(team), team.goals_pro);
}

TEAM* getTeamByName(char* name, TEAM* teams, int num) {
    int i;
    for (i = 0; i < num; ++i) {
        if (!strcmp(teams[i].name, name)) return &teams[i];
    }
    return NULL;
}

void printRound(FILE* f, int round, TOURNAMENT t) {
    int i;
    fprintf( f, "%d\n", round);
    for (i = 0; i < t.teamsNum; ++i) { printTeam(f, t.teams[i]); }
}

void copyTeam(TEAM* a, TEAM* b) {
    a->id = b->id;
    memcpy(a->name, b->name, strlen(b->name));
    a->name[strlen(b->name)] = '\0';
    a->draws = b->draws;
    a->goals_con = b->goals_con;
    a->goals_pro = b->goals_pro;
    a->wins = b->wins;
}

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

int calculatePoints (TEAM team) { return team.wins * WIN_POINTS + team.draws; };
int calculateGoals (TEAM team) { return team.goals_pro - team.goals_con; };

