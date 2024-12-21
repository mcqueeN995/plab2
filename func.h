#ifndef TEXT_O_H
#define TEXT_O_H

void replace(const char *filename, const char *old_text,const char* new_text);
void delete(const char *filename, const char *pattern);
void add(const char *filename, const char *text, const char *position);
#endif
