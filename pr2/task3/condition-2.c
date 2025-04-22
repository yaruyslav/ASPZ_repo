#include <stdio.h>
#include <stdlib.h>
int num = 23;
int main(void) {
    int *dynam = malloc(sizeof(int));
    printf("top of text is %p\n", main);
    printf("top of data is %p\n", &num) ;
    printf("top of heap is %p\n", dynam);
}