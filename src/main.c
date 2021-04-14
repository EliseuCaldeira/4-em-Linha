/**
 * Autor: EliseuCaldeira
 * Version: 1.0.0
 */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rlutil.h"
#define COLUNAS 7
#define LINHAS 6

//BOOL para saber se o programa deve parar
int exit_program = 0;
//BOOL para saber se o programa deve processar input; colocar a 0 para fazer anima‡”es, por exemplo.
int expect_input = 1;
/**
 * Estado do jogo:
 * 0 -> Menu inicial
 * 1 -> Novo jogo
 * 2 -> Durante o jogo
 * 3 -> Fim do jogo
 */
int state = 0;
/**
 * tabuleiro[COLUNAS][LINHAS]
 * Cont‚m o local das pe‡as no tabuleiro vertical do jogo
 * 0 -> casa vazia
 * 1 -> pe‡a amarela
 * 2 -> pe‡a azul
 */
int tabuleiro[COLUNAS][LINHAS];
/**
 * De quem ‚ a vez de jogar:
 * (ou quem ‚ o vencedor caso state == 3)
 * (por isso deve de ser reiniciada a 1 sempre que state == 1)
 * 0 -> Ningu‚m
 * 1 -> Pe‡as amarelas
 * 2 -> Pe‡as azuis
 */
int turno = 0;
//Um contador que ‚ reposto quando novo jogo; Serve para anima‡äes, por exemplo
int count = 0;
/**
 * As coordenadas da sequˆncia vencedora
 * [n] [0]: coluna
 * [n] [1]: linha
 */
int sequencia_vencedora[4][2];
//Cont‚m poss¡veis mensagens de erro, como por exemplo, quando se introduz uma op‡„o inv lida
char err_msg[255] = "";

void draw_screen();
void process_input();
/**
 * Verifica se h  vit¢ria ou empate
 * Retorna:
 * 0 se n„o h  nem vit¢ria nem empate
 * 1 se houve vit¢ria ou empate
 */
int vitoria_ou_empate();
//Coloca pe‡a da cor da vari vel global turno, na coluna correspondente
void jogar(int coluna);

int main() {
    system("mode con:cols=44 lines=22");
    system("color 0f");
    system("chcp 860");

    //Game Loop:
    while (!exit_program) {
        //Draw:
        system("cls");//limpar ecr„
        draw_screen();//desenhar ecr„
        //Process Input:
        if(expect_input) {
            process_input();
        }
        //Sleep (16 667 micro-segundos s„o 60 fps):
        usleep(16667);
    }

    //Sair do jogo
    setColor(WHITE);
    printf("\nO programa vai parar...");
    usleep(2000000);//2 segundos
    return 0;
}

