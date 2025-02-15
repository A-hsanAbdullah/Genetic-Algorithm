#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define populationsize 4
#define parents populationsize / 2
#define boardsize 4
#define knights 15

void initializeBoard(int board[boardsize][boardsize]) {
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard(int board[boardsize][boardsize]) {
    printf("Board:\n");
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void crossover(int boards[populationsize][boardsize][boardsize]) {
    int final_position[populationsize][2];
    int k = 0, r, c;

    // First loop: Place half of the knights randomly for the first parents
    for (int p = 0; p < parents; p++) {
        for (r = 0; r < boardsize; r++) {
            for (c = 0; c < boardsize; c++) {
                if (boards[p][r][c] == 1) {
                    boards[p + parents][r][c] = 1;
                    k++;
                }
                if (k == knights / 2)
                    break;
            }
            if (k == knights / 2)
                break;
        }
        final_position[p][0] = r;
        final_position[p][1] = c;
        k = 0;
    }

    // Second loop: Place the remaining knights for the first parents
    for (int p = 0; p < parents - 1; p++) {
        for (r = 0; r < boardsize; r++) {
            for (c = 0; c < boardsize; c++) {
                if (boards[p][r][c] == 1 && r > final_position[p][0] && c > final_position[p][1]) {
                    boards[p + 1 + parents][r][c] = 1;
                    k++;
                }
                if (k == knights)
                    break;
            }
            if (k == knights)
                break;
        }
        k = 0;
    }
}

int main() {
    srand(time(NULL));

    // Initialize the boards
    int game_boards[populationsize][boardsize][boardsize];
    for (int i = 0; i < populationsize; i++) {
        initializeBoard(game_boards[i]);
    }

    // Randomly place knights on the initial boards
    for (int i = 0; i < populationsize; i++) {
        for (int k = 0; k < knights; k++) {
            int x = rand() % boardsize;
            int y = rand() % boardsize;
            game_boards[i][x][y] = 1;
        }
    }

    // Print the initial boards
    printf("Initial Population:\n");
    for (int i = 0; i < populationsize; i++) {
        printBoard(game_boards[i]);
        printf("\n");
    }

    // Perform crossover
    crossover(game_boards);

    // Print the resulting boards after crossover
    printf("\nAfter Crossover:\n");
    for (int i = 0; i < populationsize; i++) {
        printBoard(game_boards[i]);
        printf("\n");
    }

    return 0;
}
