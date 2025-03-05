#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

struct line_t{
    char* pline;
    struct line_t* next;
};

int main(int argc, char *argv[])
{
    FILE *fp;
    printf("argc = %d\n", argc);
    printf("%s", argv[1]);
    fflush(stdout);
    //return -1;
    sleep(3);

    char *filename = NULL;
    char buf[MAX]; 
    memset(filename, 0, sizeof(filename));

    filename = argv[1]; 
    if ((fp = fopen(filename,"r")) == NULL)
    {
        printf("ERROR: %d,%s\n", errno, filename);   
        return 0;
    }  
    while(fgets(buf, MAX , fp) != NULL) 
        printf("%s", buf);   
    fclose(fp); 
}

#if (0)
int linecnt(char *tmpstr, File *tmpfp)
{
    int count;
    char *pnew;
    for(count = 0; pnew->pline != NULL; count++)
    {
        pnew = add_l_node;
        pnew->pline = fgets(tmpstr, MAX, tmpfp);
    } 
    
}

struct line_t* add_l_node(void)
{
    struct line_t* p = NULL;
    p = (struct line_t*)malloc(sizeof (struct line_t));
    memset(p, 0, sizeof(struct line_t));
    return p;
}


struct word_t* add_w_node(void)
{
    struct word_t* p = NULL;
    p = (struct word_t*)malloc(sizeof (struct word_t));
    memset(p, 0, sizeof(struct word_t));
    return p;
}
#endif
