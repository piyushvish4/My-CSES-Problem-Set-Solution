#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct process
{
    int STATE;
    int START;
    int END;
    int MODE;
    // 0 - first fit
    // 1 - best fit
    // 2 - worst fit
};

struct process pc[100];
int MAX;
int n;
int *root;
char *cammand;
char **cmd;

int min(int a, int b)
{
    return a < b ? a : b;
}

int format_cammand(char *cammand, char **cmd)
{
    int j = 0, flag = 0, ind = 0;
    for (int i = 0; cammand[i] != '\0'; i++)
    {
        if (flag == 1 && (cammand[i] == ' ' || cammand[i] == '\t'))
            continue;

        else if (cammand[i] == ' ' || cammand[i] == '\t')
        {
            cammand[i] = '\0';
            cmd[j] = &cammand[ind];
            j++;
            ind = -1;
            flag = 1;
        }
        else if (flag == 1 && cammand[i] != ' ' && cammand[i] != '\t')
        {
            ind = i;
            flag = 0;
        }
    }

    if (ind != -1)
        cmd[j] = &cammand[ind],
        j++;

    return j;
}

int main(int argc, char **argv)
{

    n = 0, MAX = atoi(argv[1]);
    root = (int *)malloc(sizeof(int) * (MAX + 1));

    for (int i = 1; i < MAX; i++)
        root[i] = 0;
    root[0] = MAX;

    cammand = (char *)malloc(sizeof(char) * 50);
    cmd = (char **)malloc(sizeof(char *) * 5);

    while (1)
    {
        printf(" > ");
        fflush(stdout);

        scanf("%[^\n]s", cammand);
        getchar();

        int len = format_cammand(cammand, cmd);

        if (strcmp(cmd[0], "RQ") == 0)
        {
            // 0     1          2       3
            // RQ    process    SIZE    MODE

            pc[atoi(cmd[1])].STATE = 1;
            int alloc = -1, sz = -1, i = 0;

            if (cmd[3][0] == 'F')
            {
                while (i < MAX)
                {
                    if (root[i] > atoi(cmd[2]))
                    {
                        pc[atoi(cmd[1])].START = i;
                        pc[atoi(cmd[1])].END = i + atoi(cmd[2]) - 1;
                        pc[atoi(cmd[1])].MODE = 0;

                        if (root[atoi(cmd[2]) + i] == 0)
                        {
                            root[atoi(cmd[2]) + i] = root[i] - (atoi(cmd[2]));
                        }
                        root[i] = -atoi(cmd[2]);
                        break;
                    }
                    i = i + abs(root[i]);
                }
                if (i == MAX)
                    printf("Not enough free space available\n");
            }

            if (cmd[3][0] == 'B')
            {
                while (i != MAX)
                {
                    if (root[i] > atoi(cmd[2]) && root[i] > sz)
                    {
                        sz = root[i];
                        alloc = i;
                    }
                    i = i + abs(root[i]);
                }
                if (alloc == -1)
                    printf("Not enough free space available\n");
                else
                {
                    pc[atoi(cmd[1])].START = alloc;
                    pc[atoi(cmd[1])].END = alloc + atoi(cmd[2]) - 1;
                    pc[atoi(cmd[1])].MODE = 0;

                    if (root[atoi(cmd[2]) + alloc] == 0)
                        root[atoi(cmd[2]) + alloc] = root[alloc] - (atoi(cmd[2]));

                    root[alloc] = -atoi(cmd[2]);
                }
            }

            if (cmd[3][0] == 'W')
            {
                sz = __INT32_MAX__;
                while (i != MAX)
                {
                    if (root[i] > atoi(cmd[2]) && root[i] < sz)
                    {
                        sz = root[i];
                        alloc = i;
                    }
                    i = i + abs(root[i]);
                }
                if (alloc == -1)
                    printf("Not free space available\n");
                else
                {
                    pc[atoi(cmd[1])].START = alloc;
                    pc[atoi(cmd[1])].END = alloc + atoi(cmd[2]) - 1;
                    pc[atoi(cmd[1])].MODE = 0;

                    if (root[atoi(cmd[2]) + alloc] == 0)
                        root[atoi(cmd[2]) + alloc] = root[alloc] - (atoi(cmd[2]));
                    root[alloc] = -atoi(cmd[2]);
                }
            }
        }

        else if (strcmp(cmd[0], "RL") == 0)
        {
            int start = pc[atoi(cmd[1])].START;
            int end = pc[atoi(cmd[1])].END;
            root[start] *= -1;
            int i = 0;
            while (i < MAX)
            {
                if (root[i] > 0 && root[root[i] + i] > 0)
                {
                    int temp = root[i] + i;
                    root[i] += root[root[i] + i];
                    root[temp] = 0;
                }
                else
                    i = i + abs(root[i]);
            }
            pc[atoi(cmd[1])].STATE = 0;
        }

        else if (strcmp(cmd[0], "STAT") == 0)
        {
            for (int i = 0; i < 100; i++)
            {
                if (pc[i].STATE == 1)
                {
                    printf("Process %d:\n\t", i);
                    printf("%d - %d\n\n", pc[i].START, pc[i].END);
                }
            }
            int i = 0;
            while (i != MAX)
            {
                if (root[i] > 0)
                {
                    printf("Unallocated\n\t");
                    printf("%d - %d\n\n", i, root[i] + i - 1);
                }
                i = i + abs(root[i]);
            }
        }

        else if (strcmp(cmd[0], "C") == 0)
        {
            int i = 0, st = 0;
            printf("%d", root[10]);
            while (i != MAX)
            {
                if (root[i] < 0)
                {
                    root[st] = root[i];
                    for (int j = 0; j < 100; ++j)
                        if (pc[j].START == i)
                        {
                            pc[j].START = st;
                            pc[j].END = st + abs(root[st]) - 1;
                        }
                    st += abs(root[i]);
                    i += abs(root[i]);
                }
                else
                    i += abs(root[i]);
            }
            root[st] = MAX - st;
        }

        else
        {
            printf("Exiting...\n");
            exit(0);
        }
    }
}