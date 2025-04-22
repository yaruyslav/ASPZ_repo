#include <stdio.h>
#include <stdlib.h>
void funk() {
    int l[1000]; 
    int m[1200];
    int s[1500];
    int j;
    printf("current top of stack is %p\n", &j);
}
int num = 23;
int main(void) {
    int i;
    printf("the stack top is near %p\n", &i);
    int *dynam = malloc(sizeof(int));
    printf("top of text is %p\n", &num);
    printf("top of data is %p\n", main);
    printf("top of heap is %p\n", dynam);
    funk();
}