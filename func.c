#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void replace(const char* file_name, const char* old_text, const char* new_text) {
    FILE* file_r = fopen(file_name, "r");
    FILE* file_w = fopen("temp.txt", "w");
    char line[1024];
    char buffer[1024];

    if (!file_r || !file_w) {
        perror("Error: cant't open file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file_r)) {
        char* pos = NULL;
        buffer[0] = '\0';

        while ((pos = strstr(line, old_text))) {
            *pos = '\0';
            strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
            strncat(buffer, new_text, sizeof(buffer) - strlen(buffer) - 1);
            strncpy(line, pos + strlen(old_text), sizeof(line) - 1);
        }

        strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
        fprintf(file_w, "%s", buffer);
    }

    fclose(file_r);
    fclose(file_w);

    if (rename("file_w.txt", file_name) != 0) {
        perror("Error: can't rename file");
        exit(EXIT_FAILURE);
    }
}

void add(const char* file_name, const char* text, const char* position) {
    FILE* file_r = fopen(file_name, "r");
    FILE* file_w = fopen("temp.txt", "w");
    char line[1024];

    if (!file_r || !file_w) {
        perror("Error: can't open file");
        exit(EXIT_FAILURE);
    }

    if (strcmp(position, "-I") == 0) {
        fprintf(file_w, "%s\n", text);
    }

    while (fgets(line, sizeof(line), file_r)) {
        fprintf(file_w, "%s", line);
    }

     if (strcmp(position, "-b") == 0) {
        fprintf(file_w, "%s\n", text);
    }

    fclose(file_r);
    fclose(file_w);

    if (rename("file_w.txt", file_name) != 0) {
        perror("Error: can't rename file");
        exit(EXIT_FAILURE);
    }
}

void delete(const char* file_name, const char* delete_text) {
    FILE* file_r = fopen(file_name, "r");
    FILE* file_w = fopen("file_w.txt", "w");
    char line[1024];

    if (!file_r || !file_w) {
        perror("Error: can't open file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file_r)) {
        if (!strstr(line, delete_text)) {
            fprintf(file_w, "%s", line);
        }
    }

    fclose(file_r);
    fclose(file_w);

    if (rename("file_w.txt", file_name) != 0) {
        perror("Error: can't rename file");
        exit(EXIT_FAILURE);
    }
}



