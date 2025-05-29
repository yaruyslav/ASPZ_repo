#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct lines_arr {
	char *lines;
	struct lines_arr *next;
};

struct line_arr {
	char line[51];
	struct line_arr *next;
};

void cat_lines(char *to, char *from, int to_num) {
	int i, j;
	i = to_num;
	for (j=0; j<50; i++, j++) {
		to[i] = from[j];
		if (from[j]=='\n') {
			to[i+1] = '\0';
			return;
		}
	}
}

int main(int argc, char **argv) {
	char f_name[] = "text.txt";
	FILE *file = fopen(f_name, "r");

	struct line_arr *line = NULL;
	struct lines_arr *lines = NULL;
	struct lines_arr *lower_lines = NULL;

	char curr_line[51];
	while (fgets(curr_line, 51, file)) {
		if (line==NULL) {
			line = malloc(sizeof(struct line_arr));
			strcpy(line->line, curr_line);
			line->next = NULL;
		} else {
			struct line_arr *curr_branch = line;
			while (curr_branch->next!=NULL) {
				curr_branch = curr_branch->next;
			}
			curr_branch->next = malloc(sizeof(struct line_arr));
			curr_branch = curr_branch->next;
			strcpy(curr_branch->line, curr_line);
			curr_branch->next = NULL;
		}

		for (int i=0; i<51; i++) {
			if (curr_line[i]=='\n') {
				struct lines_arr *curr_branch1;
				struct lines_arr *curr_branch_l;
				if (lines==NULL) {
					lines = malloc(sizeof(struct lines_arr));
					lines->next = NULL;
					curr_branch1 = lines;
					lower_lines = malloc(sizeof(struct lines_arr));
					lower_lines->next = NULL;
					curr_branch_l = lower_lines;
				} else {
					curr_branch1 = lines;
					curr_branch_l = lower_lines;
					while (curr_branch1->next!=NULL) {
						curr_branch1 = curr_branch1->next;
						curr_branch_l = curr_branch_l->next;
					}
					curr_branch1->next = malloc(sizeof(struct lines_arr));
					curr_branch1 = curr_branch1->next;
					curr_branch1->next = NULL;

					curr_branch_l->next = malloc(sizeof(struct lines_arr));
					curr_branch_l = curr_branch_l->next;
					curr_branch_l->next = NULL;
				}

				struct line_arr *curr_branch2 = line;
				int size;
				for (size=0; curr_branch2; size++) {
					curr_branch2 = curr_branch2->next;
				}

				curr_branch2 = line;
				char *all_line = malloc((size*50*sizeof(char))+1);
				for (int j=0; j<size; j++) {
					cat_lines(all_line, line->line, 50*j);
					line = line->next;
				}
				curr_branch1->lines = all_line;

				char *all_line_l = malloc((size*50*sizeof(char))+1);
				for (int j=0; j<(int)((size*50*sizeof(char))+1); j++) {
					*(all_line_l+j) = tolower(*(all_line+j));
				}
				curr_branch_l->lines = all_line_l;

				curr_branch2 = line;
				while (curr_branch2!=NULL) {
					struct line_arr *curr_branch3 = curr_branch2;
					curr_branch2 = curr_branch2->next;
					free(curr_branch3);
				}
			}
		}
	}

	struct lines_arr *curr_branch, *curr_branch_l;
	curr_branch = lines;
	printf("\n\t>>> All text <<<\n");
	while (curr_branch) {
		printf("%s", curr_branch->lines);
		curr_branch = curr_branch->next;
	}

	curr_branch = lines;
	curr_branch_l = lower_lines;
	if (*(argv+1)==NULL) {
		printf("\n\t>>> Programm don't have no word <<<\n");
	} else {
		printf("\n\t>>> All text with word '%s' <<<\n", *(argv+1));
		while (curr_branch) {
			if (*(argv+1)==NULL) {
				printf("%s", curr_branch->lines);
			} else {
				if (strstr(curr_branch_l->lines, *(argv+1))) {
					printf("%s\n", curr_branch->lines);
				}
			}
			curr_branch = curr_branch->next;
			curr_branch_l = curr_branch_l->next;
		}
	}
	
	fclose(file);
}