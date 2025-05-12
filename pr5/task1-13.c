#include <stdio.h>
#include <stdlib.h>

char *global_var = NULL;

void init_shifted() {
	char *var = malloc(10*sizeof(char));
	global_var = var + 1;
}

int main(void) {
	init_shifted();
	*global_var = 'S';
	printf("Shifted global var[0] = %c\n", *global_var);
	return 0;
}