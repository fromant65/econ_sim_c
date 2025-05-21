#include "string_custom.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
void string_init(String* s){
  assert(s!=NULL);
  s->size = DEFAULT_STR_SIZE;
  s->buff = malloc(sizeof(char)*DEFAULT_STR_SIZE);
  s->buff[0] = '\0';
  s->len = 0;
}

int string_length(String s){
  return s.len;
}

void string_copy_to(String* origin, String* dest){
  assert(origin!=NULL && dest!=NULL );
  assert( origin->buff!=NULL && dest->buff!=NULL);
  int origin_len = string_length(*origin);
  if(dest->size < origin_len){
    string_expand_size(dest, origin_len+1);
  }
  strcpy(dest->buff, origin->buff);
}

void string_copy_from(String* dest, char* origin){
  assert(dest!=NULL &&origin!=NULL);
  assert(dest->buff!=NULL);
  strcpy(dest->buff, origin);
}

void string_expand_size(String* s, int new_size){
  s->buff = realloc(s->buff, sizeof(char)*new_size);
  s->size = new_size;
  assert(s->buff!=NULL);
}

void string_free(String* s){
  free(s->buff);
  free(s);
}