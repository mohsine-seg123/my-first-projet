#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int i,j;
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard() {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("    %c | %c   | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("  ----|-----|----\n");
    printf("    %c | %c   | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("  ----|-----|----\n");
    printf("    %c | %c   | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreespaces() {
    int freespaces = 9;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freespaces--;
            }
        }
    }
    return freespaces;
}

void playerMove() {
    int x, y;
    do {
        printf("Enter row (1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column (1-3): ");
        scanf("%d", &y);
        y--;
        if (board[x][y] != ' ') {
            printf("Invalid move! Try again.\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}

void computerMove() {
    srand(time(0));
    int x, y;
    if (checkFreespaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = COMPUTER;
    }
}

char checkWinner() {
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER)
        printf("YOU WIN!\n");
    else if (winner == COMPUTER)
        printf("YOU LOSE!\n");
    else
        printf("It's a DRAW!\n");
}

int main() {
    char winner = ' ';
    char response;
     do {
        winner = ' ';
        resetBoard();
        while (winner == ' ' && checkFreespaces() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreespaces() == 0) {
                break;
            }
            system("cls");
            computerMove();
            winner = checkWinner();
        }
        printf("\n\n");
        printBoard();
        printWinner(winner);
        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &response);  // Note the space before %c to catch any newline characters

    } while (response == 'Y' || response == 'y');

    printf("Thank you for playing!\n");
   

    return 0;
}