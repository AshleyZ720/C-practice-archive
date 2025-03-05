#include <stdio.h>
int main()
{
    printf("Please type in dd/mm/yyyy:");
    int day, month, year;
    scanf("%d/%d/%d", &day, &month, &year);
    printf("%d,%d,%d",day,month,year);
}

