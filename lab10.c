#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *memory;
void print(int n)
{
    printf("State of memory block:\n");
    for(int i=0;i<n;i++)
        printf("%d ",memory[i]);
    printf("\n");
}
void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void first_fit(int pid,int mem,int n)
{
    int start=0,end=0,i,j,k,flag;
    for(i=0;i<n;i++)
    {
        if(memory[i]==-1)
        {
            flag=0;
            start=i;
            for(j=i+1;j<n;j++)
            {
                if(memory[j]!=-1 || (flag==0 && j==n-1))
                {
                    end=j-1;
                    if(j==n-1 && flag==0)
                        end=j;
                    flag=1;
                    if(end-start+1>=mem)
                    {
                        for(k=start;k<start+mem;k++)
                            memory[k]=pid;
                        printf("Memory allocation request ACCEPTED\n");
                        print(n);
                        return;
                    }
                    else
                    {
                        i=j;
                        break;
                    }
                }
            }
        }
    }
    printf("Memory allocation request REJECTED\n");
    print(n);
}
void best_fit(int pid,int mem,int n)
{
    int i,j,start=0,end=0,small=n+1,x=-1,y=-1,flag;
    for(i=0;i<n;i++)
    {
        if(memory[i]==-1)
        {
            flag=0;
            start=i;
            for(j=i+1;j<n;j++)
            {
                if(memory[j]!=-1 || (flag==0 && j==n-1))
                {
                    end=j-1;
                    if(flag==0 && j==n-1)
                        end=j;
                    flag=1;
                    if(end-start+1<small && end-start+1>=mem)
                    {
                        small=end-start+1;
                        x=start;
                        y=end;
                    }
                    i=j;
                    break;
                }
            }
        }
    }
    if(y-x+1>=mem && x!=-1 && y!=-1)
    {
        for(i=x;i<x+mem;i++)
            memory[i]=pid;
        printf("Memory allocation request ACCEPTED\n");
    }
    else
        printf("Memory allocation request REJECTED\n");
    print(n);
}
void worst_fit(int pid,int mem,int n)
{
    int i,j,k,start=0,end=0,large=0,x=-1,y=-1,flag;
    for(i=0;i<n;i++)
    {
        if(memory[i]==-1)
        {
            flag=0;
            start=i;
            for(j=i+1;j<n;j++)
            {
                if(memory[j]!=-1 || (flag==0 && j==n-1))
                {
                    end=j-1;
                    if(flag==0 && j==n-1)
                        end=j;
                    flag=1;
                    if(end-start+1>large)
                    {
                        large=end-start+1;
                        x=start;
                        y=end;
                    }
                    i=j;
                    break;
                }
            }
        }
    }
    if(y-x+1>=mem && x!=-1 && y!=-1)
    {
        for(i=x;i<x+mem;i++)
            memory[i]=pid;
        printf("Memory allocation request ACCEPTED\n");
    }
    else
        printf("Memory allocation request REJECTED\n");
    print(n);
}
void release(int pid,int n)
{
    int i;
    for(i=0;i<n;i++)
        if(memory[i]==pid)
            memory[i]=-1;
    print(n);
}
void status(int n)
{
    int i,j,pid,flag1,flag2;
    for(i=0;i<n;i++)
    {
        if(memory[i]==-1)
        {
            flag1=0;
            printf("Unused Addresses [%d:",&memory[i]);
            for(j=i+1;j<n;j++)
            {
                if(memory[j]!=-1 || (flag1==0 && j==n-1))
                {
                    if(flag1==0 && j==n-1)
                    {
                        printf("%d]\n",&memory[j]);
                        i=j;
                    }
                    else
                    {
                        printf("%d]\n",&memory[j-1]);
                        i=j-1;
                    }
                    flag1=1;
                    break;
                }
            }
        }
        else
        {
            flag2=0;
            pid=memory[i];
            printf("Addresses [%d:",&memory[i]);
            for(j=i+1;j<n;j++)
            {
                if(memory[j]!=pid || (flag2==0 && j==n-1))
                {
                    if(flag2==0 && j==n-1)
                    {
                        printf("%d] Process P%d\n",&memory[j],pid);
                        i=j;
                    }
                    else
                    {
                        printf("%d] Process P%d\n",&memory[j-1],pid);
                        i=j-1;
                    }
                    flag2=1;
                    break;
                }
            }
        }
    }
    print(n);
}
void compact(int n)
{
    int i,j,k,start;
    for(i=0;i<n;i++)
        if(memory[i]==-1)
        {
            start=i;
            break;
        }
    for(j=i+1;j<n;j++)
        if(memory[j]!=-1)
            swap(&memory[start++],&memory[j]);
    print(n);
}
int main(int argc, char* argv[])
{
    int i,n=atoi(argv[1]),mem,pid;
    memory=(int*)malloc(n*sizeof(int));
    if(memory==NULL)
    {
    	printf("Specified memory could not be allocated\n");
    	exit(0);
    }
    for(i=0;i<n;i++)
        memory[i]=-1;
    print(n);
    char s[4]="0",p[2],type;
    do
    {
        printf("allocator>");
        scanf(" %s",s);
        if(!strcmp(s,"RQ"))
        {
            scanf(" %s%d %c",p,&mem,&type);
            pid=(int)p[1]-48;
            if(type=='F')
                first_fit(pid,mem,n);
            else if(type=='B')
                best_fit(pid,mem,n);
            else if(type=='W')
                worst_fit(pid,mem,n);
        }
        else if(!strcmp(s,"RL"))
        {
            scanf(" %s",p);
            pid=p[1]-48;
            release(pid,n);
        }
        else if(!strcmp(s,"C"))
            compact(n);
        else if(!strcmp(s,"STAT"))
            status(n);
    }while(strcmp(s,"X"));
    return 0;
}

