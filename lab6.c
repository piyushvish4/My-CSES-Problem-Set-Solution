#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>
#define MAX 3
#define MAX_THREAD 3
int matrixA[MAX][MAX];
int matrixB[MAX][MAX];
int matrixC[MAX][MAX];
int row = 0;

void* multi(void* arg)
{
	int i = row++;

	for (int j = 0; j < MAX; j++)
	for (int k = 0; k < MAX; k++)
		matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
}

int main()
{
    printf("Enter %dX%d matrix A:\n",MAX,MAX);
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            scanf("%d",&matrixA[i][j]);
    }

    printf("Enter %dX%d matrix B:\n",MAX,MAX);
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            scanf("%d",&matrixB[i][j]);
    }
	pthread_t threads[MAX_THREAD];
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_create(&threads[i], NULL, multi,NULL);
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);
    
    printf("Resultant Matrix after multiplying A and B: \n");
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++)
            printf("%d ",matrixC[i][j]);
        printf("\n");
    }
	return 0;
}
