#include <stdio.h>
int check_int(int value);
int main()
{
    int n,i;
    for(n=2; n<=100; n++)
    {
        if(check_int(n)==1)
#if defined(HAHA)
            for(i=2; i<n; i++)
            {

                if(n%i==0)
                    break;
            }
        if(i==n)
#endif
            printf("%d\n",n);
    }
}

int check_int(int value)
{
    int i;
    for(i=2; i<value; i++)
    {
        if(value%i==0)
            break;
    }
    if(i==value)
        return 1;
    else
        return 0;
}