void draw_screen(){
//printf("12345678901234567890123456789012345678901234");//referˆncia de largura de ecr„
    switch(state) {
    case 1:
        turno = 1;
        count = 0;
        for(int linha = 0; linha < LINHAS; linha++) {
            for(int coluna = 0; coluna < COLUNAS; coluna++) {
                tabuleiro[coluna][linha] = 0;
            }
        }
        state = 2;
        expect_input = 0;
        break;
    case 2:
        printf("\n");
        setColor(WHITE);
        printf("             a vez das ");
        if(turno == 2) {
            setColor(LIGHTCYAN);
            printf("azuis\n\n");
        }
        else {
            setColor(YELLOW);
            printf("amarelas\n\n");
        }
        printf("            1  2  3  4  5  6  7\n");
        printf("            ³  ³  ³  ³  ³  ³  ³\n");
        printf("            V  V  V  V  V  V  V\n");
        for(int linha = 0; linha < LINHAS; linha++) {
            setColor(DARKGREY);
            printf("           º");
            for(int coluna = 0; coluna < COLUNAS; coluna++) {
                switch(tabuleiro[coluna][linha]) {
                case 1:
                    setColor(YELLOW);
                    break;
                case 2:
                    setColor(LIGHTCYAN);
                    break;
                default:
                    setColor(BLACK);
                    break;
                }
                printf("ÛÛ");
                setColor(DARKGREY);
                printf("º");
            }
            setColor(DARKGREY);
            printf("           ");
            if(linha == LINHAS-1) {
                printf("           ÈÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍ¼\n");
            }
            else {
                printf("           ÌÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍ¹\n");
            }
        }
        setColor(DARKGREY);
        expect_input = 1;
        break;
    case 3:
        if(count < 6) {
            count++;
        }
        printf("\n");
        setColor(WHITE);
        if(turno) {
            printf("            Ganharam as ");
            if(turno == 2) {
                setColor(LIGHTCYAN);
                printf("azuis\n\n");
            }
            else {
                setColor(YELLOW);
                printf("amarelas\n\n");
            }
        }
        else {
            if(count % 2){
                printf("           O jogo ficou\n\n");
            }
            else {
                printf("           O jogo ficou empatado\n\n");
            }
        }
        if(count < 6) {
            printf("\n\n\n");
        }
        else {
            setColor(GREEN);
            printf("1 <- Voltar ao menu inicial\n");
            printf("Para sair a qualquer momento, prima x\n\n");
        }
        for(int linha = 0; linha < LINHAS; linha++) {
            setColor(DARKGREY);
            printf("           º");
            for(int coluna = 0; coluna < COLUNAS; coluna++) {
                switch(tabuleiro[coluna][linha]) {
                case 1:
                    setColor(YELLOW);
                    break;
                case 2:
                    setColor(LIGHTCYAN);
                    break;
                default:
                    setColor(BLACK);
                    break;
                }
                int pertence_a_sequencia_vencedora = 0;
                for(int n = 0; n < 4; n++) {
                    if(sequencia_vencedora[n][0] == coluna && sequencia_vencedora[n][1] == linha) {
                        pertence_a_sequencia_vencedora = 1;
                    }
                }
                if(turno && pertence_a_sequencia_vencedora && count % 2) {
                    setColor(BLACK);
                }
                printf("ÛÛ");
                setColor(DARKGREY);
                printf("º");
            }
            setColor(DARKGREY);
            printf("           ");
            if(linha == LINHAS-1) {
                printf("           ÈÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍÊÍÍ¼\n");
            }
            else {
                printf("           ÌÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍÎÍÍ¹\n");
            }
        }
        setColor(DARKGREY);
        if(count < 6) {
            expect_input = 0;
            usleep(500000);
        }
        else {
            expect_input = 1;
        }
        break;
    default:
        printf("\n\n\n");
        setColor(LIGHTCYAN);
        printf("               4 EM LINHA\n\n");
        setColor(MAGENTA);
        printf("Para fazer uma escolha, basta premir a tecla");
        printf("do caractere correspondente.\n");
        printf("N„o precisa fazer ENTER no fim.\n\n");
        setColor(GREEN);
        printf("1 <- Novo jogo local (2 jogadores humanos)\n");
        printf("Para sair a qualquer momento, prima x\n\n");
        setColor(DARKGREY);
        printf("Introduza a sua escolha\n");
        expect_input = 1;
        break;
    }
    //Mostrar eventual mensagem de erro
    setColor(LIGHTRED);
    printf("%s\n", err_msg);
    strcpy(err_msg, "");//depois de a mostrar, voltamos a limp -la
    setColor(BLACK);
}

void process_input() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//limpar buffer
    //printf("\a");//dar um sinal sonoro
    int input = getch();//guardar tecla premida em input
    switch(state) {
    case 1:
        break;
    case 2:
        switch(input) {
        case '1':
            jogar(1);
            break;
        case '2':
            jogar(2);
            break;
        case '3':
            jogar(3);
            break;
        case '4':
            jogar(4);
            break;
        case '5':
            jogar(5);
            break;
        case '6':
            jogar(6);
            break;
        case '7':
            jogar(7);
            break;
        default:
            sprintf(err_msg, "\"%c\" ‚ uma sele‡„o inv lida!", input);
            break;
        }
        if(vitoria_ou_empate()) {
            state = 3;
        }
        break;
    case 3:
        switch(input) {
        case '1':
            state = 0;
            break;
        default:
            sprintf(err_msg, "\"%c\" ‚ uma sele‡„o inv lida!", input);
            break;
        }
        break;
    default:
        switch(input) {
        case '1':
            state = 1;
            break;
        default:
            sprintf(err_msg, "\"%c\" ‚ uma sele‡„o inv lida!", input);
            break;
        }
        break;
    }
    if(input == 'x' || input == 'X') {
        exit_program = 1;
        expect_input = 0;
    }
}

