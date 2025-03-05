#include <stdio.h>
int main( )
{
    int choice;

    printf("Hey,guys!\n");
    while(1) {

        printf("Please type in an integer ranging from 1 to 100: ");
        scanf("%d",&choice);

        if(choice>=1&&choice<=100)
        {
            int a=choice;
            int oddsum=0,b=1,evensum=0;
            for(a; a>=b; a--)
            {
                if(a%2!=0)
                {
                    oddsum+=a;
                }
                else
                {
                    evensum+=a;
                }
            }
            printf("oddsum=%d.\nevensum=%d.\n",oddsum,evensum);
            return 0;

        }
        else
            printf("Error! Please ensure that the integer you typed [%d] is ranging from 1 to 100.\n", choice);


    }
}
