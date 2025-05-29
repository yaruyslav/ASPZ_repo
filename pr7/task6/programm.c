#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

struct class_info {
	int size_array;
	int curr_num;
	char **array;
};

bool init_class(struct class_info *info);
bool increase_array(struct class_info *info, char *value);
bool add_val(struct class_info *info, char *value);
int get_size(struct class_info *info);
char *get_value(struct class_info *info, int num);
void free_clas(struct class_info *info);
void sort_values(struct class_info *info);

bool init_class(struct class_info *info) {
	info->array = malloc(30*sizeof(char *));
	if (info->array) {
		info->size_array = 30;
		return true;
	}
	return false;
}

bool increase_array(struct class_info *info, char *value) {
	char **new_arr = malloc((info->size_array+20)*sizeof(char *));
	if (new_arr) {
		for (int i=0; i<info->size_array; i++) {
			*(new_arr+i) = *(info->array+i);
		}
		info->size_array = info->size_array + 20;
		free(info->array);
		info->array = new_arr;
		return add_val(info, value);
	}
	return false;
}

bool add_val(struct class_info *info, char *value) {
	if (info->curr_num<info->size_array) {
		int size = strlen(value);
		*(info->array+(info->curr_num)) = malloc(size+1);
		strcpy(*(info->array+(info->curr_num)), value);
		info->curr_num = info->curr_num + 1;
	} else {
		return increase_array(info, value);
	}
	return true;
}

void sort_values(struct class_info *info) {
	for (int i=0; i<info->curr_num-1; i++) {
		for (int j=i+1; j<info->curr_num; j++) {
			for (int k=0; k<strlen(*(info->array+i)) && k<strlen(*(info->array+j)); k++) {
				if ((int)toupper(*(*(info->array+i)+k))>(int)toupper(*(*(info->array+j)+k))) {
					char *arr = *(info->array+i);
					*(info->array+i) = *(info->array+j);
					*(info->array+j) = arr;
					break;
				} else if ((int)toupper(*(*(info->array+i)+k))<(int)toupper(*(*(info->array+j)+k))) {
					break;
				}
			}
		}
	}
}

int get_size(struct class_info *info) {
	return info->curr_num;
}

char *get_value(struct class_info *info, int num) {
	return *(info->array+num);
}

void free_clas(struct class_info *info) {
	for (int i=0; i<info->curr_num; i++) {
		free(*(info->array+i));
	}
}

void file_brouser(char *dname, int num) {
	DIR *directory;
	struct dirent *dstruct;
	struct stat dinfo;
	char path[200];

	if ((directory=opendir(dname))==NULL) {
		printf("Wrong with open directory!\n");
		return;
	}
	for (int i=0; i<num; i++)
		printf("   ");
	printf("%s/\n", dname);

	struct class_info *info = malloc(sizeof(struct class_info));
	if (!init_class(info)) {
		printf("Invalid initialisation class info!\n");
	}

	while ((dstruct=readdir(directory))!=NULL) {
		if (dstruct->d_name[0]=='.')
			continue;
		strcpy(path, dname);
		strcat(path, "/");
		strcat(path, dstruct->d_name);
		stat(path, &dinfo);
		if (S_ISDIR(dinfo.st_mode)) {
			add_val(info, path);
		}
	}
	closedir(directory);

	sort_values(info);
	for (int i=0; i<info->curr_num; i++) {
		file_brouser(get_value(info, i), num+1);
	}
}

int main(void) {
	char dname[] = ".";
	file_brouser(dname, 0);
}
