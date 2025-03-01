#include <stdio.h>
#include <stdlib.h>
void show(int *arr,int len) {
    printf("Current array: ");
    if (arr) {
        for (int i=0; i<len; i++) {
            printf("%d ", *(arr+i));
        }
    } else {
        printf("-");
    }
    putchar('\n');
}
int enter_len() {
    int len;
    printf("Enter lenght (1 to continue): ");
    scanf("%d", &len);
    if (!(len>=1&&len<=100)) {
        printf("Enter number from 2 to 100!\n");
        return 0;
    }
    return len;
}
int main(void) {
    int state;
    state = 0;
    int len;
    for (;;) {
        len = enter_len();
        if (len) {
            break;
        }
    }
    int *arr = NULL;
    if (len > 1) {
        arr = (int *)malloc(len);
        for (int i=0; i<len; i++) {
            *(arr+i) = len;
        }
        state = 1;
    }
    show(arr,len);
    
    char *choi = (char *)malloc(5);
    printf("You can change size of array, get current state of memory or close the programm\n");
    while (1) {
        printf("Enter (ch/mem/ex): ");
        scanf("%s", choi);
        if (*(choi)=='c'&&*(choi+1)=='h') {
            int curr = enter_len();
            if (!curr) {
                continue;
            } else if (curr!=1) {
                len = curr;
                arr = (int *)malloc(len);
                for (int i=0; i<len; i++) {
                    *(arr+i) = len;
                }
                arr = realloc(arr,len);
                state = 2;
            }
            show(arr,len);
        } else if (*(choi)=='m'&&*(choi+1)=='e'&&*(choi+2)=='m') {
            if (state==0) {
                printf("Memory is free!\n");
            } else if (state==1) {
                printf("Memory is initialised and has size %d!\n", len);
            } else if (state==2) {
                printf("Memory is reloaded and has size %d!\n", len);
            }
        } else if (*(choi)=='e'&&*(choi+1)=='x') {
            break;
        }
    }
    printf("Closing...\n");
    return 0;
}