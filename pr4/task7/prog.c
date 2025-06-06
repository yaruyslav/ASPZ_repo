#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct sbar {
    int tables;
    double money;
    char *currency;
};

int main(void) {
    struct sbar *ptr, *newptr;
    size_t size1 = 1000, size2 = 500;
    ptr = reallocarray(NULL, size1, sizeof(struct sbar));
    newptr = reallocarray(ptr, size2, sizeof(struct sbar));
    printf("Size of ptr: %zu bytes, and newptr: %zu bytes!\n", size1, size2);

    if (ptr==newptr) {
        printf("prt = newptr.\n");
        free(newptr);
    } else {
        printf("prt != newptr.\n");
        free(ptr);
	free(newptr);
    }
}