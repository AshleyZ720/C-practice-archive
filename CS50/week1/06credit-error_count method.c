#include <stdio.h>
#define DEBUG_ON
#define MAX 100
int main()
{
    int count=0;
    int test=0;
    char credit_number[MAX];
    char c;
    printf("Number:");
    while((c = getchar()) != EOF && c != '\n' && c != '\r')
    {
        if(c>='0'&&c<='9')
        {
            credit_number[count] = c;
            int i= c -'0';
            test+=i;
            count++;
            #ifdef DEBUG_ON
            printf("c=%c,test=%d,count=%d\n",c,test,count);
            #endif
        }
        else
        {
            printf("%d,How dare you!!!\n",c);
            return 0;
        }
    }
    int j=count-1;
    do
    {
        j--;
        int k=credit_number[j] - '0';
        test+=k;
        j--;
        #ifdef DEBUG_ON
        printf("test=%d",test);
        #endif
    } while (j>0);
    
    if(count<13||count>16)
        printf("INVALID\n");
    else 
    {
        if(test%10==0)
            {
                char h,a;
                h=credit_number[1];
                a=credit_number[2];
                switch(h)
                {
                    case '3':
                        if(a=='4'||a=='7' && count==15)
                        {
                            printf("Hello, American Express user!\n");
                            break;
                        }
                        else
                        {
                            printf("Sorry, this is probably a credit card number but it is not in my set range.\n");
                            break;
                        }
                    case '4':  
                        if(count!=14||count!=15)
                        {
                            printf("Hello, Visa user!\n");
                            break;
                        }
                        else
                        {
                            printf("Sorry, this is probably a credit card number but it is not in my set range.\n");
                            break;
                        }
                    case '5':
                        if(a=='1'||a=='2'||a=='3'||a=='4'||a=='5' && count==16) 
                        {
                            printf("Hello, Mastercard user!\n");
                            break;
                        }
                    default:
                        printf("Sorry, this is probably a credit card number but it is not in my set range.\n");
                        break;                
                }
            }
        else
            printf("INVALID\n");
    }  
}