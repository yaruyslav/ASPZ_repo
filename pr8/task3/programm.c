#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct sort_data {
    void *arr_bf;
    void *arr_af;
    int size;
    char type_arr;
    double work;
};

char type;
int cmp_more(const void *a, const void *b) {
    if (type=='i') {
        if (*(int *)a > *(int *)b)
            return 1;
        else if (*(int *)a < *(int *)b)
            return -1;
    } else if (type=='d') {
        if (*(double *)a > *(double *)b)
            return 1;
        else if (*(double *)a < *(double *)b)
            return -1;
    } else if (type=='c') {
        if (*(char *)a > *(char *)b)
            return 1;
        else if (*(char *)a < *(char *)b)
            return -1;
    }
    return 0;
}

int cmp_less(const void *a, const void *b) {
    if (type=='i') {
        if (*(int *)a < *(int *)b)
            return 1;
        else if (*(int *)a > *(int *)b)
            return -1;
    } else if (type=='d') {
        if (*(double *)a < *(double *)b)
            return 1;
        else if (*(double *)a > *(double *)b)
            return -1;
    } else if (type=='c') {
        if (*(char *)a < *(char *)b)
            return 1;
        else if (*(char *)a > *(char *)b)
            return -1;
    }
    return 0;
}

void print_elem(void *arr, int num) {
    if (type=='i') {
        printf("%d", *((int *)arr+num));
    } else if (type=='d') {
        printf("%f", *((double *)arr+num));
    } else if (type=='c') {
        printf("%c", *((char *)arr+num));
    }
}

void out_array(void *arr, int size) {
    for (int i=0; i<size; i++) {
        if (i+1==size) {
            print_elem(arr, i);
            printf("\n");
            break;
        }
        print_elem(arr, i);
        printf(", ");
    }
}

int get_size() {
    if (type=='i')
        return sizeof(int);
    else if (type=='d')
        return sizeof(double);
    else if (type=='c')
        return sizeof(char);
    return 0;
}

double get_double(int num1, int num2) {
    char arr1[11], arr2[11], double_str[23];
    sprintf(arr1, "%d", num1);
    sprintf(arr2, "%d", num2);
    strcpy(double_str, arr1);
    strcat(double_str, ".");
    strcat(double_str, arr2);
    // printf("''%f''\n", atof(double_str));
    return atof(double_str);
}

struct sort_data* check_array(int size, int max, char type_in, char sort_t) {
    type = type_in;

    struct sort_data *data = (struct sort_data *)malloc(sizeof(struct sort_data)*20);
    int curr_size, data_s;
    void *arr;

    srand(time(0));
    data_s = 0;
    int for_num = (max-size);
    if (for_num<7)
        for_num = 7;
    for (int i=0; i<for_num && i<20; i++) {
        curr_size = (i+size);
        if (curr_size>max)
            curr_size = max;

        if (type=='c')
            arr = (char *)malloc(curr_size*sizeof(char));
        else if (type=='i')
            arr = (int *)malloc(curr_size*sizeof(int));
        else if (type=='d')
            arr = (double *)malloc(curr_size*sizeof(double));

        for (int j=0; j<curr_size; j++) {
            if (type=='c')
                *((char *)arr+j) = rand()%24+65;
            else if (type=='i')
                *((int *)arr+j) = rand()%100000;
            else if (type=='d')
                *((double *)arr+j) = get_double(rand()%10000, rand()%10000);
        }

        void *arr_before;
        if (type=='c') {
            arr_before = (char *)malloc(curr_size*sizeof(char));
            for (int m=0; m<curr_size; m++)
                *((char *)arr_before+m) = *((char *)arr+m);
        } else if (type=='i') {
            arr_before = (int *)malloc(curr_size*sizeof(int));
            for (int m=0; m<curr_size; m++)
                *((int *)arr_before+m) = *((int *)arr+m);
        } else if (type=='d') {
            arr_before = (double *)malloc(curr_size*sizeof(double));
            for (int m=0; m<curr_size; m++)
                *((double *)arr_before+m) = *((double *)arr+m);
        }

        time_t time_st = clock();
        if (sort_t=='b')
            qsort(arr, curr_size, get_size(), cmp_more);
        else if (sort_t=='l')
            qsort(arr, curr_size, get_size(), cmp_less);
        else {
            printf("Wrong type sorting!\n");
            return 0;
        }
        time_t time_ed = clock();

        data[data_s].arr_af = arr;
        data[data_s].arr_bf = arr_before;
        data[data_s].size = curr_size;
        data[data_s].work = ((double)(time_ed-time_st))/CLOCKS_PER_SEC;
        data[data_s].type_arr = type;
        arr = NULL;
        data_s++;
    }

    return data;
}

void my_free(struct sort_data *arr) {
    for (int i=0; i<20; i++) {
        if ((arr+i)->arr_af) {
            free((arr+i)->arr_af);
        }
        if ((arr+i)->arr_bf) {
            free((arr+i)->arr_bf);
        }
    }
    free(arr);
}

void out_arr(struct sort_data *data, char out_t) {
    for (int i=0; i<(data)->size; i++) {
        if (out_t=='r') {
            if ((data)->type_arr=='c')
                printf("%c ", *(((char *)(data->arr_bf))+i));
            else if ((data)->type_arr=='d')
                printf("%f ", *(((double *)(data->arr_bf))+i));
            else if ((data)->type_arr=='i')
                printf("%d ", *(((int *)(data->arr_bf))+i));
                // printf("%d ", *((int *)(((data)->arr_bf)+i)));
            if (i>64) {
                printf("...");
                break;
            }
        } else if (out_t=='s') {
            if ((data)->type_arr=='c')
                printf("%c ", *(((char *)(data->arr_af))+i));
            else if ((data)->type_arr=='i')
                printf("%d ", *(((int *)(data->arr_af))+i));
                // printf("%d ", *((int *)(((data)->arr_af)+i)));
            else if ((data)->type_arr=='d')
                printf("%f ", *(((double *)(data->arr_af))+i));
            if (i>64) {
                printf("...");
                break;
            }
        }
    }
}

struct sort_data *search_slow(struct sort_data *data) {
    double max;
    max = 0;
    for (int i=0; (data+i)->size; i++) {
        if (max < (data+i)->work)
            max = (data+i)->work;
    }
    for (int i=0; (data+i)->size; i++) {
        if ((data+i)->work==max) {
            return data+i;
        }
    }
    return NULL;
}

int main() {
    int size_fir, size_lim;
    struct sort_data *curr;

    printf("\n\tChar array:\n");
    size_fir = 55, size_lim = 62;
    curr = check_array(size_fir, size_lim, 'c', 'b');

    struct sort_data *slowest = search_slow(curr);
    int id_slow;
    for (int i=0; i<20; i++) {
        if (!curr)
            break;
        if (slowest==(curr+i)) {
            id_slow = i;
        }
        if ((curr+i)->arr_bf) {
            printf("Before sorting %d: ", i+1);
            out_arr(curr+i, 'r');
            printf("\nAfter sorting %d: ", i+1);
            out_arr(curr+i, 's');
            printf("\nSort time: %f sec\n\n", (curr+i)->work);
        }
    }
    printf("Slowest sorting is %d: ", id_slow+1);
    printf("\nSort time: %f sec\n", (curr+id_slow)->work);
    my_free(curr);
}