#include <iostream>
#include "Funciones_bit.h"
#include "Func_Tablero.h"
#include "random.h"

using namespace std;

int Leer_entero(const char mensaje[])
{
    int valor = 0;
    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
            return valor;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida. Intente nuevamente.\n";
    }
}

void Mostrar_menu()
{
    cout << "\n1. Mostrar tablero\n";
    cout << "2. Eliminar ficha\n";
    cout << "3. Agregar fila\n";
    cout << "4. Eliminar fila\n";
    cout << "5. Agregar columna\n";
    cout << "6. Eliminar columna\n";
    cout << "0. Salir\n";
}

static const char* simbol_ficha(unsigned char ficha)
{
    static const char* Simb[] = {"#", "@", "*", "$", "&", "%"};

    if (ficha < Libre)
        return Simb[ficha];
    if (ficha == Libre)
        return ".";
    return "?";
}

static void Nuevo_tablero(unsigned char *&memoria, int &Capacid_bytes,unsigned char *nueva_memoria, int nueva_capacidad)
{
    Delete_memoria(memoria);
    memoria = nueva_memoria;
    Capacid_bytes = nueva_capacidad;
}

unsigned char *Crear_tablero(int filas, int columnas, int &Capacid_bytes)
{
    Capacid_bytes = Bytes_nec(filas, columnas);
    return Pack_memoria(Capacid_bytes);
}

void Llenar_tablero(unsigned char *memoria, int Capacid_bytes, int filas, int columnas)
{
    int posiciones = filas * columnas;
    for (int idx = 0; idx < posiciones; ++idx)
        asignar_ficha(memoria, Capacid_bytes, idx, randomFicha());

    limpiar_no_use(memoria, Capacid_bytes, filas, columnas);
}

void Imprim_tablero(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas)
{
    cout << "\nTablero de fichas\n    ";
    for (int col = 0; col < columnas; ++col) {
        if (col < 10)
            cout << ' ';
        cout << ' ' << col;
    }
    cout << '\n';

    for (int f = 0; f < filas; ++f) {
        if (f < 10) cout << ' ';
        cout << f << " | ";
        for (int c = 0; c < columnas; ++c) {
            int pos = f * columnas + c;
            cout << ' ' << simbol_ficha(Obtener_ficha(memoria, Capacid_bytes, pos)) << ' ';
        }
        cout << '\n';
    }
}

void Imp_tablero_binario(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas)
{
    if (!memoria || Capacid_bytes <= 0)
        return;

    int posiciones = filas * columnas;
    cout << "\nTrama logica de fichas, tres bits por posicion\n";
    for (int idx = 0; idx < posiciones; ++idx) {
        unsigned char val = Obtener_ficha(memoria, Capacid_bytes, idx);
        cout << ((val >> 2) & 1) << ((val >> 1) & 1) << (val & 1) << ' ';
        if ((idx + 1) % columnas == 0)
            cout << '\n';
    }

    cout << "Bytes fisicos, mayor indice primero; los bits no validos quedan a la izquierda\n";
    for (int byteIndex = Capacid_bytes - 1; byteIndex >= 0; --byteIndex) {
        for (int bit = 7; bit >= 0; --bit) {
            cout << ((memoria[byteIndex] >> bit) & 1u);
        }
        cout << ' ';
    }
    cout << '\n';
}

void gravedad_relleno(unsigned char *memoria, int Capacid_bytes, int filas, int columnas)
{
    for (int c = 0; c < columnas; ++c) {
        int fila_destino = filas - 1;
        for (int fila_origen = filas - 1; fila_origen >= 0; --fila_origen) {
            int pos_origen = fila_origen * columnas + c;
            unsigned char valor = Obtener_ficha(memoria, Capacid_bytes, pos_origen);
            if (valor != Libre) {
                int pos_destino = fila_destino * columnas + c;
                if (pos_destino != pos_origen) {
                    asignar_ficha(memoria, Capacid_bytes, pos_destino, valor);
                    asignar_ficha(memoria, Capacid_bytes, pos_origen, Libre);
                }
                --fila_destino;
            }
        }
        while (fila_destino >= 0) {
            int pos_destino = fila_destino * columnas + c;
            asignar_ficha(memoria, Capacid_bytes, pos_destino, randomFicha());
            --fila_destino;
        }
    }
    limpiar_no_use(memoria, Capacid_bytes, filas, columnas);
}

