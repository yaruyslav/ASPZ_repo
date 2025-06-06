#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	int fd = open("./prog_task.txt", O_WRONLY | O_TRUNC);

	size_t nbytes = 10000;
	char *buffer = (char *)malloc(nbytes*sizeof(char)+1);
	int i;
	for (i=0; i<nbytes; i++) {
		*(buffer+i) = i%26 + 65;
	}
	*(buffer+i) = '\0';

	int wr_num = write(fd, buffer, nbytes);
 	printf("buffer: ");
	for (i=0; i<nbytes; i++) {
		if (i<65)
			printf("%c", *(buffer+i));
		else {
			printf("...\n");
			break;
		}
	}
	printf("nbytes:     %d\n", (int)nbytes);
	printf("num writed: %d\n", wr_num);
}