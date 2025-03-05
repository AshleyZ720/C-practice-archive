#include <stdio.h>
#include <string.h>
#define MAX 100
#define DEBUG_ON
int arr[MAX],sum[MAX];
int count;
char POINTS[MAX];
int compute_score(int);
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
            if((scan>='A' && scan<='Z') || (scan>='a' && scan<='z'))
            {
                POINTS[count] = scan;
                arr[count]=compute_score(POINTS[count]);
                #ifdef DEBUG_ON
                printf("arr[%d]=%d\n",count,arr[count]);
                #endif
                count++;
            }
            else
            {
                printf("How dare you!!!\n");
                return 1;
            }
       }
       sum[0]=0;
       for(tmp=0;tmp<=count;tmp++)
       {
            sum[player_number]+=arr[tmp];
       }
        memset(POINTS,0,sizeof(POINTS));
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

int compute_score(int point) 
{
    switch(POINTS[count])
    {
        case 'A':case 'a':
            {
                point=1;
                return point;
            }
        case 'B':case 'b':
            {
                point=3;
                return point;
            }
        case 'C':case 'c':
            {
                point=3;
                return point;
            }
        case 'D':case 'd':
            {
                point=2;
                return point;
            }
        case 'E':case 'e':
            {
                point=1;
                return point;
            }
        case 'F':case 'f':
            {
                point=4;
                return point;
            }
        case 'G':case 'g':
            {
                point=2;
                return point;
            }
        case 'H':case 'h':
            {
                point=4;
                return point;
            }
        case 'I':case 'i':
            {
                point=1;
                return point;
            }
        case 'J':case 'j':
            {
                point=8;
                return point;
            }
        case 'K':case 'k':
            {
                point=5;
                return point;
            }
        case 'L':case 'l':
            {
                point=1;
                return point;
            }
        case 'M':case 'm':
            {
                point=3;
                return point;
            }
        case 'N':case 'n':
            {
                point=1;
                return point;
            }
        case 'O':case 'o':
            {
                point=1;
                return point;
            }
        case 'P':case 'p':
            {
                point=3;
                return point;
            }
        case 'Q':case 'q':
            {
                point=10;
                return point;
            }
        case 'R':case 'r':
            {
                point=1;
                return point;
            }
        case 'S':case 's':
            {
                point=1;
                return point;
            }
        case 'T':case 't':
            {
                point=1;
                return point;
            }
        case 'U':case 'u':
            {
                point=1;
                return point;
            }
        case 'V':case 'v':
            {
                point=4;
                return point;
            }
        case 'W':case 'w':
            {
                point=4;
                return point;
            }
        case 'X':case 'x':
            {
                point=8;
                return point;
            }
        case 'Y':case 'y':
            {
                point=4;
                return point;
            }
        case 'Z':case 'z':
            {
                point=10;
                return point;
            }
    }
}