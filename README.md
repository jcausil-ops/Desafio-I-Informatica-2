Sweet Crush
Simulación del juego Sweet Crush desarrollada en C++ para la asignatura Informática II. El objetivo principal es la representación de un tablero de dimensiones variables con optimización de memoria RAM, almacenando cada casilla en exactamente 3 bits mediante operaciones de bits.


Características Principales
Optimización de Memoria: Empaquetado dinámico de 3 bits por casilla dentro de un arreglo unidimensional de bytes.

Tablero Dinámico: Permite agregar y eliminar filas y columnas en tiempo de ejecución.

Lógica de Juego: Detección automática de alineaciones de 3 o más fichas, eliminación física y caída por gravedad con rellenado aleatorio.

Reacción en Cadena: Procesamiento de cascadas iterativas y acumulación de puntuación.


Estructura del Código
main.cpp: Bucle principal del juego y menú de usuario.

Funciones_bit.cpp / Funciones_bit.h: Algoritmos de empaquetado, desempaquetado y manipulación a nivel de bits.

Func_Tablero.cpp / Func_Tablero.h: Gestión de memoria dinámica, renderizado y redimensionamiento del tablero.

Logica_juego.cpp / Logica_juego.h: Detección de patrones, marcas y resolución de cascadas.

random.cpp / random.h: Generación aleatoria de fichas.

CMakeLists.txt: Configuración para la compilación del proyecto.


Compilación y Ejecución
Para compilar el proyecto con CMake:

Crear carpeta de compilación: mkdir build y cd build

Generar archivos del proyecto: cmake ..

Compilar: make

Ejecutar el programa: ./SweetCrush


Autores 
Juan Sebastian Rodriguez Lizcano 
Juan David Causil Osorio
