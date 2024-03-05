#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	
	int n=0;
	int k=0;
		do
		{
			printf("Please enter a number greater than 0 to run the Collatz Conjecture.\n"); 
  			scanf("%d", &k);	
		}
		while (k <= 0);
		
		while (k!=1)
			{
				int fd[2];
				pipe(fd);
				pid_t pid = fork();
				if (pid == 0)
			        {
					close(fd[0]);

					if (k%2 == 0)
					{
						k = k/2;
						write(fd[1], &k, sizeof(k) );
					}
					else if (k%2 == 1)
					{
						k = 3 * (k) + 1;
						write(fd[1], &k, sizeof(k) );
					}	
			
					printf("%d\n",k);
					close(fd[1]);
					break;
				}
				else 
				{
					wait(NULL);
					close(fd[1]);
					read (fd[0], &k, sizeof(k) );
					close(fd[0]);
				}
			}
	return 0; 
}