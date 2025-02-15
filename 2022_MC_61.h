#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// define global variables
#define boardsize 8
#define knights 14
#define populationsize 500
#define parents (populationsize / 2)
// define functions
int boards[populationsize][boardsize][boardsize];    // 3D array for boards
int fitnessArray[populationsize];        // array for fitness

void initialize_pop(int boards[populationsize][boardsize][boardsize], int start)
{
    for (int z = start; z < populationsize; z++)
    {
        for (int x = 0; x < boardsize; x++)
        {
            for (int y = 0; y < boardsize; y++)
            {
                boards[z][x][y] = 0;
            }
        }
    }
}

void placeRandomKnights(int boards[populationsize][boardsize][boardsize])
// x defines rows, y defines colunms, z defines board
{
    for (int z = 0; z < populationsize; z++)
    {
        for (int k = 0; k < knights; k++)
        {
            int x = rand() % boardsize;
            int y = rand() % boardsize;
            if (boards[z][x][y] != 1)
            {
                boards[z][x][y] = 1;
            }
            else
            {
                k--;  // if knight already placed at that position
            }
        }
    }
}

void Placement(int board[boardsize][boardsize])
{ /* code for printing the chess board grid
  ___________*/
    int k = 0;
   
    printf("   1   2   3   4   5   6   7   8\n");
    printf("__________________________________\n");
    for (int i = 0; i < boardsize; i++)
    {
        printf("%d|", i+1); // Print row number with vertical line
        for (int j = 0; j < boardsize; j++)
        {
            if (board[i][j] == 1)
            {
                printf(" k ");
                k++;
            }
            else if (board[i][j] == 2)
            {
                printf(" X ");
            }
            else
            {
                printf("   ");
            }
            printf("|");
        }
        printf("\n__________________________________\n");
    }
    printf("no. of knights = %d\n", k);
}

void applyingattacks(int board[populationsize][boardsize][boardsize])
{
    int knightMoves[8][2] = {
        {2, 1}, {2, -1},  //For upward attack
         {-2, 1}, {-2, -1}, //For downward attack
        {1, 2}, {1, -2}, // For right attack
         {-1, 2}, {-1, -2}//For left attack
                        };

    for (int z = 0; z < populationsize; z++)
    {
        for (int x = 0; x < boardsize; x++)
        {
            for (int y = 0; y < boardsize; y++)
            {
                if (board[z][x][y] == 1)
                {
                    for (int attack = 0; attack < 8; attack++)
                    {
                        int attack_x = x + knightMoves[attack][0];
                        int attack_y = y + knightMoves[attack][1];
                        if (attack_x >= 0 && attack_x < boardsize && attack_y >= 0 && attack_y < boardsize && board[z][attack_x][attack_y] != 1)
                        {
                            board[z][attack_x][attack_y] = 2;
                        }
                    }
                }
            }
        }
    }
}

void fitnesscalculation(int boards[populationsize][boardsize][boardsize], int fitnessArray[populationsize])
{
    int fitness = 0;
    for (int z = 0; z < populationsize; z++)
    {
        for (int i = 0; i < boardsize; i++)
        {
            for (int j = 0; j < boardsize; j++)
            {
                if (boards[z][i][j] == 0)
                {
                    fitness++;
                }
            }
        }
        fitnessArray[z] = fitness;
        fitness = 0;
        
    }
    
}

void selectionofparents(int fitnessArray[populationsize], int boards[populationsize][boardsize][boardsize])
{
    for (int i = 0; i < populationsize; i++)
    {
        for (int j = i + 1; j < populationsize; j++)
        {
            if (fitnessArray[j] < fitnessArray[i])      // sorting fitnessArray in ascending order
            {
                int temp = fitnessArray[i];
                fitnessArray[i] = fitnessArray[j];
                fitnessArray[j] = temp;
                for (int x = 0; x < boardsize; x++)
                {
                    for (int y = 0; y < boardsize; y++)
                    {
                        temp = boards[i][x][y];          // sorting boards according to fitnessArray
                        boards[i][x][y] = boards[j][x][y];
                        boards[j][x][y] = temp;
                    }
                }
            }
        }
    }
}
void RemoveAttacksForNextPopulation(int boards[populationsize][boardsize][boardsize])  //
{
    for (int P_N = 0; P_N < populationsize; P_N++)   // P_N = population number
    {
        for (int R = 0; R < boardsize; R++)
        {
            for (int C = 0; C < boardsize; C++)
            {
                if (boards[P_N][R][C] == 2)
                {
                    boards[P_N][R][C] = 0;
                }
            }
        }
    }
}

void crossover(int boards[populationsize][boardsize][boardsize])
{
    int final_position[populationsize][2];
    int k = 0,r, c;
    for (int p = 0; p < (int)( parents); p++)
    {
        for (r = 0; r < boardsize; r++)
        {
            for (c = 0; c < boardsize; c++)
            {
                if (boards[p][r][c] == 1)
                {
                    boards[p +(int)( parents)][r][c] = 1;
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
    for (int p = 0; p < (int)( parents) - 1; p++)
    {
        int r, c;
        for (r = 0; r < boardsize; r++)
        {
            for (c = 0; c < boardsize; c++)
            {
                if (boards[p][r][c] == 1 && r > final_position[p][0] && c > final_position[p][1])
                {
                    boards[p + 1 + (int)( parents)][r][c] = 1;
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

void mutation(int boards[populationsize][boardsize][boardsize]) // mutation
{
    for (int i = 0; i < populationsize; i++)
    {
        int k = 0;
        for (int r = 0; r < boardsize; r++)
        {
            for (int c = 0; c < boardsize; c++)
            {
                if (boards[i][r][c] == 1)
                {
                    k++;
                }
            }
        }
        if (k < knights)
        {
            while (k < knights)
            {
                int row = rand() % boardsize;
                int col = rand() % boardsize;
                if (boards[i][row][col] != 1)
                {
                    boards[i][row][col] = 1;
                    k++;
                }
            }
        }
        else if (k > knights)
        {
            while (k > knights)
            {
                int row = rand() % boardsize;
                int col = rand() % boardsize;
                if (boards[i][row][col] == 1)
                {
                    boards[i][row][col] = 0;
                    k--;
                }
            }
        }
    }
}