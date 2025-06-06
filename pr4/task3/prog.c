#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num;
    char *arr;

    num = -23;
    arr = malloc(num);
    printf("1. Allocation mamory with number %d:\n", num);
    if (arr!=NULL) {
        printf("Memory allocated with size %zu bytes!\n", (size_t)num);
        printf("Memory freed.\n");
        free(arr);
    } else {
        printf("Malloc can't allocate memory with size %zu bytes!\n", (size_t)num);
        printf("Memory didn't freed because memory didn't allocated!\n");
    }

    num = 12;
    arr = malloc(num);
    printf("2. Allocation mamory with number %d:\n", num);
    if (arr!=NULL) {
        printf("Memory allocated with size %zu bytes!\n", (size_t)num);
        printf("Memory freed.\n");
        free(arr);
    } else {
        printf("Malloc can't allocate memory with size %zu bytes!\n", (size_t)num);
        printf("Memory didn't freed because memory didn't allocated!\n");
    }
}
