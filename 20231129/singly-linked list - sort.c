#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct az* addnode(void);
void printlist(struct az*);
struct az* sortlist(struct az*);

struct az{
    int i;
    struct az* pnext;
};

struct az* phead = NULL;
struct az* ptail = NULL;
struct az* pnode = NULL;
struct az* pnew = NULL;

int main()
{
    int check = 1;   
    do
    {
        printf("PLZ give me an integer (if you wanna stop, type in 'q'):");
        pnew = addnode();
        check = scanf("%d", &(pnew->i));
        if(check != 1)
        {
            break;
        }
        printf("%d\n", check);
        pnew->pnext = NULL;
        if(phead == NULL)
        {
            phead = pnew;
            //ptail = pnew;
        }else{
            ptail->pnext = pnew;
            //ptail = pnew;
        }
        ptail = pnew;
        //pnode = pnew;
    } while (1);
    printlist(phead);
    phead = sortlist(phead);
    printlist(phead);
    return 0;
}

struct az* addnode(void)
{
    struct az* p = NULL;
    p = (struct az*)malloc(sizeof (struct az));
    memset(p, 0, sizeof(struct az));
    return p;
}

void printlist(struct az* phead)
{
    for(pnode = phead; pnode != NULL; pnode = pnode->pnext)
    {
        printf("%d ", pnode->i);
    }
    printf("\n");    
}

struct az* sortlist(struct az* phead)
{
    while(1)
    {
        struct az* psort = phead;
        pnode = phead;
        while(pnode->pnext != NULL && psort->i > pnode->pnext->i)
        {
            pnode = pnode->pnext;
        }
        if(pnode != phead)
        {
            phead = phead->pnext;
            psort->pnext = pnode->pnext;
            pnode->pnext = psort;            
            if(pnode->pnext == NULL)
            {
                ptail = pnode;
            }
        }
        else
        {
            struct az* pdaddy;
            do
            {
                pdaddy = psort;
                psort = psort->pnext;
            } while (psort->pnext != NULL && psort->i < psort->pnext->i);
            if(psort->pnext != NULL)
            {
                pnode = psort;
                while(pnode->pnext != NULL && psort->i > pnode->pnext->i)
                {
                    pnode = pnode->pnext;
                }
                pdaddy->pnext = psort->pnext;
                psort->pnext = pnode->pnext;
                if(pnode->pnext == NULL)
                {
                    ptail = psort;
                }
                pnode->pnext = psort;
            }
            else
            {
                break;
            }
        }  
    }
    return phead;
}