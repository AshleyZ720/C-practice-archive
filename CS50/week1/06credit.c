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
            count++;
            
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
        int k=(credit_number[j] - '0')*2;
        char tmp[MAX];
        sprintf(tmp,"%d",k);
        for(int x=0;tmp[x] != '\0';x++)
        {
            int i=tmp[x] - '0';
            test+=i;
        }
        j--;
        #ifdef DEBUG_ON
        printf("test1=%d",test);
        #endif
    } while (j>0);
    int m=count-1;
    while (m>=0)
    {
        int n=credit_number[m] - '0';
        test+=n;
        m--;
        m--;
        #ifdef DEBUG_ON
        printf("test2=%d",test);
        #endif
    } 
    if(count<13||count>16)
        printf("INVALID\n");
    else 
    {
        if(test%10==0)
            {
                char h,a;
                h=credit_number[0];
                a=credit_number[1];
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
                            printf("Yeah, this is probably a credit card number but it is not in my set range.\n");
                            break;
                        }
                    case '4':  
                        if(count!=14 && count!=15)
                        {
                            printf("Hello, Visa user!\n");
                            break;
                        }
                        else
                        {
                            printf("Yeah, this is probably a credit card number but it is not in my set range.\n");
                            break;
                        }
                    case '5':
                        if(a=='1'||a=='2'||a=='3'||a=='4'||a=='5' && count==16) 
                        {
                            printf("Hello, Mastercard user!\n");
                            break;
                        }
                    default:
                        printf("Yeah, this is probably a credit card number but it is not in my set range.\n");
                        break;                
                }
            }
        else
            printf("INVALID\n");
    }  
}