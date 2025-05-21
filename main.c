#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include "./service/comando/comando.h"
#include "./config/termios/termios_config.h"
#include "./ui/ui.h"
#include "./service/gestor_agentes/gestor_agentes.h"
#include "time.h"
#define MAX_EVENTS 10
int cant_eventos = 0;
Comando comando;
char comando_print[128] = "";
GestorAgentes g;

void input_handler()
{
  ssize_t count;
  char buf[128];
  while ((count = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
  {
    // Iteramos sobre cada carácter leído
    for (ssize_t i = 0; i < count; i++)
    {
      if (buf[i] != '\n')
      {
        command_write_char(&comando, buf[i]);
      }
      else
      {
        cant_eventos = 0;
        command_reset(&comando);
      }
      command_copy_to_string(comando, comando_print);
      manage_console_content(&g, &comando);
    }
  }
  if (count == -1 && errno != EAGAIN)
  {
    perror("read STDIN");
  }
}

int main()
{
  srand(time(NULL));
  int nfds, epollfd;
  init_comando(&comando);

  // Configurar la terminal para lectura no canónica
  set_input_mode();

  // Configurar STDIN en modo no bloqueante
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (flags == -1)
  {
    perror("fcntl get STDIN_FILENO");
    exit(EXIT_FAILURE);
  }
  if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1)
  {
    perror("fcntl set O_NONBLOCK on STDIN_FILENO");
    exit(EXIT_FAILURE);
  }

  // Crear la instancia de epoll
  epollfd = epoll_create1(0);
  if (epollfd == -1)
  {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  // Preparar la estructura para registrar eventos
  struct epoll_event ev, events[MAX_EVENTS];

  // Agregar STDIN_FILENO con EPOLLET (edge-triggered) y no bloqueante
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = STDIN_FILENO;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1)
  {
    perror("epoll_ctl: STDIN_FILENO");
    exit(EXIT_FAILURE);
  }

  gestor_agentes_init(&g);
  gestor_agentes_generate(&g);

  //printf("Entro al bucle\n");
  // Bucle principal que espera y procesa los eventos
  while (1)
  {
    // 16ms ~ 60 fps
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, 16);
    if (nfds == -1)
    {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    // Si no hay eventos, realizamos tareas auxiliares
    if (nfds == 0)
    {
      //printf("Ejecutando console content\n");
      manage_console_content(&g, &comando);
      continue;
    }

    for (int n = 0; n < nfds; ++n)
    {
      if (events[n].data.fd == STDIN_FILENO)
      {
        input_handler();
      }
    }
  }

  close(epollfd);
  return 0;
}
