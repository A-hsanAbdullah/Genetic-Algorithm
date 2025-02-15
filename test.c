#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define PopSize 50
#define length 8
#define PosKnights 28

int attackOn5X5 = 0;
int parent = 0;
int num = 0;
char generation[length * PopSize][length];
char worldSpace[length * PopSize][length];
int knightX[PosKnights * PopSize];
int knightY[PosKnights * PopSize];
int knightAttacksArray[PosKnights * PopSize];

void random_generation()
{
    srand(time(0));
    for (int j = 0; j < PopSize; j++)
    {
        for (int i = 0; i < PosKnights; i++)
        {
            int x = rand() % length + (length * j);
            int y = rand() % length;
            if (generation[x][y] == 1)
            {
                --i;
                continue;
            }
            knightX[i + (PosKnights * j)] = x;
            knightY[i + (PosKnights * j)] = y;
            generation[x][y] = 1;
        }
    }
}

int isValidMove(int x, int y)
{
    if (x >= length * parent && x < length * (parent + 1) && y >= 0 && y < length && generation[x][y] == 0)
    {
        return 1;
    }
    return 0;
}

int solve(int x, int y)
{
    int attacks = 0;
    num++;
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    for (int i = 0; i < 8; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValidMove(newX, newY))
        {
            worldSpace[newX][newY] = 1;
            attacks++;
        }
    }
    knightAttacksArray[num - 1] = attacks;
    return attacks;
}

int isAllAttacked(int x)
{
    for (int i = (x * length); i < (length + (x * length)); i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (worldSpace[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    printf("worldspace before\n");
    int v = 0;
    for (int i = 0; i < length * PopSize; i++)
    {
        if (v % length == 0)
        {
            printf("%d\n", v / length);
        }
        for (int j = 0; j < length; j++)
        {
            printf("%d ", worldSpace[i][j]);
        }
        printf("\n");
        v++;
        if (v % length == 0)
        {
            printf("\n");
        }
    }

    random_generation();

    printf("random gen\n");
    v = 0;
    for (int i = 0; i < length * PopSize; i++)
    {
        if (v % length == 0)
        {
            printf("%d\n", v / length);
        }
        for (int j = 0; j < length; j++)
        {
            printf("%d ", generation[i][j]);
        }
        printf("\n");
        v++;
        if (v % length == 0)
        {
            printf("\n");
        }
    }

    for (int i = 0; i < length * PopSize; i++)
    {
        for (int j = 0; j < length; j++)
        {
            worldSpace[i][j] = generation[i][j];
        }
    }

    printf("worldspace after\n");
    v = 0;
    for (int i = 0; i < length * PopSize; i++)
    {
        if (v % length == 0)
        {
            printf("%d\n", v / length);
        }
        for (int j = 0; j < length; j++)
        {
            printf("%d ", worldSpace[i][j]);
        }
        printf("\n");
        v++;
        if (v % length == 0)
        {
            printf("\n");
        }
    }

    int next = 0;
    for (int k = 0; k < PosKnights; k++)
    {
        for (int i = 0; i < PopSize; i++)
        {
            parent = (next / PosKnights);
            printf("%d knight has %d attacks by function\n", next + 1, solve(knightX[i + (PopSize * k)], knightY[i + (PopSize * k)]));
            next++;
        }
    }

    printf("worldspace after attacks\n");
    v = 0;
    for (int i = 0; i < length * PopSize; i++)
    {
        if (v % length == 0)
        {
            printf("%d\n", v / length);
            attackOn5X5 = 0;
        }

        for (int j = 0; j < length; j++)
        {
            printf("%d ", worldSpace[i][j]);
            if (worldSpace[i][j] == 1)
            {
                attackOn5X5++;
            }
        }
        printf("\n");
        v++;
        if (v % length == 0)
        {
            printf("attacks >>%d\n", attackOn5X5);
        }
    }

    for (int k = 0; k < PopSize; k++)
    {
        if (isAllAttacked(k))
        {
            printf("FINAL RESULT is %d\n", k);
          
            printf("-----------------\n");
            
            
            for (int i = (k * length); i < length + (k * length); i++)
            {
                printf("|");
                for (int j = 0; j < length; j++)
                { if (generation[i][j] == 1)
                {
                   generation[i][j] = 'K';
                }
                else{
                    generation[i][j] = 'X';
                }
                
                    printf("%c|", generation[i][j]);
                }
                
                printf("\n");
                printf("-----------------\n");
            }
        }
    }

    return 0;
}