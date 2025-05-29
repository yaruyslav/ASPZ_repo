#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void choice(int type, mode_t mode1, mode_t mode2, int end) {
	int endle;
	if (type==1) {
		if (mode1 & mode2)
			printf("can read"), endle = 1;
		else
			printf("can't read"), endle = 2;
	} else if (type==2) {
		if (mode1 & mode2)
			printf("can write"), endle = 1;
		else
			printf("can't write"), endle = 2;
	} else if (type==3) {
		if (mode1 & mode2)
			printf("can execute"), endle = 1;
		else
			printf("can't execute"), endle = 2;
	}
	if (end==1) {
		if (endle==1)
			printf(",   ");
		else if (endle==2)
			printf(", ");
	} else if (end==2) {
		printf("\n");
	}
}

void permitions(mode_t mode) {
	printf("Owner:  ");
	choice(1, mode, S_IRUSR, 1);
	choice(2, mode, S_IWUSR, 1);
	choice(3, mode, S_IXUSR, 2);
	printf("Group:  ");
	choice(1, mode, S_IRGRP, 1);
	choice(2, mode, S_IWGRP, 1);
	choice(3, mode, S_IXGRP, 2);
	printf("Others: ");
	choice(1, mode, S_IROTH, 1);
	choice(2, mode, S_IWOTH, 1);
	choice(3, mode, S_IXOTH, 2);
}

int main(void) {
	char name_dir[] = ".";
	DIR *directory;
	struct dirent *fstruct;
	struct stat finfo;
	char path[200];
	if ((directory=opendir(name_dir))==NULL) {
		perror("Wrong open directory!\n");
	}
	while ((fstruct=readdir(directory))!=NULL) {
		if (fstruct->d_name[0]=='.') {
			continue;
		}
		strcpy(path, name_dir);
        strcat(path, "/");
        strcat(path, fstruct->d_name);
		stat(path, &finfo);

		printf("\t%s:\n", fstruct->d_name);
		permitions(finfo.st_mode);
	}
}