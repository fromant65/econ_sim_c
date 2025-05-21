#include "gestor_agentes.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void gestor_agentes_init(GestorAgentes* g){
  assert(g!=NULL);
  g->agentes = malloc(sizeof(Agente)*DEFAULT_GESTOR_SIZE);
  g->cant_agentes=0;
  g->size=DEFAULT_GESTOR_SIZE;
}

void gestor_agentes_generate(GestorAgentes* g){
  assert(g!=NULL);
  assert(g->agentes!=NULL);
  for(int i=0; i<g->size;i++){
    agente_init(&g->agentes[i],i);
    g->cant_agentes++;
  }
}

void gestor_agentes_intercambio_aleatorio(GestorAgentes* g){
  assert(g!=NULL);
  assert(g->agentes!=NULL);
  //printf("Primero calculamos los indices. Cant agentes: %d\n", g->cant_agentes);
  int a=rand()%g->cant_agentes, b=rand()%g->cant_agentes;
  //printf("Despues chequeamos si son iguales\n");
  if(a==b){
    //printf("Eran iguales, va de vuelta: %d, %d\n", a, b);
    return gestor_agentes_intercambio_aleatorio(g);
  }
  //printf("Si no son iguales, intercambiamos\n");
  gestor_agentes_intercambio(&g->agentes[a], &g->agentes[b]);
}

void gestor_agentes_intercambio(Agente* a, Agente* b){
  assert(a!=NULL && b!=NULL);
  //envia mensaje a
  agente_send_msg(b,a->data);
  //envia mensaje b
  agente_send_msg(a, b->data);
  a->cant_intercambios++;
  b->cant_intercambios++;
}

Agente* gestor_agentes_get_agente_con_mas_intercambios(GestorAgentes* g){
  assert(g!=NULL);
  assert(g->agentes!=NULL);
  int max_id = 0;
  for(int i=1; i<g->cant_agentes; i++){
    if(g->agentes[i].cant_intercambios>g->agentes[i-1].cant_intercambios){
      max_id = i;
    }
  }
  return &g->agentes[max_id];
}