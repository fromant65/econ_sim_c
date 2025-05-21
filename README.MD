# Comandos No Bloqueantes en C

Este proyecto implementa un mecanismo de flujo de comandos para aplicaciones de terminal en C. Permite que el usuario proporcione entrada de forma no bloqueante mientras el programa se ejecuta, mostrando en tiempo real el comando a medida que se escribe.

## Características

- **Entrada No Bloqueante:** Procesa los caracteres individualmente a medida que se presionan, evitando bloqueos en la ejecución.
- **Visualización en Tiempo Real:** Muestra el comando en formación mientras se introduce.
- **Optimizado para Linux:** Diseñado y probado para distribuciones Linux.

## Cómo Compilar

Para compilar el proyecto, asegúrate de contar con un compilador compatible (por ejemplo, GCC). En el directorio raíz del proyecto, ejecuta el siguiente comando:

```bash
make
```
Esto generará un ejecutable llamado `programa`.

Si deseas limpiar los archivos objeto generados durante la compilación, ejecuta:

```bash
make clean
```

## Cómo Ejecutar

Ubícate en el mismo directorio donde se compiló el proyecto y ejecuta en una terminal:

```bash
./programa
```

## Aclaraciones

- **Sistema Operativo:** Este programa ha sido desarrollado y probado en distribuciones Linux. No se garantiza su funcionamiento en otros sistemas operativos.
- **Configuración de la Terminal:** Para lograr que se procese cada tecla sin esperar al ENTER, el programa desactiva el modo canónico. Asegúrate de que la terminal utilizada soporte estas modificaciones.

## Contribuciones

Si deseas contribuir con mejoras o sugerir cambios, siéntete libre de enviar un pull request o abrir un issue en el repositorio.
