#include <stdio.h>
int main()
{
    int height,count,n;
    char c;
    height = 0;
    do
    {
        printf("Please give an integer between 1 and 8:");
        n=scanf("%d",&height);//n = the number for matching character
        if(n==0)
        {
            printf("How dare you!!!Retype!!!\n");
            //Clear keyboard buffer
            while((c = getchar()) != EOF && c!='\n');
        }

    }
    while(height<1||height>8);

    for(n=1; n<=height; n++)
    {
        //print spaces
        count=height-n;
        for(; count>=1; count--)
        {
            printf(" ");
        }

        //print hashes
        for(; count<n; count++)
        {
            printf("#");
        }
        printf("  ");
        for(; count>=1; count--)
        {
            printf("#");
        }

        //better way for hashes
#if defined(HAHA)
        for (int col = 1; col <= 2; col++)
        {
            for (int col2 = 0; col2 != row; col2++)
            {
                printf("#");
            }
            if (col == 1)
            {
                printf("  ");
            }
        }
#endif
        printf("\n");
    }
}
