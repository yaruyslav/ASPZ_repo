#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    fd = open("prog_task.txt", O_WRONLY | O_TRUNC);
    if (fd < 0) {
        printf("Can't open file!\n");
        return 0;
    }

    char arr[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    int wr_num = write(fd, arr, sizeof(arr)/sizeof(arr[0]));
    printf("Written symbols: %d\n", wr_num);

    close(fd);
    fd = -1;

    fd = open("prog_task.txt", O_RDONLY);
    if (fd < 0) {
        printf("Can't open file!\n");
        return 0;
    }

    char buffer[100];
	lseek(fd, 3, SEEK_SET);
    int num = read(fd, &buffer, 4);
    buffer[num] = '\0';

    printf("Readed bytes in char type: '%s'\n", buffer);
    printf("Readed bytes in decimal:");
	for (int i=0; i<num; i++) {
		printf(" '%d'", (char)buffer[i]);
	}
    putchar('\n');

    close(fd);
    return 0;
}