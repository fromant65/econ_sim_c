# Econ Sim: Simulador de Modelos Económicos y Mercados

## 📅 Índice

1. [Resumen del Proyecto](#1-resumen-del-proyecto)
2. [Modelos de la Simulación](#2-modelos-de-la-simulación)

   * [2.1 POP](#21-pop)

     * [2.1.1 Personalidad](#211-personalidad)
     * [2.1.2 Necesidades](#212-necesidades)
   * [2.2 Bien](#22-bien)

     * [2.2.1 Bienes transables](#221-bienes-transables)
     * [2.2.2 Bienes no transables](#222-bienes-no-transables)
   * [2.3 Empresa](#23-empresa)
   * [2.4 Región](#24-región)
   * [2.5 Mercado](#25-mercado)
3. [Flujo de la Simulación](#3-flujo-de-la-simulación)

   * [3.1 Flujo del tiempo en la simulación y coordinación entre POPs y empresas](#31-flujo-del-tiempo-en-la-simulación-y-coordinación-entre-pops-y-empresas)
4. [Arquitectura del Proyecto](#4-arquitectura-del-proyecto)

   * [4.1 Estructuras (Structures)](#41-estructuras-structures)
   * [4.2 Lógica Central (Service)](#42-lógica-central-service)
   * [4.3 Interfaz de Usuario (UI)](#43-interfaz-de-usuario-ui)
   * [4.4 Aplicación (Application)](#44-aplicación-application)
   * [4.5 Persistencia de Datos (Repository)](#45-persistencia-de-datos-repository)
   * [4.6 Testing](#46-testing)
   * [4.7 Flujo de Datos entre Capas](#47-flujo-de-datos-entre-capas)
   * [4.8 Aclaraciones](#48-aclaraciones)
5. [Cómo Compilar y Ejecutar el Programa](#5-como-compilar-y-ejecutar-el-programa)

   * [5.1 Compilación y limpieza](#51-compilación-y-limpieza)
   * [5.2 Ejecución](#52-ejecución)
6. [Estrategia de Testing](#6-estrategia-de-testing)

   * [6.1 Testing unitario y de integración](#61-testing-unitario-y-de-integración)
   * [6.2 Testing de memoria](#62-testing-de-memoria)
   * [6.3 Testing de performance](#63-testing-de-performance)
   * [6.4 Compilación de los test](#64-compilación-de-los-test)
   * [6.5 Ejecución de los test](#65-ejecución-de-los-test)

## 1. Resumen del Proyecto

**Objetivo:**
El proyecto "Econ Sim" tiene como propósito simular modelos económicos y dinámicas de mercado a partir de la interacción de grupos de población que producen, consumen e intercambian bienes para satisfacer sus necesidades y generar ganancias.
El objetivo del proyecto es poder derivar conclusiones macroeconomicas basadas en interacciones microeconomicas entre agentes con personalidades distintas que definan su comportamiento esperado.

---

## 2. Modelos de la Simulación

### 2.1 POP
- **Descripcion**
  Representa a grupos de población con caracteristicas similares. Los mismos comparten:
  - Personalidad
  - Lugar de residencia
  - Lugar de trabajo (Empresa)
  - Profesión
  Cada POP tiene una cantidad determinada de población la cual puede fluctuar durante la simulación.

#### 2.1.1 Personalidad
- **Descripcion**
  Representa el conjunto de atributos que posee una POP que lo diferencian del resto respecto a sus preferencias
  - Determina las necesidades
  - Determina la propensión al consumo
  - Determina la propensión a la procreación

#### 2.1.2 Necesidades
- **Descripcion**
  Una necesidad es una caracteristica de la personalidad que determina el deseo de una POP de consumir determinada cantidad de ciertos bienes.
- **Formas de cubrirlas**
  Cada necesidad se cubre con una cierta cantidad de algún bien dentro de un grupo de bienes.
  Por ejemplo:
  - Hambre: verduras, carne, queso, etc
  - Vestimenta: ropa simple, ropa de lujo, etc

### 2.2 Bien
- **Descripción:**  
  Representa cada elemento producido y consumido por las POPs.  
- **Dinámica de Precios:**  
  Cada bien tiene un precio que fluctúa en cada jornada según la oferta y la demanda registradas en el mercado. La proporcion en la que esto ocurre por cada unidad del bien comerciado se deriva del promedio de las personalidades de todas las POPs (esto es, la funcion de elasticidad de cada bien va a depender de las preferencias de cada uno de los consumidores)
#### 2.2.1 Bienes transables
Representan aquellos que pueden ser comercializados entre regiones (materias primas, comida, vestimenta, etc)
#### 2.2.2 Bienes no transables
Son los que solo se pueden comerciar dentro de una region (transporte, educacion, salud, etc)

### 2.3 Empresa
- **Descripción:**  
  Es el modelo que se encarga de coordinar la producción de bienes. Utiliza bienes intermedios, materia prima y mano de obra para llevar a cabo la producción.
  La funcion de costos de la empresa depende de la mano de obra que utilicen, de la proporción de bienes y del capital utlizado en la producción.
- **Empresas intermediarias**
  Son aquellas que manejan el comercio entre regiones (se explica de forma más extensa en el apartado 2.5). Cualquier empresa puede volverse intermediaria si lo considera rentable.

### 2.4 Región
- **Descripción:** 
Las regiones son los lugares fisicos donde ocurre la producción, donde viven las POPs y de donde se extraen los bienes primarios. Además, las regiones tienen distancias definidas entre sí que pueden afectar la eficiencia del comercio.

### 2.5 Mercado
- **Descripción:**  
  Espacio de intercambio donde las POPs y empresas pueden adquirir bienes y ofertar sus productos. El mercado dispone los bienes dados por las empresas y POPs y les permite acceder a ellos a través del comercio. Existe un mercado por región.
- **Rol:**  
  Opera como interfaz intermedia y regula las transacciones, guardando información necesaria para el ajuste de precios.
- **Existencia de empresas intermediarias**
  Como en una misma region todo el comercio se regula mediante un solo mercado, la existencia de empresas intermediarias a nivel local no tiene sentido. Para manejar el comercio entre regiones existen empresas intermediarias que comercian bienes entre regiones, llevando bienes de una region a otra como parte de sus tareas. Sin embargo, el comercio entre regiones tiene costos extra de transporte (que a su vez dependen de los bienes de transporte disponibles en el mercado).
---

## 3. Flujo de la Simulación

1. **Inicio de la Jornada:**
   - Una POP inicia un nuevo día identificando las necesidades que debe satisfacer.
2. **Revisión de Recursos:**
   - La POP verifica los bienes que posee y que pueden cubrir sus necesidades.
3. **Producción o Trabajo:**
   - La POP comienza su día laboral asistiendo a la empresa donde trabaja. Allí se le proveen los bienes y herramientas necesarios para llevar a cabo dicha producción. Una vez que termina de producir, se le paga la remuneración acordada.
4. **Operaciones de Mercado:**
   - Una vez finalizada la jornada laboral, la empresa vende los bienes producidos en el mercado.
   - La POP puede optar por vender bienes en su posesión si necesitara recursos extra.
   - Las empresas proceden a comprar los bienes necesarios para la producción del día siguiente (según la producción esperada y los recursos disponibles), y las POPs los bienes necesarios para cubrir sus necesidades. La cantidad adquirida dependerá de la personalidad de la POP y de los recursos que posea
5. **Iteración:**
   - La jornada concluye y se inicia el siguiente ciclo, ajustando los precios de los bienes según la nueva oferta y demanda y las elasticidades de cada bien particular.

> **Nota:** El precio de cada bien es dinámico y se regula en función de las interacciones de oferta y demanda durante cada jornada. Los precios ademas son locales al mercado de cada región.

### 3.1 Flujo del tiempo en la simulación y coordinación entre POPs y empresas
Cada iteración corresponde a una jornada. Dentro de cada jornada, las POPs deben realizar 3 tareas
 - Cubrir sus necesidades
 - Trabajar
 - Comerciar
Cubrir sus necesidades y trabajar son dos tipos de operaciones que las POPs pueden realizar en paralelo (ya que no dependen de otras POPs para hacerlo), por lo que se calcularan en paralelo.
Comerciar es una actividad que requiere varias etapas:
 - Llevar los bienes al mercado
 - Reconocer qué bienes hay en el mercado
 - Comprar los bienes necesarios
Además, el stock de bienes no es infinito, por lo que habrá bienes que ciertas POPs o empresas puedan adquirir y que otras no, por lo que las últimas dos etapas representan un desafío interesante si queremos evitar linealizar el procesamiento de la etapa de comercio.
En este sentido, la tarea de llevar los bienes al mercado se puede paralelizar. Una vez el mercado tiene todo el stock disponible, los agentes (POPs y empresas) pueden comenzar a comerciar. Para ello, se establecerá un orden aleatorio en el que los agentes acceden al mercado (para garantizar equidad de acceso en el largo plazo) y cada agente comprará los bienes que necesite en 3 etapas (esto evita que los agentes con mayor propensión al consumo dejen sin bienes al resto, en caso de escasez significativa. El número 3 es arbitrario).

---

## 4. Arquitectura del Proyecto

Dado que se opta por desarrollar desde cero en C, siendo un lenguaje de bajo nivel, es fundamental una buena organización del código. Para ello, se ha planteado una arquitectura modular por capas:

### 4.1 Estructuras (Structures)
- **Función:**  
  Define y agrupa las estructuras de datos utilizadas en la simulación.
- **Importancia:**  
  Facilita la reutilización y el mantenimiento del código subyacente.

### 4.2 Lógica Central (Service)
- **Función:**  
  Implementa la lógica principal del programa, basada en los modelos descritos en el apartado anterior.
- **Responsabilidad:**  
  Efectúa los cálculos y establece las reglas que rigen la simulación.

### 4.3 Interfaz de Usuario (UI)
- **Función:**  
  Se encarga de la presentación y visualización de los datos generados por la simulación.
- **Enfoque:**  
  Asegura que el usuario final tenga acceso a información clara y precisa sobre el estado y evolución del sistema.

### 4.4 Aplicación (Application)
- **Función:**  
  Actúa como una capa intermediaria entre la lógica de negocio (Service) y la interfaz de usuario (UI).
- **Responsabilidades:**
  - Gestionar y mantener el estado global de la simulación.
  - Coordinar el flujo de datos entre las diferentes capas.
  - Facilitar la comunicación bidireccional (por ejemplo, enviar datos calculados al UI y recibir el estado actualizado para la siguiente iteración).

### 4.5 Persistencia de Datos (Repository)
- **Función:**  
  Define los contratos y la lógica de persistencia, permitiendo guardar y recuperar el estado de la simulación.
- **Aplicación:**  
  Se encarga de almacenar registros en archivos, lo cual es crucial para el análisis y la trazabilidad de la simulación.

### 4.6 Testing
- **Funcion**
  Asegurar que todos los modulos funcionen correctamente
- **Tipos de testing**
  Los test unitarios se definen dentro de cada módulo en un archivo (modulo).test.c (con su correspondiente header). Los test de integración se definen en la capa de testing general
- **Importancia**
  Asegura que cada una de las partes del proyecto, y el proyecto en su conjunto, funcionen como se espera.

### 4.7 Flujo de Datos entre Capas
- **Service → Application:**  
  El módulo Service calcula los datos y los transmite a Application.
- **Application → UI:**  
  La capa Application envía los datos pertinentes a la UI para su visualización.
- **Application → Repository:**  
  Application comunica los datos a la capa Repository para guardarlos de manera persistente.
- **Application → Service:**  
  La capa Application retroalimenta el estado actualizado al Service para permitir el cálculo de la siguiente iteración.

### 4.8 Aclaraciones
- Las implementaciones especificas que se hagan en cada capa no se detallan en la documentación ya que la idea es que distintas implementaciones sean aplicables y se puedan reemplazar sin afectar al resto de capas

---

## 5. Como compilar y ejecutar el programa

### 5.1 Compilación y limpieza
Compilamos ejecutando el siguiente comando en una consola
```bash
make
```
Esto nos generará un ejecutable. Para eliminar los archivos .o ejecutamos
```bash
make clean
```
### 5.2 Ejecución
Si queremos correr el programa directamente, ejecutamos
```bash
make run
```
Esto además limpiará los archivos .o

## 6. Estrategia de testing
### 6.1 Testing unitario y de integración
Se generarán archivos con extensión .test.c (con sus respectivos headers) los cuales contengan funciones de testing para cada uno de los modulos. mediante un archivo (type).test.c  (donde type es unit o integration) se ejecutarán de forma centralizada todos los test a la vez.
Los test deberán generar una salida a un archivo de texto con los logs de todos los test que hayan fallado, junto con una estadistica general (total de tests, tests exitosos, tests fallidos)
Para generar la salida de los test que fallan, se utilizarán macros similares a assert que den información extra, por ejemplo
```C
#include <stdio.h>
#include <stdlib.h>

#define MY_ASSERT(expr, msg) do { \
    if (!(expr)) { \
        fprintf(stderr, "Assertion failed: %s\nFile: %s, Line: %d - %s\n", #expr, __FILE__, __LINE__, msg); \
        return 1; \
    } \
} while (0)

```
### 6.2 Testing de memoria
Se utilizará Valgrind para corroborar que no ocurran leaks de memoria durante la ejecución del programa.
Se automatizará su uso mediante scripts de bash para ejecutar y analizar mas eficientemente la salida brindada por valgrind. Dichas salidas se guardaran en archivos de log para su posterior análisis
### 6.3 Testing de performance
Se utilizará una estrategia similar a la del punto 6.2, pero con el uso de funciones como clock() para medir el tiempo de ejecución de ciertas funciones críticas.
### 6.4 Compilación de los test
Se utilizará un makefile para los test unitarios y uno para los test de integración.
### 6.5 Ejecución de los test
Un script de bash se utilizará para realizar las siguientes tareas en orden
1. Compilar todos los test
2. Ejecutar tests unitarios
3. Ejecutar tests de integración
4. Ejecutar tests de memoria
5. Ejecutar tests de performance
6. Recopilar toda la información en un archivo de resumen con formato adecuado

## Materias pendientes
En esta sección se detallan cuestiones importantes que faltan definir para la implementación del proyecto.
### 1 Manejo de errrores
Definir una estrategia de manejo de errores dentro del programa.
### 2 Logging
Definir una implementación de logs (preferiblemente en archivos) para recopilar información interna importante de la ejecución del programa.
### 3 Manejo de memoria
Definir explicitamente cual es el patron por el cual se va a manejar la memoria dentro del proyecto.
### 4 Definición de interfaces de modelos
Definir los métodos y parametros que va a utilizar cada modelo descrito en la sección 2, además de las interfaces a usar para comunicarse con los otros modelos.
### 5 Definición de interfaces de capas
Definir cómo van a interactuar las distintas capas entre sí para garantizar la intercambiabilidad de módulos de ser necesario.
### 7 Definición de un apartado de configuración y parametrización general
Se requiere un apartado que detalle ciertos parametros como la cantidad de agentes y bienes, los rangos de precios, o los valores que determinan las necesidades, y que explique la razón detrás de los mismos, además de proyecciones de cómo podrían cambiar en el tiempo (ejemplo, se puede empezar con 3 bienes para testear una version inicial del modelo y ampliar ese número lo máximo posible con el tiempo).
### 9 Detalle de posibles implementaciones particulares de UI y capa de persistencia
Describir cómo se mostrarán los datos al usuario y cómo se van a guardar.
### 10 Definición de un menú de control para toda la app
Describir un flujo externo a la simulación que nos permita cargar otras simulaciones previas, borrarlas, etc. Esto ademas implica la definición de estrategias especificas de configuracion de simulaciones para parametrizarlas.
### 11 Diagrama de alto nivel
Un UML de componentes o un diagrama de secuencia para el flujo de una jornada ayudaría a visualizar la interacción entre agentes y capas.
### 12 Gestión de concurrencia
Definir una estrategia de gestión de concurrencia e hilos (si aplica)
### 13 Roadmap
Definir el flujo de desarrollo por etapas esperado para facilitar el desarrollo en el tiempo y evitar bloqueos.
### 14 Definir estandares de estilo codigo
Idioma en el que se programa (preferiblemente ingles), que tipo de notacion para variables, funciones y constantes se usa (preferiblemente usar snake_case para variables y funciones en UPPER_SNAKE_CASE)
### 16 Definir cómo se comportarán las funciones de costos de las empresas
Idealmente, esta función no debe tener "numeros mágicos", sino que debe derivar su funcionamiento de variables esenciales dentro de la simulación
---