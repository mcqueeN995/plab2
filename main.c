#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void print_comands() {
	printf("Error!\n");
	printf("./sed_simplified input.txt -r 'old text' 'new text'\n");
	printf("./sed_simplified input.txt -d 'text to delete'\n");
	printf("./sed_simplified input.txt -i -I 'text' (add text to first element file)\n");
	printf("./sed_simplified input.txt -i -b 'text' (add text like last elemnt file)\n");
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		print_comands();
		return 1;
	}

	char* filename = argv[1];
	char* position = NULL;

	if (argc == 5) {
		position = argv[3];
	}

	if (strcmp(argv[2], "-r") == 0 && argc == 5) {
		replace(filename, argv[3], argv[4]);
	} else if (strcmp(argv[2], "-d") == 0 && argc == 4) {
		delete(filename, argv[3]);
	} else if (strcmp(argv[2], "-i") == 0 && argc == 5) {
		add(filename, argv[4], argv[3]);
	} else {
		print_comands();
		return 1;
	}

	return 0;
}
