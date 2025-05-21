#include "agente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

inline int max(int a, int b){return a>b?a:b;}

void agente_init(Agente* a, int id){
  assert(a!=NULL);
  a->cant_intercambios = 0;
  String* str = malloc(sizeof(String));
  string_init(str);
  a->data = str;
  a->id = id;
}

void agente_send_msg(Agente* receiver, String* msg){
  assert(receiver!=NULL && msg!=NULL);
  string_copy_to(msg, receiver->data);
}

String *agente_get_data(Agente* a){
  assert(a!=NULL);
  return a->data;
}

char* agente_get_stats(Agente* a){
  assert(a!=NULL);
  assert(a->data!=NULL);
  char* buff = malloc(sizeof(char)*(a->data->size + 128));
  snprintf(buff, sizeof(char)*(a->data->size + 128), "Id: %d\nCantidad de intercambios: %d\nData: %s\n", a->id, a->cant_intercambios, a->data->buff);
  return buff;
}