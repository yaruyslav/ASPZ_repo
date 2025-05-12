#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int *ptr1 = malloc(sizeof(int));			// Memory leak
	*ptr1 = 20;
	printf("*ptr1 = %d\n", *ptr1);

	int *ptr2 = malloc(sizeof(int));			// UAF + Double free
	*ptr2 = 10;
	printf("current *ptr2 = %d\n", *ptr2);
	free(ptr2);
	*ptr2 = 12;
	printf("changed *ptr2 after free = %d\n", *ptr2);
	free(ptr2);
}