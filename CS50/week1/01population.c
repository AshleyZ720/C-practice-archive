#include <stdio.h>
int main()
{
    int start,end,year;
    year=0;
    do
    {
        printf("Please give two positive integers as the start size and the end size:\n");
        scanf("%d %d",&start,&end);
    }
    while(start<9 || end<start);
    int i=start;
    for(year=0; start<end; year++)
    {
        start+=start/3-start/4;
    }
    printf("Start size: %d\nEnd Size: %d\nYears: %d\n",i,end,year);
}