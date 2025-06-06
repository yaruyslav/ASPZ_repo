#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr1 = malloc(sizeof(int));
    int *ptr2;

    ptr2 = realloc(ptr1, 0);
    if (ptr2!=NULL) {
        printf("Memory reallocated with size 0 bytes!\n");
        free(ptr2);
    } else {
        printf("Realloc can't reallocate memory with size 0 bytes!\n");
    }

    ptr2 = realloc(NULL, 12345);
    if (ptr2!=NULL) {
        printf("Memory reallocated with size 12345 and NULL variable!\n");
        free(ptr2);
    } else {
        printf("Realloc can't reallocate memory with size 12345 and NULL variable!\n");
    }
}
