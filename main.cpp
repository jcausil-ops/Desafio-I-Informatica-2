#include "Funciones_bit.h"
#include "Func_Tablero.h"
#include "Logica_juego.h"
#include <iostream>

using namespace std;


int main()
{
    cout << "=====================================================================\n";
    cout << "||                                                                 ||\n";
    cout << "||                   BIENVENIDO A SWEET CRUSH                      ||\n";
    cout << "||                                                                 ||\n";
    cout << "||                    by: Juan and Sebastian                       ||\n";
    cout << "=====================================================================\n\n";
    int filas = Leer_entero("Filas iniciales, minimo 3: ");
    int columnas = Leer_entero("Columnas iniciales, minimo 3: ");

    while (filas < 3 || columnas < 3)
    {
        cout << "Ambas dimensiones deben ser al menos 3.\n";
        filas = Leer_entero("Filas iniciales: ");
        columnas = Leer_entero("Columnas iniciales: ");
    }

    int Capacid_bytes = 0;
    unsigned char *memoria = Crear_tablero(filas, columnas, Capacid_bytes);
    Llenar_tablero(memoria, Capacid_bytes, filas, columnas);

    void tablero_limpio(unsigned char *memoria, int Capacid_bytes, int filas, int columnas);

    int remociones_usuario = 0;
    int total_eliminadas = 0;
    int total_combinaciones = 0;
    int comb_horizontales = 0;
    int comb_verticales = 0;
    int ultimas_cascadas = 0;
    long long puntuacion = 0;

    int opcion = -1;

    while (opcion != 0)
    {
        Imprim_tablero(memoria, Capacid_bytes, filas, columnas);
        cout << "Presione [Enter]: ";
        cin.ignore(10000, '\n');
        cin.get();

        Imp_tablero_binario(memoria, Capacid_bytes, filas, columnas);
        Mostrar_estado(filas, columnas, Capacid_bytes, remociones_usuario, total_eliminadas,
                       total_combinaciones, comb_horizontales, comb_verticales,
                       ultimas_cascadas, puntuacion);

        Mostrar_menu();
        opcion = Leer_entero("Opcion: ");
        ultimas_cascadas = 0;
        bool cambio = false;

        if (opcion == 2)
        {
            int fila = Leer_entero("Fila: ");
            int columna = Leer_entero("Columna: ");
            cambio = Eliminar_ficha_jugador(memoria, Capacid_bytes, filas, columnas,
                                            fila, columna, remociones_usuario, total_eliminadas,
                                            total_combinaciones, comb_horizontales,
                                            comb_verticales, puntuacion, ultimas_cascadas);
        }
        else if (opcion == 3)
        {
            int posicion = Leer_entero("Posicion de la nueva fila, de 0 a filas: ");
            cambio = Agregar_fila(memoria, Capacid_bytes, filas, columnas, posicion);
        }
        else if (opcion == 4)
        {
            int posicion = Leer_entero("Fila que se eliminara: ");
            cambio = Eliminar_fila(memoria, Capacid_bytes, filas, columnas, posicion);
        }
        else if (opcion == 5)
        {
            int posicion = Leer_entero("Posicion de la nueva columna, de 0 a columnas: ");
            cambio = Agregar_columna(memoria, Capacid_bytes, filas, columnas, posicion);
        }
        else if (opcion == 6)
        {
            int posicion = Leer_entero("Columna que se eliminara: ");
            cambio = Eliminar_columna(memoria, Capacid_bytes, filas, columnas, posicion);
        }

        if (cambio && opcion >= 3 && opcion <= 6)
        {
            ultimas_cascadas = Resolver_cascadas(memoria, Capacid_bytes, filas, columnas,
                                                 total_eliminadas, total_combinaciones,
                                                 comb_horizontales, comb_verticales, puntuacion);
        }
        else if ((opcion >= 2 && opcion <= 6) && !cambio)
        {
            cout << "Operacion rechazada: revise la posicion o la dimension minima.\n";
        }
        else if (opcion < 0 || opcion > 6)
        {
            cout << "Opcion: " << opcion << " Ingrese una opcion valida\n";
        }
    }

    Delete_memoria(memoria);
    return 0;
}