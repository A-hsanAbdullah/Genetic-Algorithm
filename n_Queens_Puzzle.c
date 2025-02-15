#include<stdio.h>
#include "n_Queens_Puzzle.h"

int main()
{
    int pSolution[boardSize];
    int isOver = 0, iter = 0, maxIter = 1000;
    Generate_Random_Boards(chromosomes);
        
    while (iter<maxIter){
        Fitness_Function(chromosomes, fitness);
        printf("Iteration number %d\n", iter);
        Display_Population(chromosomes, fitness);
        isOver = Check_for_Solution(fitness, pSolution);
        if (isOver == 1){
            printf("Solution found after %d iterations!\n\n", iter+1);
            Display_Solution(pSolution);
            break;
        }
        Next_Generation(chromosomes, fitness);
        iter++;
    }
    return 0;
}

// End of program