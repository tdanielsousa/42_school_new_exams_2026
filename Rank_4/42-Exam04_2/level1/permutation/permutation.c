#include <unistd.h>
#include <stdlib.h>

void sorted(char *str){
    char tmp;
    for(int i = 0; str[i]; i++){
        for(int j = i+1; str[j]; j++){
            if(str[i] > str[j]){
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
        }
    }
}

void perm(char *str , char *result , int *used, int dep, int len)
{
    if (dep == len)
    {
        for(int i = 0; i < len; i++)
        {
            write(1, &result[i], 1);
        }
        write(1,"\n",1);
        return;
    }
    for (int i = 0; i < len; i++)
    {
        if (used[i]) 
            continue;
        used[i] = 1;
        result[dep] = str[i];
        perm(str, result , used , dep + 1 , len);
        used[i] = 0;        
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;

    int i = 0;
    while (argv[1][i])
        i++;
    int len = i;
    char *result = malloc(len + 1);
    int *used = calloc(len, sizeof(int));
    sorted(argv[1]);
    perm(argv[1], result, used, 0, len);    
    free(result);
    free(used);
}