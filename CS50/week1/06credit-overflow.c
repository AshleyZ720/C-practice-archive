#include <stdio.h>
#define double 2
long power(int,int);
int main()
{
    int test=0;
    int count=0;
    long credit_number,l;
    printf("Number:");
    scanf("%ld",&credit_number);
    l=credit_number;
    for(count=0;power(10,count)<l;count++)
    {
        if(count%2==0)
        {
            test+=credit_number%10*double;
            credit_number=credit_number/10;
        }
        else
        {
            test+=credit_number%10;
            credit_number=credit_number/10;
        }
    }
    if(count<13||count>16)
        printf("INVALID\n");
    else 
    {
        
        if(test%10==0)
            {
                int i;
                i=l/power(10,count-2);
                switch(i)
                {
                    case 34:case 37:
                        printf("Hello, American Express user!\n");
                        break;
                    case 51:case 52:case 53:case 54:case 55:
                        printf("Hello, Mastercard user!\n");
                        break;
                    case 41:case 42:case 43:case 44:case 45:
                    case 46:case 47:case 48:case 49:case 40:
                        printf("Hello, Visa user!\n");
                        break;
                    default:
                        printf("Sorry, this is probably a credit card number but it is not in my set range.\n");
                        break;                
                }
            }
        else
            printf("INVALID\n");
    }
}

long power(int x,int y)
{
    int j;
    int a=1;
    for(j=0;j<y;j++)
    {
        a*=x;
    }
    return a;
}