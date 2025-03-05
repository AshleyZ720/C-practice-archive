#include <stdio.h>
#define percent 100
#define half 2
double myfunc(double,double,double);
int main()
{
    double amount,tax,tip;
    printf("Bill before tax and tip: ");
    scanf("%5le", &amount);
    printf("Sale Tax Percent: ");
    scanf("%5le", &tax);
    printf("Tip Percent: ");
    scanf("%5le", &tip);
    printf("You will owe $%.2f each!\n",myfunc(amount,tax,tip));

}

double myfunc(double i,double j,double k)
{
    i+=i*(j/percent);
    return (i+i*(k/percent))/half;
}