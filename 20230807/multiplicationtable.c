#include <stdio.h>
int main()
{
    int a;
    int b;
    for (a=9; a>0; a--)
    {
        for (b=a; b>0; b--)
        {
            printf("%d*%d=%d ", a, b, a*b);
        }
        printf("\n");
    }
}