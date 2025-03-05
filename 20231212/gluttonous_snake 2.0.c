#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#define XL 75
#define YL 36
#define SNAKE_L 12

#define XM 50
#define YM 24
#define SNAKE_M 6

#define XS 32
#define YS 18
#define SNAKE_S 3

#define SLEEP 50000

#define SLOW 5
#define MEDIUM 3
#define FAST 2


void flush_screen(int, int);
struct snake* addnode(void);
void addbody_still(void);
void addbody_move(int);
void create_food(void);
char getinput(void);
void snake_move(int, int);
int setlflag(int, int);

struct point {
    int x;
    int y;
};

struct snake {
    struct point snakebody;
    int count;
    struct snake *prev;
    struct snake *next;
};

int timecnt, inputcnt, askcnt, foodchange, score;
int score_weighting, time_weighting;
int inputb4, input;
int food_flag, fail_flag;
time_t start, changefood, now;
struct snake* g_pHEAD = NULL;
struct snake* g_pTAIL = NULL;
struct point food;
struct point wallsize;
char buf[128];

int main()
{
    system("clear");
    printf("Hello, mate! Are you ready for the game?\nIf yes, plz hit ENTER.\n");
    int i = getchar();
    if(i != 10 && i != 14)
    {
        printf("Fine. Hope to see you next time!\n");
        return -1;
    }
    else
    {
        printf("PLZ choose a speed at which the snake moves.\nType in '1' for SLOW.\nType in '2' for MEDIUM.\nType in '3' for FAST.\n");
        int speed_choose, speed = 0;
        while(speed == 0)
        {
        scanf("%d", &speed_choose);
        switch(speed_choose)
        {
            case 1:
                speed = SLOW;
                break;
            case 2:
                speed = MEDIUM;
                break;
            case 3:
                speed = FAST;
                break;
            default:
                speed = 0;
                printf("WRONG ENTER. PLZ type in another correct one:");                
        }
        }
        printf("PLZ choose a size for the map.\nType in '1' for SMALL.\nType in '2' for MEDIUM.\nType in '3' for LARGE.\n");
        int wall_choose, snakesize = 0;
        
        while(snakesize == 0)
        {
        scanf("%d", &wall_choose);
        switch(wall_choose)
        {
            case 1:
                wallsize.x = XS;
                wallsize.y = YS;
                snakesize = SNAKE_S;
                break;
            case 2:
                wallsize.x = XM;
                wallsize.y = YM;
                snakesize = SNAKE_M;
                break;
            case 3:
                wallsize.x = XL;
                wallsize.y = YL;
                snakesize = SNAKE_L;
                break;
            default:
                snakesize = 0;
                printf("WRONG ENTER. PLZ type in another correct one:");                
        }
        }
        score_weighting = speed_choose + 3 - wall_choose;
        time_weighting = 4 - speed_choose + wall_choose;
        for( ; snakesize > 0; snakesize--)
        {
            addbody_still();
        }
        printf("\033[?25l");
        system("clear");
        flush_screen(wallsize.x, wallsize.y);
        create_food();
        input = 119;
        askcnt = 1;        
        sleep(1);
        time(&start);
        time(&changefood);
        while(fail_flag != 1)
        {
            food_flag = 0; 
            fail_flag = 0;
            printf("\033[H");
            flush_screen(wallsize.x, wallsize.y);
            if(input != 0)
            {
                inputb4 = input;
                //printf("      %d \n",inputb4);                
            }
            input = getinput();
            usleep(SLEEP);
            while(input == 0 && askcnt != speed)
            {
                input = getinput();
                usleep(SLEEP);  
                askcnt++;          
            }
            askcnt = 1;
            int cond = abs(input-inputb4);
            if((cond == 4 || cond == 3))
            {
                input = inputb4;
            }
            time(&now);
            if(food_flag == 0)
            {
                if(difftime(now,changefood) == 5.0 * time_weighting)
                {
                    create_food(); 
                    time(&changefood);                   
                }
      
            }
            else  
            {
                create_food();
                time(&changefood);            
            }           
            snake_move(input, inputb4);
            //score = difftime(now,start)*score_weighting;
            printf("score: %g Playing time:%g\n", score + difftime(now,start)*score_weighting, difftime(now,start));
        }
        printf("Thank you for your playing!\n");
        printf("\033[?25h");
    }
    setlflag(ECHO | ICANON, 1);
    return 0;
}

void flush_screen(int x, int y)
{
    //system("clear");
    struct point node;
    int tmp;
    char check = 0;
    for(node.y=0; node.y < y; node.y++)
    {
        for(node.x=0; node.x < x; node.x++)
        {
            if(node.y == 0)
            {
                printf("#");    
                fflush(stdout);        
            }

            if(node.x == 0 && node.y != 0)
            {
                printf("\n#");
                fflush(stdout);
            }
            if(node.y != y-1 && node.y != 0 && node.x != 0)
            {

                if(node.y == food.y && node.x == food.x)
                {
                    check = 'f';
                }
                if(node.y == g_pHEAD->snakebody.y && node.x == g_pHEAD->snakebody.x)
                {
                    check = 'h';
                    if(food.y == g_pHEAD->snakebody.y && food.x == g_pHEAD->snakebody.x)
                    {
                        addbody_move(inputb4);
                        food_flag = 1;
                    }                       
                }
                for(struct snake* psort = g_pHEAD->next; psort != NULL; psort = psort->next)
                {
                    if(node.y == psort->snakebody.y && node.x == psort->snakebody.x)
                    {
                        check = 'b';
                    }
                }
                if(check == 'h')
                {
                    printf("\033[40;33mO\033[0m");
                    fflush(stdout);
                    check = 0;
                }
                else if(check == 'b')
                {
                    printf("o");
                    fflush(stdout);
                    check = 0;
                }
                else if(node.x == x-1)
                {
                    printf("#");                
                    fflush(stdout);
                }

                else if(check == 'f')
                {
                    printf("\033[40;31mX\033[0m");
                    fflush(stdout);
                    check = 0;
                }
                else
                {
                    printf(" ");
                    fflush(stdout);                    
                }
            }
            if(node.y == y-1 && node.x != 0)
            {
                printf("#");
                fflush(stdout); 
            }
            if(node.y == y-1 && node.x == x-1)
            {
                printf("\n");
                fflush(stdout); 
            }
        }
    }
}

