#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *file_in;
	FILE *file_out = fopen("prog_out.txt", "w");
	char line[128];

	file_in = popen("who", "r");
	while (fgets(line, 128, file_in)) {
		fprintf(file_out, "%s", line);
	}
	fclose(file_out);
	pclose(file_in);

	printf("<<< Pipe open now write in shell! >>>\n");
	file_in = popen("more prog_out.txt", "w");
	pclose(file_in);
}