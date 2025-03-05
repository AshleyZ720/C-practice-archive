#include <stdio.h>
int main()
{
    int i=254, n=0177;
    printf("i = %o\n",i);
    printf("n = %d\n",n);
    i &= 0177;
    printf("i = %d\n",i);
}