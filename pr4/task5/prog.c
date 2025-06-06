#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t size;

    size = sizeof(int)*4;
    int *ptr1 = malloc(size);
    if (ptr1!=NULL) {
        printf("Memory of ptr1 allocated with size %zu bytes!\n", size);
        *(ptr1+1) = 2;
        *(ptr1+3) = 4;
        printf("ptr1: [2]: %d; [4]: %d\n", *(ptr1+1), *(ptr1+3));
    } else {
        printf("Malloc can't allocate memory of ptr1 with size %zu bytes!\n", size);
    }

    size = -1;
    int *ptr2 = realloc(ptr1, size);
    if (ptr2!=NULL) {
        printf("Memory of ptr2 reallocated with size %zu bytes!\n", size);
        *(ptr2+2) = 3;
        *(ptr2+7) = 8;
        printf("ptr2: [3]: %d; [8]: %d\n", *(ptr2+2), *(ptr2+7));
    } else {
        printf("Realloc can't reallocate memory of ptr2 with size %zu bytes!\n", size);
    }
}