bool Agregar_fila(unsigned char *&memoria, int &Capacid_bytes, int &filas, int columnas, int posicion)
{
    if (posicion < 0 || posicion > filas)
        return false;

    int nuevas_filas = filas + 1;
    int bytes_requeridos = Bytes_nec(nuevas_filas, columnas);
    int nueva_capacidad = bytes_requeridos > Capacid_bytes ? bytes_requeridos : Capacid_bytes;

    unsigned char *nueva_memoria = Pack_memoria(nueva_capacidad);

    for (int f_nueva = 0; f_nueva < nuevas_filas; ++f_nueva) {
        for (int c = 0; c < columnas; ++c) {
            unsigned char valor = randomFicha();
            if (f_nueva != posicion) {
                int f_vieja = f_nueva < posicion ? f_nueva : f_nueva - 1;
                valor = Obtener_ficha(memoria, Capacid_bytes, f_vieja * columnas + c);
            }
            asignar_ficha(nueva_memoria, nueva_capacidad, f_nueva * columnas + c, valor);
        }
    }

    limpiar_no_use(nueva_memoria, nueva_capacidad, nuevas_filas, columnas);
    Nuevo_tablero(memoria, Capacid_bytes, nueva_memoria, nueva_capacidad);
    filas = nuevas_filas;
    return true;
}

bool Eliminar_fila(unsigned char *&memoria, int &Capacid_bytes, int &filas, int columnas, int posicion)
{
    if (posicion < 0 || posicion >= filas || filas == 1)
        return false;

    int nuevas_filas = filas - 1;
    int bytes_requeridos = Bytes_nec(nuevas_filas, columnas);
    int nueva_capacidad = (bytes_requeridos * 100 < Capacid_bytes * 65) ? bytes_requeridos : Capacid_bytes;

    unsigned char *nueva_memoria = Pack_memoria(nueva_capacidad);
    int f_nueva = 0;

    for (int f_vieja = 0; f_vieja < filas; ++f_vieja) {
        if (f_vieja == posicion)
            continue;

        for (int c = 0; c < columnas; ++c) {
            unsigned char valor = Obtener_ficha(memoria, Capacid_bytes, f_vieja * columnas + c);
            asignar_ficha(nueva_memoria, nueva_capacidad, f_nueva * columnas + c, valor);
        }
        ++f_nueva;
    }
    limpiar_no_use(nueva_memoria, nueva_capacidad, nuevas_filas, columnas);
    Nuevo_tablero(memoria, Capacid_bytes, nueva_memoria, nueva_capacidad);
    filas = nuevas_filas;
    return true;
}

bool Agregar_columna(unsigned char *&memoria, int &Capacid_bytes, int filas, int &columnas, int posicion)
{
    if (posicion < 0 || posicion > columnas)
        return false;

    int nuevas_columnas = columnas + 1;
    int bytes_requeridos = Bytes_nec(filas, nuevas_columnas);
    int nueva_capacidad = bytes_requeridos > Capacid_bytes ? bytes_requeridos : Capacid_bytes;

    unsigned char *nueva_memoria = Pack_memoria(nueva_capacidad);

    for (int f = 0; f < filas; ++f) {
        for (int c_nueva = 0; c_nueva < nuevas_columnas; ++c_nueva) {
            unsigned char valor = randomFicha();
            if (c_nueva != posicion) {
                int c_vieja = c_nueva < posicion ? c_nueva : c_nueva - 1;
                valor = Obtener_ficha(memoria, Capacid_bytes, f * columnas + c_vieja);
            }
            asignar_ficha(nueva_memoria, nueva_capacidad, f * nuevas_columnas + c_nueva, valor);
        }
    }

    limpiar_no_use(nueva_memoria, nueva_capacidad, filas, nuevas_columnas);
    Nuevo_tablero(memoria, Capacid_bytes, nueva_memoria, nueva_capacidad);
    columnas = nuevas_columnas;
    return true;
}

bool Eliminar_columna(unsigned char *&memoria, int &Capacid_bytes, int filas, int &columnas, int posicion)
{
    if (posicion < 0 || posicion >= columnas || columnas == 1)
        return false;

    int nuevas_columnas = columnas - 1;
    int bytes_requeridos = Bytes_nec(filas, nuevas_columnas);
    int nueva_capacidad = (bytes_requeridos * 100 < Capacid_bytes * 65) ? bytes_requeridos : Capacid_bytes;

    unsigned char *nueva_memoria = Pack_memoria(nueva_capacidad);

    for (int f = 0; f < filas; ++f) {
        int c_nueva = 0;
        for (int c_vieja = 0; c_vieja < columnas; ++c_vieja) {
            if (c_vieja == posicion)
                continue;

            unsigned char valor = Obtener_ficha(memoria, Capacid_bytes, f * columnas + c_vieja);
            asignar_ficha(nueva_memoria, nueva_capacidad, f * nuevas_columnas + c_nueva, valor);
            ++c_nueva;
        }
    }

    limpiar_no_use(nueva_memoria, nueva_capacidad, filas, nuevas_columnas);
    Nuevo_tablero(memoria, Capacid_bytes, nueva_memoria, nueva_capacidad);
    columnas = nuevas_columnas;
    return true;
}

