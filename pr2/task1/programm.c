#include <stdio.h>
#include <time.h>
int main(void) {
    time_t t1 = 7;
    int time1 = t1;
    time_t last_t = time(0);
    time_t curr_t;
    int counter;
    counter = 1;
    printf("Wait %d seconds! \n", time1);
    do {
        curr_t = time(0);
        if ((int)(curr_t-last_t)>=counter) {
            for (int i=0; i<counter; i++) {
                printf(".");
            }
            printf("\n");
            counter++;
        }
    } while ((int)(curr_t-last_t)<time1);
    printf("Time has passed!\n" );
}