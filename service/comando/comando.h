
#ifndef COMANDO_H
#define COMANDO_H
typedef struct
{
  int size, i;
  char *comando;
} Comando;
void init_comando(Comando *c);
void command_write_char(Comando *str, char c);
void command_reset(Comando *str);
void command_copy_to_string(Comando com, char *string);
#endif 