#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define file_name "prog_text.txt"

char *str_stream(int size) {
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

struct full_buf {
    char *buff;
    int size;
};

int main(void) {
    int fd, written, fbuf_l;
    struct full_buf *set_buffers = (struct full_buf *)malloc(100*sizeof(struct full_buf));
    char *buffer;
    fd = open(file_name, O_RDWR | O_APPEND);

    void *map_file;
    struct stat dinfo;

    stat(file_name, &dinfo);
    map_file = mmap(NULL, dinfo.st_size+1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (!map_file) {
        perror("Wrong init map_file!");
    }

    printf("\tWhen you write, information will add to buffer;\n");
    printf("\t- exit() -- stop program;\n");
    printf("\t- show() -- show data of file;\n");
    printf("\t- buff() -- show data of file;\n");
    printf("\t- save() -- save information in file;\n");
    fbuf_l = 0;
    while (1) {
        printf("Enter: ");
        buffer = str_stream(301);

        if (*(buffer+0)=='e'&&*(buffer+1)=='x'&&*(buffer+2)=='i'&&*(buffer+3)=='t'&&*(buffer+4)=='('&&*(buffer+5)==')') {
            break;
        } else if (*(buffer+0)=='s'&&*(buffer+1)=='h'&&*(buffer+2)=='o'&&*(buffer+3)=='w'&&*(buffer+4)=='('&&*(buffer+5)==')') {
            munmap(map_file, dinfo.st_size);
            stat(file_name, &dinfo);
            map_file = mmap(NULL, dinfo.st_size+1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
            if (!map_file) {
                perror("Wrong init map_file!");
            }

            printf("\tData of file:\n");
            char *cmap = (char *)map_file;
            printf("'''\n%s\n'''\n", cmap);
        } else if (*(buffer+0)=='b'&&*(buffer+1)=='u'&&*(buffer+2)=='f'&&*(buffer+3)=='f'&&*(buffer+4)=='('&&*(buffer+5)==')') {
            printf("\tData of buffer:\n");
            for (int i=0; i<fbuf_l; i++) {
                printf("l%d: %s\n", i+1, (set_buffers+i)->buff);
            }
        } else if (*(buffer+0)=='s'&&*(buffer+1)=='a'&&*(buffer+2)=='v'&&*(buffer+3)=='e'&&*(buffer+4)=='('&&*(buffer+5)==')') {
            printf("\tSaving...\n");
            for (int i=0; i<fbuf_l; i++) {
                written = write(fd, (set_buffers+i)->buff, (set_buffers+i)->size);
                written += write(fd, "\n", 1);
                free((set_buffers+i)->buff);
            }
            fbuf_l = 0;
        } else {
            (set_buffers+fbuf_l)->buff = (char *)malloc(strlen(buffer)*sizeof(char));
            (set_buffers+fbuf_l)->size = strlen(buffer);
            strcpy((set_buffers+fbuf_l)->buff, buffer);
            fbuf_l++;
        }
        free(buffer);
    }

    munmap(map_file, dinfo.st_size);
    free(set_buffers);
    // written = write(fd, )
}