#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void create_array1(double *arr, int size) {
	for (int i=0; i<size; i++) {
		arr[i] = (double)(rand()%10)/10;
	}
	return;
}

void create_array2(double *arr, int size, char *number) {
	int rand1, rand2;
	for (int i=0; i<size; i++) {
		int max_num = 7;
		int max_rand = 100000;

		double num = atof(number);
		if (num==0 && number[0]!='0') {
			return;
		}
		int num_int, num_frac;
		num_int = (int)num;

		if (num_int>max_rand)
			num_int = max_rand;
		else if (num_int==0)
			num_int = 1;

		rand1 = rand()%num_int;

		char *num_last = strchr(number, '.');
		if (!num_last) {
			num_frac = 0;
		} else {
			char int_arr[max_num+1];
			int i;
			for (i=1; i<max_num+1!='\0'&&isdigit(*(num_last+i)); i++) {
				int_arr[i-1] = *(num_last+i);
			}
			int_arr[i-1] = '\0';
			num_frac = atoi(int_arr);
		}

		if (num_frac>max_rand)
			num_frac = max_rand;
		else if (num_frac==0)
			num_frac = 1;

		rand2 = rand()%num_frac;
		char ch_arr[26];
		char num1[12];
		sprintf(num1, "%d", (int)rand1);
		strcpy(ch_arr, num1);
		char num2[12];
		sprintf(num2, "%d",(int)rand2);
		strcat(ch_arr, ".");
		strcat(ch_arr, num2);
		num = atof(ch_arr);
		arr[i] = num;
	}
	return;
}

void show_array(double *arr, int size) {
	for (int i=0; i<size; i++) {
		printf("%f", arr[i]);
		if (i+1<size)
			printf(" ");
		else
			printf("\n");
	}
}

char *get_stdin(int size) {
	char ch_buf;
	char *ch = malloc(size+1);
	int i;
	for (i=0; (ch_buf=getchar())!='\n';) {
		if (i<size) {
			ch[i] = ch_buf;
			i++;
		}
	}
	ch[i] = '\0';
	return ch;
}

int main(void) {
	srand(time(0));

	double num_arr[10];
	create_array1(num_arr, (sizeof(num_arr)/sizeof(num_arr[0])));
	printf("Random values from 0.0 to 1:\n");
	show_array(num_arr, (sizeof(num_arr)/sizeof(num_arr[0])));

	printf("Enter number n: ");
	char *number = get_stdin(31);
	create_array2(num_arr, (sizeof(num_arr)/sizeof(num_arr[0])), number);
	printf("Random values from 0.0 to n:\n");
	show_array(num_arr, (sizeof(num_arr)/sizeof(num_arr[0])));
	free(number);
}
