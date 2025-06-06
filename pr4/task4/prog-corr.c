#include <stdio.h>
#include <stdlib.h>

int main(void) {
    void *ptr = NULL;
    int i, n=8;
    i = 0;
    while (i<10) {
        ptr = malloc(n);
        *((int *)ptr) = i;
        printf("Current i=%d\n", *(int *)ptr);
        free(ptr);
        i++;
    }
}
