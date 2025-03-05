#include <stdio.h>
int main()
{
    printf("Please type in dd/mm/yyyy:");
    int day, month, year;
    scanf("%d/%d/%d", &day, &month, &year);
    int i,j,k=0;

    for (i=1; i<=month-1; i++)
    {
        if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
        {
            k=k+31;
        }
        else
        {
            if(i==2)
            {
                k += 28;
                if((year%4==0 && year%100!=0)||year%400==0)
                {
                    k=k+1;
                }
            }
            else
            {
                k=k+30;
            }
        }
    }
    printf("The result is %d.\n",k+day);
}