#include <stdio.h>
int main()
{
    int i;
    int j;
    i=9;
    while(i>0)
    {
        j=1;
        while(j<=i)
        {
            printf("%d*%d=%d ", j, i, i*j);
            j++;
        }
        printf("\n");
        i--;
    }
}