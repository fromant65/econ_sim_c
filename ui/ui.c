#include <stdio.h>
#include <stdlib.h>
#include "../service/agente/agente.h"
#include "ui.h"
#include <assert.h>
void print_data(char *data_print, char* comando)
{
  system("clear");
  printf("%s\nComando: %s\n", data_print, comando);
}

void manage_console_content(GestorAgentes *g, Comando* c)
{
  assert(g!=NULL);
  //printf("Primero: intercambio aleatorio\n");
  gestor_agentes_intercambio_aleatorio(g);
  //printf("Segundo: get stats\n");
  char *stats = agente_get_stats(gestor_agentes_get_agente_con_mas_intercambios(g));
  assert(stats!=NULL);
  print_data(stats, c->comando);
  free(stats);
}