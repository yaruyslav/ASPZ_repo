#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void) {
	int *ptr;

	mallopt(M_CHECK_ACTION, 1);
	ptr = malloc(8);
	free(ptr);
	free(ptr);

	printf("Text after free\n");
	return 0;
}