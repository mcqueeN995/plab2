#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void replace(const char* file_name, const char* old_text, const char* new_text) {
    FILE* file = fopen(file_name, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("ErrorL can't open file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    char buffer[1024];
    while (fgets(line, sizeof(line), file)) {
        char* pos = NULL;
        buffer[0] = '\0';

        while ((pos = strstr(line, old_text))) {
            *pos = '\0';
            strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
            strncat(buffer, new_text, sizeof(buffer) - strlen(buffer) - 1);
            strncpy(line, pos + strlen(old_text), sizeof(line) - 1);
        }

        strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
        fprintf(temp, "%s", buffer);
    }

    fclose(file);
    fclose(temp);

    if (rename("temp.txt", file_name) != 0) {
        perror("Error: can't rename file");
        exit(EXIT_FAILURE);
    }
}

void delete(const char* file_name, const char* pattern) {
    FILE* file = fopen(file_name, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Error: can't openfile");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (!strstr(line, pattern)) {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    if (rename("temp.txt", file_name) != 0) {
        perror("Error: can't rename file");
        exit(EXIT_FAILURE);
    }
}

void add(const char* file_name, const char* text, const char* position) {
    FILE* file = fopen(file_name, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Error: can't open file");
        exit(EXIT_FAILURE);
    }

    char line[1024];

    if (strcmp(position, "-I") == 0) {
        fprintf(temp, "%s\n", text);
    }

    while (fgets(line, sizeof(line), file)) {
        fprintf(temp, "%s", line);
    }

    if (strcmp(position, "-b") == 0) {
        fprintf(temp, "%s\n", text);
    }

    fclose(file);
    fclose(temp);

    if (rename("temp.txt", file_name) != 0) {
        perror("Error: can't file");
        exit(EXIT_FAILURE);
    }
}
