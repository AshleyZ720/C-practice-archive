#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_t* addnode(void);
void printlist(struct list_t*);
struct list_t* sortlist(struct list_t*);

struct list_t {
    int num;
    struct list_t* next;
    struct list_t* prev;
};

struct list_t* g_pHEAD = NULL;
struct list_t* g_pTAIL = NULL;

int main()
{
    int check = 1;
    struct list_t* pnew = NULL;
    do
    {
        printf("PLZ give me an integer (if you wanna stop, type in 'q'):");
        pnew = addnode();
        check = scanf("%d", &(pnew->num));
        if(check != 1)
        {
            break;
        }
        //printf("%d\n", check);
        pnew->next = NULL;
        pnew->prev = NULL;
        if(g_pHEAD == NULL)
        {
            g_pHEAD = pnew;
        }
        else
        {
            g_pTAIL->next = pnew;
            pnew->prev = g_pTAIL;
        }
        g_pTAIL = pnew;
    } while (1);
    printlist(g_pHEAD);
    g_pHEAD = sortlist(g_pHEAD);
    printlist(g_pHEAD);
    return 0;
}

struct list_t* addnode(void)
{
    struct list_t* p = NULL;
    p = (struct list_t*)malloc(sizeof (struct list_t));
    memset(p, 0, sizeof(struct list_t));
    return p;
}

void printlist(struct list_t* plist)
{
    struct list_t* pnode = NULL;
    for(pnode = plist; pnode != NULL; pnode = pnode->next)
    {
        printf("%d ", pnode->num);
    }
    printf("\n");
}

struct list_t* sortlist(struct list_t* plist)
{
    struct list_t* psort, * pnode, * phead;
    int count = 0;
    while(plist->prev != NULL)
    {
        plist = plist->prev;
    }
    pnode = phead = plist;
    do
    {
        psort = pnode;
        while (pnode->next != NULL)
        {
            pnode = pnode->next;
            psort = (psort->num > pnode->num) ? psort : pnode;
            count++;
            printf("hello, %d %d %d\n", psort->num, pnode->num, count);
        }
        while(count>0)
        {
            pnode = pnode->prev;
            count--;
            printf("%d %d %d\n", psort->num, pnode->num, count);
        }
        if(pnode == psort)
        {
            if(pnode->next != NULL)
            {
                pnode = pnode->next;
            }
            if(psort == phead)
            {
                continue;
            }
        }
        if(psort->prev != NULL)
        {
            psort->prev->next = psort->next;
        }
        if(psort->next != NULL)
        {
            psort->next->prev = psort->prev;
        }
        phead->prev = psort;
        psort->next = phead;
        psort->prev = NULL;
        phead = psort;
        printf("%d\n", phead->num);
    } while (pnode != phead);
    return phead;
}