int vitoria_ou_empate() {
    //BOOL para saber se ainda h  posi‡”es livres; serve para calcular se h  empate
    int posicoes_livres = 0;
    for(int coluna = 0; coluna < COLUNAS; coluna++) {
        if(!tabuleiro[coluna][0]) {
            posicoes_livres = 1;
            break;
        }
    }
    /**
     * 0 -> Ningu‚m
     * 1 -> Pe‡as amarelas
     * 2 -> Pe‡as azuis
     */
    int pretendente_atual = 0;
    //Em quantas pe‡as seguidas do pretendente_atual j  vamos? Se 4, pretendente_atual ganha
    int seguidas = 0;
    //Verificar linhas:
    for(int linha = 0; linha < LINHAS; linha++) {
        for(int coluna = 0; coluna < COLUNAS; coluna++) {
            if(tabuleiro[coluna][linha] == pretendente_atual) {
                seguidas++;
            }
            else if (tabuleiro[coluna][linha]) {
                seguidas = 1;
            }
            if(seguidas > 0 && seguidas <= 4){
                sequencia_vencedora[seguidas-1][0] = coluna;
                sequencia_vencedora[seguidas-1][1] = linha;
            }
            pretendente_atual = tabuleiro[coluna][linha];
            if(seguidas == 4 && pretendente_atual) {
                turno = pretendente_atual;
                return 1;
            }
        }
        pretendente_atual = 0;
        seguidas = 0;
    }
    //Verificar colunas:
    pretendente_atual = 0;
    seguidas = 0;
    for(int coluna = 0; coluna < COLUNAS; coluna++) {
        for(int linha = 0; linha < LINHAS; linha++) {
            if(tabuleiro[coluna][linha] == pretendente_atual) {
                seguidas++;
            }
            else if (tabuleiro[coluna][linha]) {
                seguidas = 1;
            }
            if(seguidas > 0 && seguidas <= 4){
                sequencia_vencedora[seguidas-1][0] = coluna;
                sequencia_vencedora[seguidas-1][1] = linha;
            }
            pretendente_atual = tabuleiro[coluna][linha];
            if(seguidas == 4 && pretendente_atual) {
                turno = pretendente_atual;
                return 1;
            }
        }
        pretendente_atual = 0;
        seguidas = 0;
    }
    //Verificar diagonais "\":
    pretendente_atual = 0;
    seguidas = 0;
    for(int coluna_referencia = -2; coluna_referencia < COLUNAS-3; coluna_referencia++) {
        int coluna = 0;
        int linha = 0;
        if(coluna_referencia < 0) {
            linha = abs(coluna_referencia);
        }
        else {
            coluna = coluna_referencia;
        }
        for( ; linha < LINHAS && coluna < COLUNAS ; linha++, coluna++) {
            if(tabuleiro[coluna][linha] == pretendente_atual) {
                seguidas++;
            }
            else if (tabuleiro[coluna][linha]) {
                seguidas = 1;
            }
            if(seguidas > 0 && seguidas <= 4){
                sequencia_vencedora[seguidas-1][0] = coluna;
                sequencia_vencedora[seguidas-1][1] = linha;
            }
            pretendente_atual = tabuleiro[coluna][linha];
            if(seguidas == 4 && pretendente_atual) {
                turno = pretendente_atual;
                return 1;
            }
        }
        pretendente_atual = 0;
        seguidas = 0;
    }
    //Verificar diagonais "/":
    pretendente_atual = 0;
    seguidas = 0;
    for(int coluna_referencia = 8; coluna_referencia > 2; coluna_referencia--) {
        int coluna = 6;
        int linha = 0;
        if(coluna_referencia >= COLUNAS) {
            linha = coluna_referencia - COLUNAS + 1;
        }
        else {
            coluna = coluna_referencia;
        }
        for( ; linha < LINHAS && coluna >= 0 ; linha++, coluna--) {
            if(tabuleiro[coluna][linha] == pretendente_atual) {
                seguidas++;
            }
            else if (tabuleiro[coluna][linha]) {
                seguidas = 1;
            }
            if(seguidas > 0 && seguidas <= 4){
                sequencia_vencedora[seguidas-1][0] = coluna;
                sequencia_vencedora[seguidas-1][1] = linha;
            }
            pretendente_atual = tabuleiro[coluna][linha];
            if(seguidas == 4 && pretendente_atual) {
                turno = pretendente_atual;
                return 1;
            }
        }
        pretendente_atual = 0;
        seguidas = 0;
    }
    if(posicoes_livres) {
        return 0;
    }
    else {
        turno = 0;
        return 1;
    }
}

void jogar(int coluna) {
    if(!tabuleiro[coluna-1][0]) {
        for(int linha = LINHAS-1; linha >= 0; linha--) {
            if(!tabuleiro[coluna-1][linha]) {
                tabuleiro[coluna-1][linha] = turno;
                if(turno == 1) {
                    turno = 2;
                }
                else {
                    turno = 1;
                }
                break;
            }
        }
    }
    else {
        sprintf(err_msg, "J  n„o pode colocar mais pe‡as na posi‡„o %d!", coluna);
    }
}