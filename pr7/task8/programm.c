#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

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

char *stream_val(int size) {
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
	char name_dir[] = ".";
	DIR *directory;
	struct dirent *dstruct;
	struct stat dinfo;
	char path[200];

	struct class_info *info = malloc(sizeof(struct class_info));
	if (!init_class(info)) {
		perror("Invalid initialisation class info!\n");
	}

	if ((directory=opendir(name_dir))==NULL) {
		perror("Wrong open directory!\n");
	}
	printf("Files in this derctory:\n");
	for (int i=1; (dstruct=readdir(directory))!=NULL; i++) {
		if (dstruct->d_name[0]=='.') {
			i--;
			continue;
		}
		strcpy(path, name_dir);
		strcat(path, "/");
		strcat(path, dstruct->d_name);
		stat(path, &dinfo);
		if (!S_ISDIR(dinfo.st_mode)) {
			printf("%d.  %s\n", i, dstruct->d_name);
			add_val(info, dstruct->d_name);
		}
	}
	closedir(directory);

	char *ch;
	printf("You want to delete any files? (y/n): ");
	ch = stream_val(1);
	if (tolower(ch[0])!='y')
		return 0;

	printf("\tMax number is 9999!\n\tEnter 0 to exit;\n\tEnter any number to delete file;\n\tEnter 'all' to delete all files;\n");
	while (1) {
		printf("Enter num of file: ");
		ch = stream_val(4);
		if (!ch) {
			printf("Wrong initialising choice!\n");
			continue;
		}

		int choi_num = atoi(ch);
		if (!strcmp(ch, "0")) {
			free(ch);
			break;
		} else if (!strcmp(ch, "all")) {
			printf("Are you sure? (y/n): ");
			free(ch);
			ch = stream_val(1);
			if (tolower(ch[0])!='y')
				continue;
			for (int i=0; i<get_size(info); i++) {
				remove(get_value(info, i-1));
			}
			printf(">> You deleted all files! <<\n");
			free(ch);
			break;
		} else if (choi_num==0) {
			printf("Unknown command '%s'!\n", ch);
		} else if (choi_num>0 && choi_num<=get_size(info)) {
			printf("Are you sure? (y/n): ");
			free(ch);
			ch = stream_val(1);
			if (tolower(ch[0])!='y')
				continue;
			for (int i=1; i<=get_size(info); i++) {
				if (i==choi_num) {
					remove(get_value(info, i-1));
					printf(">> File %s is deleted! <<\n", get_value(info, i-1));
				}
			}
		} else {
			printf("File with number '%d' does'n exist!\n", choi_num);
		}
		free(ch);
	}
	printf("Closing programm...\n");
}