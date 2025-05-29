#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void search_erro1(char *path, mode_t info, char *name) {
	int check;
	check = 0;
	printf("%s: ", path);
	if (!(info&S_IRUSR) && (info&S_IXUSR)) {
		printf("Suspicious file for owner");
		check = 1;
	}
	if (!(info&S_IRGRP) && (info&S_IXGRP)) {
		if (check==1)
			printf(", group");
		else {
			printf("Suspicious file for group");
			check = 1;
		}
	}
	if (!(info&S_IROTH) && (info&S_IXOTH)) {
		if (check==1)
			printf(", others");
		else {
			printf("Suspicious file for owner");
			check = 1;
		}
	}
	if (check==1) {
		printf(" '%s'!\n", name);
	} else {
		printf("File is normal!\n");
	}
}

int main(void) {
	char name_dir[] = ".";
	DIR *directory;
	struct dirent *dstruct;
	struct stat dinfo;
	char path[200];

	directory = opendir(name_dir);

	while ((dstruct=readdir(directory))!=NULL) {
		if (dstruct->d_name[0]=='.')
			continue;

		strcpy(path, name_dir);
		strcat(path, "/");
		strcat(path, dstruct->d_name);

		stat(path, &dinfo);
		if (S_ISREG(dinfo.st_mode)&&((dinfo.st_mode & S_IXUSR)||(dinfo.st_mode & S_IXGRP)||(dinfo.st_mode & S_IXOTH))) {
			search_erro1(path, dinfo.st_mode, "only executable");
		}
	}

	closedir(directory);
}
