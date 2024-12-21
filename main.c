#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

// Функция для замены текста в строке
void replace_text(char *line, const char *old_text, const char *new_text) {
    char *pos;
    int old_len = strlen(old_text);
    int new_len = strlen(new_text);
    char *result = (char *)malloc(strlen(line) + 1);  // Буфер для новой строки
    char *res_ptr = result;

    while ((pos = strstr(line, old_text)) != NULL) {
        // Копируем все до найденного вхождения
        strncpy(res_ptr, line, pos - line);
        res_ptr += pos - line;
        // Добавляем новый текст
        strcpy(res_ptr, new_text);
        res_ptr += new_len;
        line = pos + old_len;
    }
    // Копируем остаток строки
    strcpy(res_ptr, line);
    strcpy(line, result);
    free(result);
}

// Функция для удаления строк, содержащих указанный текст
void delete_matching_lines(FILE *input, FILE *output, const char *text_to_delete) {
    char *line = (char *)malloc(INITIAL_BUFFER_SIZE);
    size_t buffer_size = INITIAL_BUFFER_SIZE;
    while (getline(&line, &buffer_size, input) != -1) {
        if (strstr(line, text_to_delete) == NULL) {
            fputs(line, output);  // Печатаем строку, если она не содержит текста для удаления
        }
    }
    free(line);
}

// Функция для вставки текста в начало или конец строки
void insert_text(FILE *input, FILE *output, const char *text, int at_start) {
    char *line = (char *)malloc(INITIAL_BUFFER_SIZE);
    size_t buffer_size = INITIAL_BUFFER_SIZE;
    while (getline(&line, &buffer_size, input) != -1) {
        if (at_start) {
            fprintf(output, "%s%s", text, line);  // Вставляем текст в начало
        } else {
            line[strcspn(line, "\n")] = 0;  // Убираем символ новой строки
            fprintf(output, "%s%s\n", line, text);  // Вставляем текст в конец
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./sed_simplified <input_file> <option> [args...]\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    // Обрабатываем различные опции командной строки
    if (strcmp(argv[2], "-r") == 0 && argc == 5) {
        // Замена текста
        char *line = (char *)malloc(INITIAL_BUFFER_SIZE);
        size_t buffer_size = INITIAL_BUFFER_SIZE;
        while (getline(&line, &buffer_size, input) != -1) {
            replace_text(line, argv[3], argv[4]);
            fputs(line, stdout);
        }
        free(line);
    } else if (strcmp(argv[2], "-d") == 0 && argc == 4) {
        // Удаление строк, содержащих заданный текст
        delete_matching_lines(input, stdout, argv[3]);
    } else if (strcmp(argv[2], "-i") == 0 && argc == 5 && strcmp(argv[3], "-f") == 0) {
        // Вставка текста в начало строки
        insert_text(input, stdout, argv[4], 1);
    } else if (strcmp(argv[2], "-i") == 0 && argc == 5 && strcmp(argv[3], "-b") == 0) {
        // Вставка текста в конец строки
        insert_text(input, stdout, argv[4], 0);
    } else {
        fprintf(stderr, "Invalid arguments\n");
        fclose(input);
        return 1;
    }

    fclose(input);
    return 0;
}
