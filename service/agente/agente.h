#ifndef AGENTE_H
#define AGENTE_H
#define MAX_DATA_SIZE 1024
#include "../string/string_custom.h"
typedef struct{
  int id, cant_intercambios;
  String* data;
}Agente;

void agente_init(Agente* a, int id);
void agente_send_msg(Agente* receiver, String* msg);
String* agente_get_data(Agente* a);
char* agente_get_stats(Agente* a);
#endif