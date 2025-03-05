#include <stdio.h>
int main()
{
    int a;
    int b;
    for (a=9; a>0; a--)
    {
        for (b=1; b<10&&b<=a; b++)
        {
            printf("%d*%d=%d ", b, a, a*b);
        }
        printf("\n");
    }
}