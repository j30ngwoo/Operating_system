#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int ac, char **av)
{
    int     end, i, j, k;
    char    tmp[1000], **arr;
    int     pid;

    if (ac <= 1)
    {
        printf("xargs : parameter error\n");
        exit();
    }

    arr = malloc(sizeof(char *) * 4);
    arr[0] = malloc(sizeof(char) * 1000);
    arr[1] = malloc(sizeof(char) * 1000);
    arr[2] = malloc(sizeof(char) * 1000);
    arr[3] = 0;

    arr[0] = av[1];
    i = 1;
    k = -1;
    while (++i < ac)
    {
        j = -1;
        while (av[i][++j])
        {
            arr[1][++k] = av[i][j];
        }
        if (i < ac - 1)
            arr[1][++k] = ' ';
    }
    arr[1][++k] = 0;
    while (1)
    {
        end = -1;
        while (1)
        {
            read(0, &tmp[++end], 1);
            if (tmp[end] == '\n') // newline
            {
                tmp[end] = 0;
                break;
            }
            else if (tmp[end] == 0) // EOF
                exit();
        }
        i = -1;
        j = -1;
        while (++j <= end)
        {
            arr[2][++i] = tmp[j];
            //printf("arr[1][%d] : %c\n", i, tmp[j]);
        }
        //printf("\narr0 : %s\narr1 : %s\n", arr[0], arr[1]);
        pid = fork();
        if (pid == 0)
        {
            printf("arr2: %s\n", arr[2]);
            exec(av[1], arr);
            printf("exec failed!\n");
            exit();
        }
        else
            wait();
        end++;
    }
    exit();
}
