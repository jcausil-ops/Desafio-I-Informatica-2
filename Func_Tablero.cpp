#include <iostream>
#include "Funciones_bit.h"
#include "random.h"
using namespace std;

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
    int posiciones = filas * columnas;
    cout << "\nTrama logica de fichas, tres bits por posicion\n";
    for (int idx = 0; idx < posiciones; ++idx) {
        unsigned char val = Obtener_ficha(memoria, Capacid_bytes, idx);
        cout << ((val >> 2) & 1) << ((val >> 1) & 1) << (val & 1) << ' ';
        if ((idx + 1) % columnas == 0)
            cout << '\n';
    }
}
