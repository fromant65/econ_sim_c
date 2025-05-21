#include "comando.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
void init_comando(Comando *c)
{
  assert(c!=NULL);
  c->size = 128;
  c->i = 0;
  c->comando = malloc(sizeof(char) * c->size + 1);
}

void command_write_char(Comando *str, char c)
{
  assert(str!=NULL);
  assert(str->comando!=NULL);
  if (str->i >= str->size)
    return;
  str->comando[str->i] = c;
  str->comando[str->i + 1] = '\0';
  str->i++;
}

void command_reset(Comando *str)
{
  assert(str!=NULL);
  assert(str->comando!=NULL);
  char null = 0;
  memcpy(str->comando, &null, str->size);
  //str->comando[0] = '\0';
  str->i = 0;
}

void command_copy_to_string(Comando com, char *string)
{
  assert(string!=NULL);
  strncpy(string, com.comando, com.i+1);
}