# Econ Sim: Simulador de Modelos Económicos y Mercados

## 1. Resumen del Proyecto

**Objetivo:**  
El proyecto "Econ Sim" tiene como propósito simular modelos económicos y dinámicas de mercado a partir de la interacción de agentes que producen, consumen e intercambian bienes para satisfacer sus necesidades.

---

## 2. Modelos de Simulación

### 2.1 Agente
- **Descripción:**  
  Representa al actor principal de la simulación. Cada agente está diseñado para:
  - Interactuar con otros agentes mediante el intercambio de bienes basado en condiciones predeterminadas.
  - Poseer una función de costos individual que determina la productividad de su trabajo (particularmente, determina la cantidad de materia prima y output esperado)
  - Poseer una funcion de demanda final, la cual utiliza la funcion de demanda de la personalidad para demandar la cantidad final de bienes que el agente va a consumir. Depende del nivel de vida esperado y de la funcion de costos del agente

### 2.2 Pop
- **Descripción:**  
  Conjunto de agentes con características similares, que comparten necesidades y funciones laborales.
- **Motivación:**  
  La agrupación de agentes simplifica el cómputo, ya que se puede asumir un comportamiento homogéneo en determinados contextos de simulación.

### 2.3 Necesidades
- **Descripción:**  
  Este modelo determina los motivos subyacentes por los cuales un agente desea consumir determinados bienes, además de definir en qué cantidad se los consume (para cubrir 1 unidad de necesidad) y qué bienes cubren dicha necesidad.
- **Importancia:**  
  La lista de necesidades es fundamental, pues define el perfil o la _personalidad_ del agente y, por ende, su comportamiento en el mercado.

### 2.4 Personalidad
- **Descripción:**  
  Conjunto de necesidades recurrentes que configuran la toma de decisiones de un agente.
- **Función:**  
  Establece la función de demanda, determinando qué bienes son prioritarios para cada agente en función de su perfil.

### 2.5 Bien
- **Descripción:**  
  Representa cada elemento producido y consumido por los agentes.  
- **Dinámica de Precios:**  
  Cada bien tiene un precio que fluctúa en cada jornada según la oferta y la demanda registradas en el mercado. La proporcion en la que esto ocurre por cada unidad del bien comerciado se deriva del promedio de las personalidades de todas las agentes (esto es, la funcion de elasticidad de cada bien va a depender de las preferencias de cada uno de los consumidores)

### 2.6 Mercado
- **Descripción:**  
  Espacio de intercambio donde los agentes pueden adquirir bienes y ofertar sus productos. El mercado dispone los bienes de los agentes y les permite acceder a ellos a través del comercio
- **Rol:**  
  Opera como interfaz intermedia y regula las transacciones, ajustando los precios de los bienes en función del balance entre oferta y demanda.

---

## 3. Flujo de la Simulación

1. **Inicio de la Jornada:**
   - Un agente inicia un nuevo día identificando las necesidades que debe satisfacer.
2. **Revisión de Recursos:**
   - El agente verifica los bienes que posee y que pueden cubrir sus necesidades.
3. **Producción o Trabajo:**
   - Ante la falta de recursos suficientes, el agente procede a trabajar para generar nuevos bienes.
   - Si los recursos fueran suficientes, dependerá de su personalidad si decide o no trabajar.
4. **Operaciones de Mercado:**
   - Una vez finalizada la jornada laboral, el agente vende los bienes producidos en el mercado.
   - Con los ingresos obtenidos, se adquieren los bienes necesarios para cubrir las necesidades del día siguiente. La cantidad adquirida de cada bien dependerá de los ingresos y personalidad del agente (pueden haber personalidades mas austeras y otras más consumistas).
5. **Iteración:**
   - La jornada concluye y se inicia el siguiente ciclo, ajustando los precios de los bienes según la nueva oferta y demanda.

> **Nota:** El precio de cada bien es dinámico y se regula en función de las interacciones de oferta y demanda durante cada jornada.

### 3.1 Flujo del tiempo en la simulación y coordinación entre agentes
Cada iteración corresponde a una jornada. Dentro de cada jornada, los agentes deben realizar 3 tareas
 - Cubrir sus necesidades
 - Trabajar
 - Comerciar
