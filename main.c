#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void print_comands() {
	printf("Ошибка!\n");
	printf("./sed_simplified input.txt -r 'old text' 'new text'\n");
	printf("./sed_simplified input.txt -d 'text to delete'\n");
	printf("./sed_simplified input.txt -i -I 'text' (добавить текст в начало файла)\n");
	printf("./sed_simplified input.txt -i -b 'text' (добавить текст в конец файла)\n");
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

	return 0;
}
