#include <stdio.h>

int myfunc(int *a){
	int b;

	printf("a1 = %d address =%x\n", *a, a);
	*a += 1;
	printf("a2 = %d address =%x\n", *a, a);

	return b;
}

int main()
{
	char x = 45, y = 65;

	myfunc(&x);

	printf("y = %c, address of x = %x, y = %x\n", y, &x, &y);
}