struct snake* addnode(void)
{
    struct snake* p = NULL;
    p = (struct snake*)malloc(sizeof (struct snake));
    memset(p, 0, sizeof(struct snake));
    return p;
}

void create_food(void)
{
    time_t t;
    srand((unsigned) time(&t));
    food.x = 1 + (int)rand()%(wallsize.x-2);
    srand((unsigned) time(&t));
    food.y = 1 + (int)rand()%(wallsize.y-2);
    for(struct snake* psort = g_pHEAD; psort != NULL; psort = psort->next)
    {
        if(food.y == psort->snakebody.y && food.x == psort->snakebody.x)
        {
            create_food();
        }
    }
    //printf("%d %d", food.x, food.y);
}

void addbody_still(void)
{
    struct snake *pnew;
    pnew = addnode();
    pnew->next = NULL;
    pnew->prev = NULL;
    if(g_pHEAD == NULL)
    {
        g_pHEAD = pnew;
        g_pHEAD->snakebody.x = wallsize.x/2;
        g_pHEAD->snakebody.y = wallsize.y/2;
    }
    else
    {
        g_pTAIL->next = pnew;
        pnew->snakebody.x = g_pTAIL->snakebody.x;
        pnew->snakebody.y = g_pTAIL->snakebody.y+1;
        pnew->prev = g_pTAIL;
    }
    g_pTAIL = pnew;

}

void addbody_move(int inputb4)
{
    struct snake *pnew;
    pnew = addnode();
    pnew->next = NULL;
    pnew->prev = NULL;
    g_pTAIL->next = pnew;
    pnew->prev = g_pTAIL; 
            switch(inputb4)
            {
                case 87:case 119:
                    pnew->snakebody.y = g_pTAIL->snakebody.y+1;
                    break;
                case 65:case 97:
                    pnew->snakebody.x = g_pTAIL->snakebody.x+1;
                    break;
                case 83:case 115:
                    pnew->snakebody.y = g_pTAIL->snakebody.y-1;
                    break;
                case 68:case 100:
                    pnew->snakebody.x = g_pTAIL->snakebody.x-1; 
                    break;
                case 0:
                    pnew->snakebody.y = g_pTAIL->snakebody.y+1;
                    break;                                    
            }   
    g_pTAIL = pnew;
    score = score + (20.0 - difftime(now,changefood))*score_weighting;
}

int setlflag(int flags, int enable)
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    if (enable) {
        attr.c_lflag |= flags;
    } else {
        attr.c_lflag &= ~flags;
    }
    return tcsetattr(STDIN_FILENO, TCIFLUSH, &attr);
}

char getinput(void)
{
    int attr = 1;
    int len = 0;
    int total = 0;
    char buf[128];
    memset(buf, 0, sizeof(buf));
    ioctl(STDIN_FILENO, FIONBIO, &attr);
    setlflag(ECHO | ICANON, 0);
    len = read(STDIN_FILENO, &buf[0], 1);
    if (len > 0)
    {
        //inputcnt++;
        return *buf;
    }
    else
        return 0;

}


void snake_move(int input, int inputb4)
{
    for(struct snake* psort = g_pTAIL; psort != g_pHEAD; psort = psort->prev)
    {
        psort->snakebody.x = psort->prev->snakebody.x;
        psort->snakebody.y = psort->prev->snakebody.y;
    } 
    switch(input)
    {
        case 87:case 119:
            g_pHEAD->snakebody.y = g_pHEAD->snakebody.y-1;
            break;
        case 65:case 97:
            g_pHEAD->snakebody.x = g_pHEAD->snakebody.x-1;
            break;
        case 83:case 115:
            g_pHEAD->snakebody.y = g_pHEAD->snakebody.y+1;
            break;
        case 68:case 100:
            g_pHEAD->snakebody.x = g_pHEAD->snakebody.x+1;
            break;
        case 0:
            switch(inputb4)
            {
                case 87:case 119:
                    g_pHEAD->snakebody.y = g_pHEAD->snakebody.y-1;
                    break;
                case 65:case 97:
                    g_pHEAD->snakebody.x = g_pHEAD->snakebody.x-1;
                    break;
                case 83:case 115:
                    g_pHEAD->snakebody.y = g_pHEAD->snakebody.y+1;
                    break;
                case 68:case 100:
                    g_pHEAD->snakebody.x = g_pHEAD->snakebody.x+1; 
                    break;
                case 0:
                    g_pHEAD->snakebody.y = g_pHEAD->snakebody.y-1;
                    break;                                  
            }

    }
    if(g_pHEAD->snakebody.x == 0 || g_pHEAD->snakebody.x == wallsize.x-1 || g_pHEAD->snakebody.y == 0 || g_pHEAD->snakebody.y == wallsize.y-1)
        fail_flag = 1;
    for(struct snake* psort = g_pTAIL; psort != g_pHEAD->next; psort = psort->prev)
    {
        if(g_pHEAD->snakebody.x == psort->snakebody.x && g_pHEAD->snakebody.y == psort->snakebody.y)
            fail_flag = 1;
    }
}


