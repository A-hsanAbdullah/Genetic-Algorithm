/*-----------------------------------------------------------------
                SEMESTER PROJECT REPORT CP I
-------------------------------------------------------------------
            KNIGHT PROBLEM USING GENATIC ALGORITHM
-------------------------------------------------------------------
WRITTEN BY: AHSAN ABDULLAH (ahsanispro@gmail.com) 2022-MC-61
-------------------------------------------------------------------
DATE: 7-1-2024
-------------------------------------------------------------------
Visual Stdio 12.2.0
-------------------------------------------------------------------*/
#include <stdio.h>

#include "2022_MC_61.h"

int main()
{
    srand(time(NULL));       // random seeding
    initialize_pop(boards, 0);  // initialize_pop first half boards
    placeRandomKnights(boards); // placeRandomKnights first half boards
    applyingattacks(boards);    // applyingattacks first half boards
    int i;
    for (i = 0; i < 10000; i++) // limits the generations
    {
        fitnesscalculation(boards, fitnessArray);
        selectionofparents(fitnessArray, boards);
        printf("generation no. %d\n", i + 1);
        printf("Most fittest offspring has fitness: %d\n", fitnessArray[0]);
        if (fitnessArray[0] == 0)
        {
            printf("Solution found after %d generations\n", i);
            Placement(boards[0]);
            break;
        }
        RemoveAttacksForNextPopulation(boards);
        initialize_pop(boards, parents); // initialize_pop second half boards
        // placeRandomKnights(boards);
        crossover(boards);
        mutation(boards);
        applyingattacks(boards);
    }
    if (fitnessArray[0] != 0)    // if no solution found
    {
        printf("\n -------------Unfortunately no solution found----------------\n");
        printf("\n--------------------------------------------------------------\n");
        printf("             No solution found after %d generations\n", i);
        printf("--------------------------------------------------------------\n");
        printf("Here's the most fittest offspring:\n");
        Placement(boards[0]);  // prints the most fittest offspring
    }
    return 0;
}