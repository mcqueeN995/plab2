#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_text(const char* filename, const char* old_text, const char* new_text) {
    FILE* file = fopen(filename, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Error opening file");
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

    if (rename("temp.txt", filename) != 0) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}