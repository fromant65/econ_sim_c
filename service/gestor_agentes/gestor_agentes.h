#ifndef GESTOR_AGENTES_H
#define GESTOR_AGENTES_H
#include "../agente/agente.h"

#define DEFAULT_GESTOR_SIZE 1024

typedef struct{
  Agente* agentes;
  int cant_agentes, size;
}GestorAgentes;

void gestor_agentes_init(GestorAgentes* g);
void gestor_agentes_generate(GestorAgentes* g);
void gestor_agentes_intercambio_aleatorio(GestorAgentes* g);
void gestor_agentes_intercambio(Agente* a, Agente* b);
Agente* gestor_agentes_get_agente_con_mas_intercambios(GestorAgentes* g);

#endif