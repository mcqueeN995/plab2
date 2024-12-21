#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* dalete(char *array, char ch) {
    int i, j = 0;
    int length = strlen(array);

    for (i = 0; i < length; i++) {
        if (array[i] != ch) {
            array[j++] = array[i];
        }
    }

    array[j] = '\0';
    return array;
}