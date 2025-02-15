/* n_Queens_Puzzle.c: n-Queens Puzzle Problem Header File
----------------------------------------------------------------------------
This header file is a library for n-Queens Puzzle Problem solver using 
Genetic Algorithm. This file contains all the global variables and user-
defined functions required to solve n-Queens Problem using Genetic Algorithm.
----------------------------------------------------------------------------
Written by Shujat Ali (engrshujatali@gmail.com) on 23-Nov-2022.
IDE: Visual Studio Code 1.60.0
C Compiler: GCC (Rev. 5, Built by MSYS2 Project) 10.3.0 */

// Built-in Libraries--------------------------------------------------------
#include<stdlib.h>
#include<time.h>

// Global Variables----------------------------------------------------------
const int boardSize = 8;           // Board size 8-by-8
const int popSize = 40;            // chromosomes population size
int chromosomes[40][8];            // population of chromosomes
int fitness[40];                   // fitness of population
int crossOverPoint = 4;             // cross-over point
const int nParents = 20;            // number of parents survived

// User-defined Functions----------------------------------------------------

// 1. 
void Generate_Random_Boards(int chromosomes[popSize][boardSize])
/* This function generates population (of size specified by popSize) of 
random chromosomes (of size specified by boardSize) required to start solving 
n-queens puzzle problem and stores it in chromosomes array.
*/
{
    srand ( time(0) );              // need to use for rand() work properly
    for (int i = 0; i < popSize; i++){
        for (int j = 0; j < boardSize; j++){
            chromosomes[i][j]=(rand()%boardSize) + 1;
        }
    }
}

// 2.
void Fitness_Function(int chromosomes[popSize][boardSize], int fitness[popSize])
/* This function calculates the fitness value of each chromosome in the population
by checking row-wise and diagonal clashes. It assumes that each queen is placed in
different column therefore column-wise clashes are not checked.
*/
{   int fitVal = 0;

    // check row-wise clashes
    for (int i = 0; i < popSize; i++){
        for (int j = 0; j < boardSize; j++){
            for (int k = j+1; k < boardSize; k++){
                if (chromosomes[i][j]==chromosomes[i][k]){
                    fitVal++;
                }
            }        
        }
        fitness[i] = fitVal;
        fitVal = 0;
    }
    
    // check diagonal-wise clashes
    for (int i = 0; i < popSize; i++){
        for (int j = 0; j < boardSize; j++){
            for (int k = j+1; k < boardSize; k++){
                if ((j!=k)&&(abs(j-k)==abs(chromosomes[i][j]-chromosomes[i][k]))){
                   fitVal++; 
                }
            }
        }
        fitness[i] += fitVal;
        fitVal = 0;
    }   
}

// 3.
void Next_Generation(int chromosomes[popSize][boardSize], int fitness[popSize])
/* This function implements the concept of "survival of the fitest" of genetics.
From the current population 3 most fitest (least value of queens attacks) chromosomes
are selected as parents and using these, through cross-over process, 6 childs are
created and 1 last child is created by mutation process performed randomly on the
most fittest chromosome. At the end, new generation (3 parents + 7 childs) is 
passed to current population (chromosomes).
*/
{
    int val = 0, ind = 0;
    int index = 0, value = 0;
    int arr[boardSize];
    
    // Bubble sort the population (most fitest, least clashes) at top-----------
    for (int i = 0; i < popSize; ++i){
            for (int j = i + 1; j < popSize; ++j){
                if (fitness[i] > fitness[j]){
                    val = fitness[j];
                    fitness[j] = fitness[i];
                    fitness[i] = val;
                    
                    for (int k = 0; k < boardSize; k++){
                        arr[k] = chromosomes[j][k];
                    }
                    for (int k = 0; k < boardSize; k++){
                        chromosomes[j][k] = chromosomes[i][k];
                    }
                    for (int k = 0; k < boardSize; k++){
                        chromosomes[i][k] = arr[k];
                    }
                }
            }
        }

    // 1. Parent selection - survival of the fitest------------------------------
    // select first nParents as parents for crossover and mutation process

    // 2. Cross-over to generate next generation---------------------------------
     for (int k = 0; k < nParents; k=k+2){
        for (int i = 0; i < crossOverPoint; i++){
            chromosomes[nParents+k][i] =  chromosomes[k][i];
        }
        for (int i = crossOverPoint; i < boardSize; i++){
            chromosomes[nParents+k][i] =  chromosomes[k+1][i];
        }
    }
    for (int k = 1; k < nParents; k=k+2){
        for (int i = 0; i < crossOverPoint; i++){
            chromosomes[nParents+k][i] =  chromosomes[k+1][i];
        }
        for (int i = crossOverPoint; i < boardSize; i++){
            chromosomes[nParents+k][i] =  chromosomes[k][i];
        }
    }

    // 3. Mutation to incorporate randomization
    
    /* for (int i = 0; i < boardSize; i++){
        chromosomes[popSize-2][i]=chromosomes[0][i];
        chromosomes[popSize-1][i]=chromosomes[1][i];
    } */
    srand ( time(NULL) );              // need to use for rand() work properly
    for (int i = 0; i < popSize; i=i+1){
        index = (rand()%boardSize);
        value = (rand()%boardSize) + 1;
        chromosomes[i][index] = value;
    }
}

// 4.
int Check_for_Solution(int fitness[popSize], int solution[boardSize])
{
    int minVal = 1000, minInd = 0;
    
    for (int i = 0; i < popSize; i++){
        if (fitness[i]<minVal){
            minVal = fitness[i];
            minInd = i;
        }
    }
    if (minVal == 0){
        for (int i = 0; i < boardSize; i++){
            solution[i] = chromosomes[minInd][i];
        }
        return 1;
    }
    return 0;
}

// 5. 
void Display_Population(int chromosomes[popSize][boardSize], int fitness[popSize])
/* This function print the entire population on the computer screen, that may be
required for debugging purpose.
*/
{
    for (int i = 0; i < popSize; i++){
            for (int j = 0; j < boardSize; j++){
                printf("%d", chromosomes[i][j]);
            }
            printf("\t%d", fitness[i]);
            printf("\n");
        }
        printf("\n");
}

// 6.
void Display_Solution(int solution[boardSize])
/* This function display the solution board i.e., 8-queens placed on chess board
and none of these attacking, on computer screen.
*/
{
    char sBoard[boardSize][boardSize];
    
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            sBoard[i][j] = ' ';
        }
    }
    
    for (int i = 0; i < boardSize; i++){
        sBoard[solution[i]-1][i] = 'X';
    }
    
    printf(" ");
    for (int i = 0; i < boardSize; i++){
        printf(" %d", solution[i]);
    }
        
    printf("\n -----------------\n");
    for (int i = 0; i < boardSize; i++){
        printf("%d", i+1);
        for (int j = 0; j < boardSize; j++){
            printf("|%c", sBoard[i][j]);
        }
        printf("|\n -----------------\n");
    }
}

// End of program