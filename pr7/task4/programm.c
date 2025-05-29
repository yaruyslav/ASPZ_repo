#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int num_stop;
int num_line;

void like_more(char *line) {
	if ((num_line+1)==num_stop) {
		printf("%s", line);
	} else
		printf("%s\n", line);
	num_line++;
	if (num_line==num_stop) {
		num_line = 0;
		char buf;
		scanf("%c", &buf);
	}
	return;
}

void init_counter() {
	num_line = 0;
	num_stop = 1;
	like_more("Enter 'Enter' to continue:");
	num_stop = 20;
}

int main(void) {
	char name_dir[] = ".";
	DIR *directory;
	struct dirent *dstruct;
	struct stat dinfo;
	char path[200];

	init_counter();

	if ((directory=opendir(name_dir))==NULL) {
		perror("Wrong open directory!\n");
	}
	while ((dstruct=readdir(directory))!=NULL) {
		if (dstruct->d_name[0]=='.')
			continue;
		strcpy(path, name_dir);
		strcat(path, "/");
		strcat(path, dstruct->d_name);
		stat(path, &dinfo);
		if (!S_ISDIR(dinfo.st_mode)) {
			like_more(path);
		}
	}
}