Cubrir sus necesidades y trabajar son dos tipos de operaciones que los agentes pueden realizar en paralelo (ya que no dependen de otros agentes), por lo que se calcularan de esta forma.
Comerciar es una actividad que requiere varias etapas:
 - Llevar los bienes al mercado
 - Reconocer qué bienes hay en el mercado
 - Comprar los bienes necesarios
Además, el stock de bienes no es infinito, por lo que habrá bienes que ciertos agentes puedan adquirir y que otros agentes no, por lo que las últimas dos etapas representan un desafío interesante si queremos evitar linealizar el procesamiento de todos los agentes.
En este sentido, la tarea de llevar los bienes al mercado se puede paralelizar. Una vez el mercado tiene todo el stock disponible, los agentes pueden comenzar a comerciar. Para ello, se establecerá un orden aleatorio en el que los agentes acceden al mercado (para garantizar equidad de acceso en el largo plazo) y cada agente comprará los bienes que necesite en 3 etapas (esto evita que los agentes con personalidades mas consumistas dejen sin bienes al resto, en caso de escasez significativa, el número 3 es arbitrario).

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

## 5. Materias pendientes
En esta sección se detallan cuestiones importantes que faltan definir para la implementación del proyecto.
### 5.1 Manejo de errrores
Definir una estrategia de manejo de errores dentro del programa.
### 5.2 Logging
Definir una implementación de logs (preferiblemente en archivos) para recopilar información interna importante de la ejecución del programa.
### 5.3 Manejo de memoria
Definir explicitamente cual es el patron por el cual se va a manejar la memoria dentro del proyecto.
### 5.4 Definición de interfaces de modelos
Definir los métodos y parametros que va a utilizar cada modelo descrito en la sección 2, además de las interfaces a usar para comunicarse con los otros modelos.
### 5.5 Definición de interfaces de capas
Definir cómo van a interactuar las distintas capas entre sí para garantizar la intercambiabilidad de módulos de ser necesario.
### 5.6 Definición de librería de Testing
Definir con qué herramientas se va a realizar el testing en el proyecto.
### 5.7 Definición de un apartado de configuración y parametrización general
Se requiere un apartado que detalle ciertos parametros como la cantidad de agentes y bienes, los rangos de precios, o los valores que determinan las necesidades, y que explique la razón detrás de los mismos, además de proyecciones de cómo podrían cambiar en el tiempo (ejemplo, se puede empezar con 3 bienes para testear una version inicial del modelo y ampliar ese número lo máximo posible con el tiempo).
### 5.8 Detalle de las estrategias de testing para cada capa
Detallar cómo se implementan los test en cada capa, si es que tienen alguna particularidad a mencionar.
### 5.9 Detalle de posibles implementaciones particulares de UI y capa de persistencia
Describir cómo se mostrarán los datos al usuario y cómo se van a guardar.
### 5.10 Definición de un menú de control para toda la app
Describir un flujo externo a la simulación que nos permita cargar otras simulaciones previas, borrarlas, etc. Esto ademas implica la definición de estrategias especificas de configuracion de simulaciones para parametrizarlas.
### 5.11 Diagrama de alto nivel
Un UML de componentes o un diagrama de secuencia para el flujo de una jornada ayudaría a visualizar la interacción entre agentes y capas.
### 5.12 Gestión de concurrencia
Definir una estrategia de gestión de concurrencia e hilos (si aplica)
### 5.13 Roadmap
Definir el flujo de desarrollo por etapas esperado para facilitar el desarrollo en el tiempo y evitar bloqueos.
### 5.14 Definir estandares de estilo codigo
Idioma en el que se programa (preferiblemente ingles), que tipo de notacion para variables, funciones y constantes se usa (preferiblemente usar snake_case para variables y funciones en UPPER_SNAKE_CASE)
### 5.15 Agregar un indice al principio de la documentación

---

## 6. Como compilar y ejecutar el programa

### 6.1 Compilación
Compilamos ejecutando el siguiente comando en una consola
```bash
make
```
Esto nos generará un ejecutable. Para eliminar los archivos .o ejecutamos
```bash
make clean
```
Si queremos correr el programa directamente, ejecutamos
```bash
make run
```