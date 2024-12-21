#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void print_comands() {
	printf("Error!\n");
	printf("./sed_simplified input.txt -r 'old text' 'new text'\n");
	printf("./sed_simplified input.txt -d 'text to delete'\n");
	printf("./sed_simplified input.txt -i -I 'text' (add text to first)\n");
	printf("./sed_simplified input.txt -i -b 'text' (add test to last)\n");
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		print_comands();
		return 1;
	}

	char* file_name = argv[1];
	char* position = NULL;

	if (argc == 5) {
		position = argv[3];
	}

	if (strcmp(argv[2], "-r") == 0 && argc == 5) {
		replace_text(file_name, argv[3], argv[4]);
	} else if (strcmp(argv[2], "-d") == 0 && argc == 4) {
		delete(file_name, argv[3]);
	} else if (strcmp(argv[2], "-i") == 0 && argc == 5) {
		add(file_name, argv[4], argv[3]);
	} else {
		print_comands();
		return 1;
	}

	return 0;
}
