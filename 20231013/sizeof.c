#include <stdio.h>
int main()
{
    char c = 'a'; 
    char a[50]="老师,早上好!";
    printf("%ld", sizeof(a));   
    printf("%ld", sizeof(c));     
    printf("%ld", sizeof('a'));
    printf("%ld", sizeof("abcefg"));
}
