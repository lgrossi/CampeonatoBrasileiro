#include "main.h"

/*
** Função principal, recebe os parâmetros externos de arquivo e chama a função de leitura.
** @params argc, argv
*/
int main()
{
    int i;
    char entrada[50], saida[50], txt[50], nentrada[50], nsaida[50];
    strcpy(entrada, "entrada");
    strcpy(saida, "saida");
    strcpy(txt, ".txt");

    for (i=1; i<9; i++){
        sprintf(nentrada, "%s%d%s", entrada, i, txt);
        printf("%s\n", nentrada);
        sprintf(nsaida, "%s%d%s", saida, i, txt);
        printf("%s\n", nsaida);
        readFile(nentrada, nsaida);
    }
    readFile("teste.txt", "saida.txt");
    return 0;
}
