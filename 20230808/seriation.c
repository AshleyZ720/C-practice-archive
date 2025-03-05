#include <stdio.h>
int main()
{
    int i,j,k;
    int x,y,z;
    printf("Please type in three integer:");
    scanf("%d %d %d", &i, &j, &k);
    if (i<j)
    {
        if (j<k)
        {
            x=i;
            y=j;
            z=k;
        }
        else
        {
            x=(i<k)?i:k;
            y=(i>k)?i:k;
            z=j;
        }

    }
    else
    {
        if (i<k)
        {
            x=j;
            y=i;
            z=k;
        }
        else
        {
            x=(j<k)?j:k;
            y=(j>k)?j:k;
            z=i;
        }
    }
    printf("x=%d,y=%d,z=%d\n",x,y,z);
}