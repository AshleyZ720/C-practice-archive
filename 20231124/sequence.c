#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct sample {
    int count;
    int *integer;
    struct sample *last;
    struct sample *next;
} ;

struct sample *talloc();
struct sample *addtree(struct sample *, int *);
int intcmp(int *, int *);
void treeprint(struct sample *);

int main()
{
    int tmp=0, n, check;
    int store[MAX];
    struct sample *root;
    root = NULL;
    do
    {
        printf("Please type in an integer:");
        check = scanf("%d\n",&n);
        *(store + tmp) = n;
        tmp++;
        root = addtree(root, (store + tmp));
        printf("If you wanna stop, type in 'q'\n");        
    }
    while(check != 0 || check != -1);
    treeprint(root);
    return 0;
}

struct sample *addtree(struct sample *pointer, int *int4n)
{
    int condition;
    if (pointer == NULL)
    {
        pointer = talloc();
        pointer->count = 1;
        pointer->integer = int4n;
        pointer->last = pointer->next = NULL;
    }
    else if ((condition = intcmp(int4n, pointer->integer)) == 0)
    {
        pointer->count++;
    }
    else if (condition < 0)
    {
        pointer->last = addtree(pointer->last, int4n);
    }
    else
    {
        pointer->next = addtree(pointer->next, int4n);
    }
    return pointer;
}

struct sample *talloc(void)
{
    return (struct sample *) malloc(sizeof(struct sample));
}

int intcmp(int *int1, int *int2)
{
    return ((*int1)-(*int2));
}

void treeprint(struct sample *s)
{
    if(s != NULL)
    {
        treeprint(s->last);
        for(; s->count>0; s->count--)
        {
            printf("%d ", *(s->integer));
        }
        treeprint(s->next);
    }
}