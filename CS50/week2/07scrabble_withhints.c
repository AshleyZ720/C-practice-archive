#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define DEBUG_ON
int arr[MAX],sum[MAX];
int count;
int  POINTS[] = { 1,  3,  3,  2,  1,  4,  2,  4,  1,  8,  5,  1,  3,  1,  1,  3,  10, 1,  1,  1,  1,  4,  4,  8,  4,  10};
char supper[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char slower[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char word[MAX];
int main()
{
    int player_number=1, tmp=0;
    char scan, clean;
    for(; player_number<3; player_number++)
    {
       count=0;
       printf("Player %d:", player_number);
       while((scan = getchar()) != EOF && scan !='\n' && scan !='\r')
       {    
            if(isupper(scan))
            {
                word[count] = scan;
                arr[count] = POINTS[supper[count] - 'A'];
                #ifdef DEBUG_ON
                printf("arr[%d]=%d\n",count,arr[count]);
                #endif
                count++;
            }
            else if(islower(scan))
            {
                word[count] = scan;
                arr[count] = POINTS[slower[count] - 'a'];
                #ifdef DEBUG_ON
                printf("arr[%d]=%d\n",count,arr[count]);
                #endif                
                count++;
            }
            else
            {
                word[count] = scan;
                arr[count] = 0;
                #ifdef DEBUG_ON
                printf("arr[%d]=%d\n",count,arr[count]);
                #endif
                count++;
            }
       }
       sum[0]=0;
       for(tmp=0;tmp<=count;tmp++)
       {
            sum[player_number]+=arr[tmp];
       }
        memset(word,0,sizeof(word));
        memset(arr,0,sizeof(arr));
    }
    #ifdef DEBUG_ON
    printf("%d,%d",sum[1],sum[2]);
    #endif
    if(sum[1]>sum[2])
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if(sum[1]<sum[2])
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else
    {
        printf("Tie!\n");
        return 0;
    }
}
