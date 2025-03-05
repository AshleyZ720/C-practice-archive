#include <stdio.h>
int main()
{
    char x;
    int i =0;
    for (x=32; x>=32&&x<=127; x++)
    {
        printf("%c ", x);
        i++;
        if (i%10==0)
        {
            printf("\n");
        }

    }
}