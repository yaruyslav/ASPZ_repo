#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t num;

    num = 4196863304;
    char *arr = malloc(num);
    if (arr!=NULL) {
        printf("Max size of char array is %lu bytes!\n", num);
        free(arr);
    } else {
        printf("Size of char array isn't initialised!\n");
    }
}