#include <stdio.h>

main() {

    int i = 0, j = 0;

    for (i = 9; i > 0; i--) {
        for (j = 1; j <=i; j++)
            printf("%dx%d=%d ", j, i, i*j);
        printf("\n");
    }
}
