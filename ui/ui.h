#ifndef UI_H
#define UI_H
#include "../service/gestor_agentes/gestor_agentes.h"
#include "../service/comando/comando.h"
void print_data(char* data_print, char* comando);
void manage_console_content(GestorAgentes* g, Comando* c);
#endif