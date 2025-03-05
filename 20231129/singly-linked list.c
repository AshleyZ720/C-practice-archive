#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct az* addnode(void);

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
    #if 1
    for(pnode = phead; pnode != NULL; pnode = pnode->pnext)
    {
        printf("%d ", pnode->i);
    }
    #endif
    printf("\n");
    return 0;
}

struct az* addnode(void)
{
    struct az* p = NULL;
    p = (struct az*)malloc(sizeof (struct az));
    memset(p, 0, sizeof(struct az));
    return p;
}