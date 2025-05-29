#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void file_counter(char *dname, int sizegap) {
	DIR *directory;
	struct dirent *dstruct;
	struct stat dinfo;
	char path[200];
	int counter;

	counter = 0;
	if ((directory=opendir(dname))==NULL) {
		printf("Wrong with open directory!\n");
		return;
	}
	while ((dstruct=readdir(directory))!=NULL) {
		if (dstruct->d_name[0]!='.') {
			strcpy(path, dname);
			strcat(path, "/");
			strcat(path, dstruct->d_name);
			stat(path, &dinfo);
			if (S_ISDIR(dinfo.st_mode)==0) {
				counter++;
			}
		}
	}
	closedir(directory);

	if ((directory=opendir(dname))==NULL) {
		printf("Wrong with open directory!\n");
		return;
	} else {
		for (int i=0; i<sizegap; i++)
			printf("   ");
		printf("Files %d in '%s/'\n", counter, dname);
	}
	while ((dstruct=readdir(directory))!=NULL) {
		if (dstruct->d_name[0]!='.') {
			strcpy(path, dname);
			strcat(path, "/");
			strcat(path, dstruct->d_name);
			stat(path, &dinfo);
			if (S_ISDIR(dinfo.st_mode)) {
				file_counter(path, sizegap+1);
			}
		}
	}
	closedir(directory);
}

int main(void) {
	char dname[] = ".";
	file_counter(dname, 0);
}