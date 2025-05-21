#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>

void set_input_mode(void)
{
  struct termios tattr;

  // Obtén los atributos actuales
  if (tcgetattr(STDIN_FILENO, &tattr) == -1)
  {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  // Desactiva el modo canónico y el eco
  tattr.c_lflag &= ~(ICANON | ECHO);
  // Configura el mínimo número de caracteres para leer
  tattr.c_cc[VMIN] = 1;
  // Configura el timeout (0, en este caso, espera indefinidamente hasta un caracter)
  tattr.c_cc[VTIME] = 0;

  if (tcsetattr(STDIN_FILENO, TCSANOW, &tattr) == -1)
  {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }
}