#ifndef STRING_CUSTOM_H
#define STRING_CUSTOM_H

#define DEFAULT_STR_SIZE 1024

typedef struct{
  char* buff;
  int size, len;
}String;

void string_init(String* s);
int string_length(String s);
void string_copy_to(String* origin, String* dest);
void string_copy_from(String* dest, char* origin);
void string_expand_size(String* s, int new_size);
void string_free(String* s);
#endif