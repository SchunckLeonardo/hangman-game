#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//Variaveis Globais
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

void abertura() {
    printf("****************\n");
    printf(" Jogo de Forca *\n");
    printf("****************\n\n");
}

void chuta() {
    //captura um novo chute
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra) {
    int achou = 0;
    
    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaForca() {

        int erros = chutesErrados();

        printf("  _______       \n");
        printf(" |/      |      \n");
        printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
            (erros>=1?'_':' '), (erros>=1?')':' '));
        printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
            (erros>=2?'|':' '), (erros>=3?'/': ' '));
        printf(" |       %c     \n", (erros>=2?'|':' '));
        printf(" |      %c %c   \n", (erros>=4?'/':' '), 
            (erros>=4?'\\':' '));
        printf(" |              \n");
        printf("_|___           \n");
        printf("\n\n");

    //imprime a palavra secreta
        for(int i = 0; i < strlen(palavraSecreta); i++) {

            //Verificando se o usuario ja chutou
            int achou = jaChutou(palavraSecreta[i]);

            if(achou) {
                printf("%c ", palavraSecreta[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");
}

void adicionaPalavra() {

    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", &quer);

    if(quer == 'S') {
        
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? \n");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1);
        }

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1);
    }

    int quantidadeDePalavras;
    fscanf(f, "%d", &quantidadeDePalavras);

    srand(time(0));
    int random = rand() % quantidadeDePalavras;

    for(int i = 0; i <= random; i++) {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int acertou() {
    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int chutesErrados() {
    int erros = 0;
        for(int i = 0; i < chutesDados; i++) {
            int existe = 0;

            for(int j = 0;j < strlen(palavraSecreta); j++) {
                if(chutes[i] == palavraSecreta[j]) {

                    existe = 1;
                    break;
                }
            }

            if(!existe) erros++;
        }
    
    return erros;
}

int enforcou() {

    return chutesErrados() >= 5;
}

int main() {

    escolhePalavra(palavraSecreta);
    abertura();

    do {
        desenhaForca(palavraSecreta, chutes, chutesDados);
        chuta(chutes, &chutesDados);

    } while(!acertou() && !enforcou());

    if(acertou()) {

    } else {

    }
    adicionaPalavra();
}