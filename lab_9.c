#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

bool isSafe()
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    bool finish[5];
    for (int k = 0; k < 5; k++)
    {
        finish[k] = 0;
    }

    // Make a copy of available resources
    int work[4];
    for (i = 0; i < 4; i++)
    {
        work[i] = available[i];
    }
    for (int k = 0; k < 5; k++)
    {
        for (i = 0; i < 5; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < 4; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    for (int y = 0; y < 4; y++) 
                    {
                        work[y] += maximum[i][y];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (int i = 0; i < 5; i++)
    {
        if (finish[i] == 0)
        {
            flag = 0;
            printf("The following system is not safe\n");
            return 0;
        }
    }

    printf("The Following system is in SAFE State\n");
    return 1;
}

void printavailable()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");
}

void printmaximum()
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
}

void printallocation()
{

    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
}

void printneed()
{

    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    printf("Enter number of resources of each type \n");
    scanf("%d %d %d %d", &available[0], &available[1], &available[2], &available[3]);

    for (int i = 0; i < 5; i++)
    {
        printf("Enter maximum need of process %d \n", (i + 1));
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    while (true)
    {

        printf("Enter 1 to request resource \n"
               "Enter 2 to release resource\n"
               "Enter 3 to print available matrix, maximum matrix, allocation matrix,need matrix \n"
               "Enter 4 to exit+ \n");

        int t;
        scanf("%d", &t);

        if (t == 1)
        {
            printf("Enter customer number and amount of each resource \n");
            int arr[4];
            int res;
            scanf("%d", &res);
            int i;
            bool check = true;
            for (i = 0; i < 4; i++)
            {
                scanf("%d", &arr[i]);
                if (arr[i] > available[i])
                {
                    check = false;
                }
            }

            if (check == false)
            {
                printf("Resources not available \n");
            }
            else {
            for (i = 0; i < 4; i++)
            {
                available[i] -= arr[i];
                allocation[res - 1][i] += arr[i];
            }

            if (isSafe() == false)
            {
                for (i = 0; i < 4; i++)
                {
                    available[i] += arr[i];
                    allocation[res - 1][i] -= arr[i];
                }
            }}
        }

        else if (t == 2)
        {

            printf("Enter customer number and amount of each resource \n");
            int arr[4];
            int res;

            scanf("%d", &res);

            int i;

            for (i = 0; i < 4; i++)
            {
                scanf("%d", &arr[i]);
            }
            bool check = true;
            for (i = 0; i < 4; i++)
            {
                if (allocation[res - 1][i] < arr[i])
                {
                    check = false;
                    break;
                }
            }
            if (check)
            {
                for (i = 0; i < 4; i++)
                {
                    available[i] += arr[i];
                    allocation[res - 1][i] -= arr[i];
                }
            }
            else
            {
                printf("Number of Resources asked to release is greater than allocated resorces\n");
            }
        }

        else if (t == 3)
        {

            printf("Available Matrix\n");
            printavailable();
            printf("\n");
            printf("Maximum Matrix\n");
            printmaximum();
            printf("\n");
            printf("Allocation Matrix\n");
            printallocation();
            printf("\n");
            printf("Need Matrix\n");
            printneed();
        }

        else
        {
            break;
        }
    }
}