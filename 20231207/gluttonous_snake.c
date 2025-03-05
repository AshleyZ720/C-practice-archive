#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#define XL 50
#define YL 24
#define SLEEP_s 100000

void flush_screen(int, int);
struct snake* addnode(void);
void addbody_still(void);
void addbody_move(int);
void create_food(void);
char getinput(void);
void snake_move(int, int);
int setlflag(int, int);
int setcc(int, int);

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

int timecnt, inputcnt, score;
int inputb4, input;
int food_flag, fail_flag;
struct snake* g_pHEAD = NULL;
struct snake* g_pTAIL = NULL;
struct point food;
char buf[128];

int main()
{
    printf("Hello, mate! Are you ready for the game?\nIf you are, plz hit ENTER.\n");
    int i = getchar();
    if(i != 10 && i != 14)
    {
        printf("Fine. Hope to see you next time!\n");
        return -1;
    }
    else
    {
        struct point wallsize;
        wallsize.x = XL;
        wallsize.y = YL;
        for(int snakesize=9; snakesize > 0; snakesize--)
        {
            addbody_still();
        }
        printf("\033[?25l");
        system("clear");
        flush_screen(wallsize.x, wallsize.y);
        sleep(1);
        input = 119;
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
            int cond = abs(input-inputb4);
            if((cond == 4 || cond == 3))
            {
                input = inputb4;
            }
            //printf("%d %d\n",input, inputb4);
            usleep(SLEEP_s);           
            //usleep(SLEEP_s);
            if(food_flag == 0)
            {
                timecnt++;            
            }
            else
                timecnt = 0;
            if(timecnt%80 == 1)
            {
                create_food();
                timecnt = 1;
            }
            score++;
            snake_move(input, inputb4);
            printf("score: %d %d\n",score, timecnt);
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
    food.x = 1 + (int)rand()%(XL-2);
    srand((unsigned) time(&t));
    food.y = 1 + (int)rand()%(YL-2);
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
        g_pHEAD->snakebody.x = XL/2;
        g_pHEAD->snakebody.y = YL/2;
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
    score = score + 100 - timecnt;
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

int setcc(int min, int timeout)
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_cc[VMIN] = min;
    attr.c_cc[VTIME] = timeout;
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
    setcc(0, 1);
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
                //default:
                    //system("pause");                                 
            }
        //default:
            //system("pause");

    }
    if(g_pHEAD->snakebody.x == 0 || g_pHEAD->snakebody.x == XL-1 || g_pHEAD->snakebody.y == 0 || g_pHEAD->snakebody.y == YL-1)
        fail_flag = 1;
    for(struct snake* psort = g_pTAIL; psort != g_pHEAD->next; psort = psort->prev)
    {
        if(g_pHEAD->snakebody.x == psort->snakebody.x && g_pHEAD->snakebody.y == psort->snakebody.y)
            fail_flag = 1;
    }
}


