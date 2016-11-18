#include "file.h"

/*
** Lê o arquivo de entrada, faz as operações necessárias para execuçao do programa.
** Responsável por criar as estruturas base do programa e fazer as chamadas das funções
** Inicializa e chama o arquivo de saída
** @param entrada Nome do arquivo de entrada
** @param saida Nome do arquivo de saida
*/
void readFile (char *entrada, char *saida) {
    TOURNAMENT tournament;
    char date[MAX/4], team1[MAX/4], team2[MAX/4], line[MAX], aux[MAX];
    int i, j, k, goalsT1, goalsT2, begin=0, step=0;
    FILE *fentrada, *fsaida;
    remove( saida );

    fentrada = fopen(entrada, "r");
    fsaida = fopen(saida, "a");

    if(fentrada == NULL) {
        printf("ERRO DE LEITURA DO ARQUIVO\n");
        return;
    }

    // Pega o tamanho da hash e o algorítmo de ordenação escolhido
    fgets(line, MAX, fentrada);
    line[strlen(line)] = line[strlen(line)-1] == '\n' ? line[strlen(line)] : '\n';
    for (i = 0; i < strlen(line); ++i) {
        if (line[i] == ';' || line[i] == '\n') {
            switch (step) {
                case 0:
                    tournament.hashSize = atoi(line + begin);
                    break;
                case 1:
                    tournament.choosedSort = atoi(line + begin);
                    break;
                default:
                    break;
            }
            ++step;
            begin = i + 1;
        }
    }

    // Cria a hash.
    HASH *hash = criaHash(tournament.hashSize);

    // Pega o número de times, rodadas e jogos por rodada.
    fgets(line, MAX, fentrada);
    line[strlen(line)] = line[strlen(line)-1] == '\n' ? line[strlen(line)] : '\n';
    for (i = begin = step = 0; i < strlen(line); ++i) {
        if (line[i] == ';' || line[i] == '\n') {
            switch (step) {
                case 0:
                    tournament.teamsNum = atoi(line + begin);
                    break;
                case 1:
                    tournament.roundsNum = atoi(line + begin);
                    break;
                case 2:
                    tournament.gamesPerRound = atoi(line + begin);
                    break;
                default:
                    break;
            }
            ++step;
            begin = i + 1;
        }
    }

    // Aloca os times.
    tournament.teams = malloc(sizeof(TEAM) * tournament.teamsNum);

    // Lê os nomes e cria os times.
    for (i = 0; i < tournament.teamsNum; ++i) {
        fgets(line, MAX, fentrada);
        line[strlen(line)-1] = line[strlen(line)-1] == '\n' ? '\0' : line[strlen(line)-1];
        tournament.teams[i] = initializeTeam(line);
    }

    // Le as rodadas.
    for (i = 0; i < tournament.roundsNum; ++i) {
        fgets(line, MAX, fentrada);
        // Le os jogos de cada rodada.
        for (j = 0; j < tournament.gamesPerRound; ++j) {
            memset(line,'\0',strlen(line));
            fgets(line, MAX, fentrada);
            line[strlen(line)] = line[strlen(line)-1] == '\n' ? line[strlen(line)] : '\n';
            memset(aux,'\0',strlen(aux));
            memset(date,'\0',strlen(date));
            memset(team1,'\0',strlen(team1));
            memset(team2,'\0',strlen(team2));
            goalsT1 = goalsT2 = begin = step = 0;
            // Pega data, times e gols de cada jogo.
            for (k = 0; k < strlen(line); ++k) {
                if (line[k] == ';' || line[k] == '\n') {
                    switch (step) {
                        case DATE:
                            memcpy(aux, line, strlen(line));
                            aux[strlen(line) - 1] = '\0';
                            memcpy(date, line + begin, k - begin);
                            date[k-begin] = '\n';
                            date[k-begin+1] = '\0';
                            insereNaHash(hash, createGame(aux, dateToKey(date)));
                            break;
                        case TEAM1:
                            memcpy(team1, line + begin, k - begin);
                            team1[k-begin] = '\0';
                            break;
                        case GOAL1:
                            goalsT1 = atoi(line + begin);
                            break;
                        case TEAM2:
                            memcpy(team2, line + begin, k - begin);
                            team2[k-begin] = '\0';
                            break;
                        case GOAL2:
                            goalsT2 = atoi(line + begin);
                            break;
                        default:
                            break;
                    }
                    ++step;
                    begin = k + 1;
                }
            }

            // Gera o resultado de cada jogo com base nos times e gols lidos.
            TEAM *t1 = getTeamByName(team1, tournament.teams, tournament.teamsNum);
            TEAM *t2 = getTeamByName(team2, tournament.teams, tournament.teamsNum);
            if (t1 != NULL && t2 != NULL) {
                if (goalsT1 > goalsT2) { t1->wins += 1; }
                else if (goalsT2 > goalsT1) { t2->wins += 1; }
                else { t1->draws += 1; t2->draws += 1; }
                t1->goals_pro += goalsT1;
                t1->goals_con += goalsT2;
                t2->goals_pro += goalsT2;
                t2->goals_con += goalsT1;
            }
        }
        // Ordena e printa as rodadas.
        tournament.choosedSort == SHELL_SORT ? shellSort(tournament.teams, tournament.teamsNum) : quickSort(tournament.teams, tournament.teamsNum);
        printRound(fsaida, i + 1, tournament);
    }

    // Libera memória dos times.
    free(tournament.teams);

    // Pesquisa os jogos na hash e escreve no arquivo
    while (!feof(fentrada)) {
        memset(line,'\0',strlen(line));
        fgets(line, MAX, fentrada);

        GAME *x = pesquisaNaHash(hash, dateToKey(line));
        for (i = 0; i < x->tam; ++i) {
            if (x->key != -1)
                fprintf(fsaida, "%s\n", x->info[i]);
        }
    }

    // Libera memória da hash.
    destroiHash(hash);
    fclose(fsaida);
    fclose(fentrada);
}
