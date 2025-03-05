#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define l_MAX 512
#define w_MAX 128

struct word_t* addnode(void);
void clear_punc(char *, int);
struct word_t *addtree(struct word_t *, char *);
void treeprint(struct word_t *);
void change_cap(char *);
int find_max(struct word_t *);
struct word_t* findword(struct word_t *, int);

struct word_t* g_pROOT = NULL;
struct word_t* psort, * pnode;
int linecnt, wordcnt, printcnt;

struct word_t {
    char* pword;
    int count;
    int flag;
    struct word_t* left;
    struct word_t* right;
};

int main(int argc, char *argv[])
{
    FILE *fp;
    int size;
    char buf[l_MAX], word_c[w_MAX], word_tmp[w_MAX];
    char *filename, *p1, *p2;

    filename = argv[1];
    printf("The filename is %s.\n", filename);
    if ((fp = fopen(filename,"r")) == NULL)
    {
        printf("ERROR\n");
        return -1;
    }
    memset(buf, 0, sizeof(buf));
    for(linecnt = 0; fgets(buf, l_MAX, fp) != NULL; linecnt++)
    {
        p2 = buf;
        if(*p2 < 32)
            continue;
        while(*p2 < 65 || (*p2 > 90 && *p2 < 97) || *p2 > 122)
            p2++;
        while(*p2 > 31)
        {
            p1 = p2;
            while(*p2 > 32)
                p2++;
            size = p2-p1;
            while(*p2 == 32)
                p2++;

            memset(word_c, 0, sizeof(word_c));
            strncpy(word_c, p1, size);
            clear_punc(word_c, size);
            if(*word_c != 0)
            {
                change_cap(word_c);
                g_pROOT = addtree(g_pROOT, word_c);
            }
        }
        memset(buf, 0, sizeof(buf));
    }
    printf("There are %d lines.\n", linecnt);
    treeprint(g_pROOT);

    printf("\nHow many words you wanna print by word frequency (There are %d words.):\n", wordcnt);
    int n;
    scanf("%d", &n);
    for(int num=1; num <= n; num++)
    {
        while(1)
        {
            int max = find_max(g_pROOT);
            findword(g_pROOT, max);
            struct word_t* maxword = psort;
            if (maxword != NULL)
            {
                if(max > 1)
                {
                    printf("NO.%-3d:  %-20s  for %-3d times\n", num, maxword->pword, max);
                    maxword->flag = 1;
                }
                if(max == 1)
                {
                    printf("NO.%-3d:  %-20s  for %-3d time\n", num, maxword->pword, max);
                    maxword->flag = 1;
                }
                break;
            }

        }
    }

    fclose(fp);
    return 0;
}

struct word_t* addnode(void)
{
    struct word_t* p = NULL;
    p = (struct word_t*)malloc(sizeof (struct word_t));
    memset(p, 0, sizeof(struct word_t));
    return p;
}

void clear_punc(char *src, int size)
{
    char *p;
    p = src+size-1;
    *(p+1) = 0;
    while(p != src)
    {
        if(*p < 65 || (*p > 90 && *p < 97) || *p > 122)
        {
            *p = 0;
            p--;
        }
        else
        {
            break;
        }
    }
    for(p = src; *p > 31 && (*p < 65 || (*p > 90 && *p < 97) || *p > 122); p = src)
    {
        while(*p > 31)
        {
            *p = *(p+1);
            p++;
        }
    }
}

void change_cap(char *src)
{
    if(strlen(src) > 1 && isupper(*src) != 0 && islower(*(src+1)) != 0)
        *src = tolower(*src);
    if(strlen(src) == 1 && isupper(*src) != 0)
        *src = tolower(*src);
}

struct word_t *addtree(struct word_t *pointer, char *str4n)
{
    int condition;
    if (pointer == NULL)
    {
        pointer = addnode();
        pointer->count = 1;
        pointer->flag = 0;
        pointer->pword = (char*)malloc(strlen(str4n));
        strcpy(pointer->pword, str4n);
        pointer->left = pointer->right = NULL;
    }
    else if ((condition = strcmp(str4n, pointer->pword)) == 0)
    {
        pointer->count++;
    }
    else if (condition < 0)
    {
        pointer->left = addtree(pointer->left, str4n);
    }
    else
    {
        pointer->right = addtree(pointer->right, str4n);
    }
    return pointer;
}

void treeprint(struct word_t *proot)
{
    if(proot != NULL)
    {
        treeprint(proot->left);
        printf(" | %-20s %-3d |  ", proot->pword, proot->count);
        wordcnt++;
        printcnt++;
        if(printcnt % 5 == 0)
            printf("\n");
        treeprint(proot->right);
    }
}

int find_max(struct word_t *proot)
{
    if(proot != NULL)
    {
        int i, j, k, max;
        i = (proot->flag == 0) ? proot->count : 0;
        j = find_max(proot->left);
        k = find_max(proot->right);
        if(j >= i)
        {
            if(i >= k)
                max = j;
            else
            {
                if(j >= k)
                    max = j;
                else
                    max = k;
            }
        }
        else
        {
            if(j >= k)
                max = i;
            else
            {
                if(i >= k)
                    max = i;
                else
                    max = k;
            }
        }
        return max;
    }
    else
        return 0;

};

struct word_t* findword(struct word_t *proot, int maxcnt)
{
    if(proot != NULL)
    {
        findword(proot->left, maxcnt);
        if(proot->flag == 0 && proot->count == maxcnt)
        {
            //proot->flag = 1;
            psort = proot;
            return proot;
        }
        //else
        //return NULL;
        findword(proot->right, maxcnt);
    }
    else
        return NULL;
}