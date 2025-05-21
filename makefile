# Definir el compilador
CC = gcc

# Definir las banderas del compilador
CFLAGS = -Wall -Wextra

# Buscar todos los archivos .c en la carpeta raíz y sus subdirectorios
SRCS = $(shell find . -name "*.c")

# Generar los nombres de los archivos objeto correspondientes
OBJS = $(SRCS:.c=.o)

# Definir el nombre del ejecutable
EXEC = programa

# Regla para compilar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar los archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos compilados
clean:
	rm -f $(OBJS)

# Regla para limpiar todos los archivos generados
distclean: clean
	rm -f *~ */*~

# Regla para ejecutar el programa
run: $(EXEC)
	rm -f $(OBJS)
	./$(EXEC)

# Regla por defecto
.PHONY: all
all: $(EXEC)
