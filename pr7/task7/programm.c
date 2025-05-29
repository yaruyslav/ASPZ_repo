#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

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

int main() {
	DIR *dir;
	struct dirent *dstruct;
	struct stat dinfo;

	dir = opendir(".");
	if (!dir) {
		perror("Could not open directory!\n");
		return 1;
	}

	printf("List of your executable files:\n");

	char *executables[100];
	int count;

	count = 0;
	while ((dstruct = readdir(dir)) != NULL) {
		if (stat(dstruct->d_name, &dinfo) == 0) {
			if (S_ISREG(dinfo.st_mode) && (dinfo.st_mode & S_IXUSR)) {
				executables[count++] = strdup(dstruct->d_name);
				printf("%d: %s\n", count, dstruct->d_name);
			}
		}
	}
	closedir(dir);

	if (count == 0) {
		printf("Executable files doesn't exist!\n");
		return 0;
	}

	for (int i = 0; i < count; i++) {
		char *answer;
		printf("Allow others to read '%s'? (y/n): ", executables[i]);
		answer = get_stdin(1);
		if (tolower(*answer) == 'y') {
			if (chmod(executables[i], dinfo.st_mode | S_IROTH) == 0) {
				printf("Permission granded!\n");
			} else {
				perror("Permission not granded!\n");
			}
		}
		free(answer);
		free(executables[i]);
	}

	return 0;
}