#include <stdio.h>
#include <time.h>

void iterations(int num) {
	for (int i=0; i<num; i++) {}
}

int main(void) {
	clock_t start, end;
	int iter = 4000000;
	start = clock();

	iterations(iter);

	end = clock();
	double res_time = ((double)(end-start))/CLOCKS_PER_SEC*1000;
	printf("Time of %d iterations is %f miliseconds!\n", iter, res_time);
}