#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int xa, xb;
    size_t num;
    char *arr;

    num = -1;
    arr = malloc(num);
    printf("1. Allocation memory with negative number %d:\n", (int)num);
    if (arr!=NULL) {
        printf("Memory allocated with size %zu bytes!\n", num);
        free(arr);
    } else {
        printf("Malloc can't allocate memory with size %zu bytes!\n", num);
    }

    xa = 1954809, xb = 13;
    num = (size_t)xa * (size_t)xb;
    arr = malloc(num);
    printf("2. Allocation memory with normal number %d:\n", (int)num);
    if (arr!=NULL) {
        printf("Memory allocated with size %zu bytes!\n", num);
        free(arr);
    } else {
        printf("Malloc can't allocate memory with size %zu bytes!\n", num);
    }

    xa = 1400000002, xb = 1316980408;
    num = (size_t)xa * (size_t)xb;
    arr = malloc(num);
    printf("3. Allocation with memory overflow with number %zu:\n", num);
    if (arr!=NULL) {
        printf("Memory allocated with size %zu bytes!\n", num);
        free(arr);
    } else {
        printf("Malloc can't allocate memory with size %zu bytes!\n", num);
    }
}