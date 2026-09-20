#include "Logica_juego.h"
#include "Func_Tablero.h"
#include "Funciones_bit.h"
#include <iostream>
using namespace std;


static int Bytes_marcado_nec(int posiciones)
{
    return (posiciones + 7) / 8;
}

static void Marcar_posicion(unsigned char *marcas, int posicion)
{

    marcas[posicion / 8] |= static_cast<unsigned char>(1 << (posicion % 8));
}

static bool Esta_marcado(const unsigned char *marcas, int posicion)
{
    return ((marcas[posicion / 8] >> (posicion % 8)) & 1) != 0;
}

static void Marcar_secuencia_horizontal(unsigned char *marcas, int fila, int columnas,
                                        int col_inicio, int longitud)
{
    for (int col = col_inicio; col < col_inicio + longitud; ++col)
        Marcar_posicion(marcas, fila * columnas + col);
}

static void Marcar_secuencia_vertical(unsigned char *marcas, int col, int columnas,
                                      int fila_inicio, int longitud)
{
    for (int fila = fila_inicio; fila < fila_inicio + longitud; ++fila)
        Marcar_posicion(marcas, fila * columnas + col);
}


bool Buscar_coincidencias(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                          unsigned char *marcas, int &horizontales, int &verticales)
{
    int posiciones = filas * columnas;
    int bytes_marcas = Bytes_marcado_nec(posiciones);
    for (int i = 0; i < bytes_marcas; ++i)
        marcas[i] = 0;

    horizontales = 0;
    verticales = 0;


    for (int f = 0; f < filas; ++f)
    {
        int inicio = 0;
        while (inicio < columnas)
        {
            unsigned char valor = Obtener_ficha(memoria, Capacid_bytes, f * columnas + inicio);
            int fin = inicio + 1;
            while (fin < columnas && Obtener_ficha(memoria, Capacid_bytes, f * columnas + fin) == valor)
                ++fin;

            int longitud = fin - inicio;
            if (valor < Libre && longitud >= 3)
            {
                Marcar_secuencia_horizontal(marcas, f, columnas, inicio, longitud);
                ++horizontales;
            }
            inicio = fin;
        }
    }


    for (int c = 0; c < columnas; ++c)
    {
        int inicio = 0;
        while (inicio < filas)
        {
            unsigned char valor = Obtener_ficha(memoria, Capacid_bytes, inicio * columnas + c);
            int fin = inicio + 1;
            while (fin < filas && Obtener_ficha(memoria, Capacid_bytes, fin * columnas + c) == valor)
                ++fin;

            int longitud = fin - inicio;
            if (valor < Libre && longitud >= 3)
            {
                Marcar_secuencia_vertical(marcas, c, columnas, inicio, longitud);
                ++verticales;
            }
            inicio = fin;
        }
    }

    return (horizontales + verticales) > 0;
}

int Eliminar_fichas_marcadas(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                             const unsigned char *marcas)
{
    int eliminadas = 0;
    int posiciones = filas * columnas;
    for (int pos = 0; pos < posiciones; ++pos)
    {
        if (Esta_marcado(marcas, pos))
        {
            asignar_ficha(memoria, Capacid_bytes, pos, Libre);
            ++eliminadas;
        }
    }
    return eliminadas;
}

int Resolver_cascadas(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                      int &total_eliminadas, int &total_combinaciones,
                      int &comb_horizontales, int &comb_verticales,
                      long long &puntuacion)
{
    int posiciones = filas * columnas;
    int bytes_marcas = Bytes_marcado_nec(posiciones);
    unsigned char *marcas = new unsigned char[bytes_marcas];

    int cascadas = 0;
    int horiz = 0;
    int vert = 0;

    while (Buscar_coincidencias(memoria, Capacid_bytes, filas, columnas, marcas, horiz, vert))
    {
        ++cascadas;
        int eliminadas = Eliminar_fichas_marcadas(memoria, Capacid_bytes, filas, columnas, marcas);

        total_eliminadas += eliminadas;
        total_combinaciones += (horiz + vert);
        comb_horizontales += horiz;
        comb_verticales += vert;

        puntuacion += static_cast<long long>(eliminadas) * 20 * cascadas;

        gravedad_relleno(memoria, Capacid_bytes, filas, columnas);
    }

    delete[] marcas;
    return cascadas;
}

void tablero_limpio(unsigned char *memoria, int Capacid_bytes, int filas, int columnas)
{
    Llenar_tablero(memoria, Capacid_bytes, filas, columnas);

    int elim = 0, comb = 0, horiz = 0, vert = 0;
    long long pts = 0;

    Resolver_cascadas(memoria, Capacid_bytes, filas, columnas, elim, comb, horiz, vert, pts);
}

bool Eliminar_ficha_jugador(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                            int fila, int columna, int &remociones_usuario, int &total_eliminadas,
                            int &total_combinaciones, int &comb_horizontales,
                            int &comb_verticales, long long &puntuacion, int &ultimas_cascadas)
{
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
        return false;

    int posicion = fila * columnas + columna;
    if (Obtener_ficha(memoria, Capacid_bytes, posicion) >= Libre)
        return false;

    asignar_ficha(memoria, Capacid_bytes, posicion, Libre);
    ++remociones_usuario;
    ++total_eliminadas;
    puntuacion += 10LL;

    gravedad_relleno(memoria, Capacid_bytes, filas, columnas);

    ultimas_cascadas = Resolver_cascadas(memoria, Capacid_bytes, filas, columnas,
                                         total_eliminadas, total_combinaciones,
                                         comb_horizontales, comb_verticales, puntuacion);
    return true;
}

void Mostrar_estado(int filas, int columnas, int Capacid_bytes, int remociones_usuario,
                    int total_eliminadas, int total_combinaciones, int comb_horizontales,
                    int comb_verticales, int ultimas_cascadas, long long puntuacion)
{
    int bytes_minimos = Bytes_nec(filas, columnas);

    cout << "\n================ ESTADO DEL JUEGO ================\n";
    cout << "Dimensiones: " << filas << " x " << columnas << '\n';
    cout << "Memoria fisica (Capacidad): " << Capacid_bytes << " bytes\n";
    cout << "Memoria logica minima: " << bytes_minimos << " bytes\n";
    cout << "Ocupacion de RAM: " << (bytes_minimos * 100 / Capacid_bytes) << " %\n";
    cout << "--------------------------------------------------\n";
    cout << "Eliminaciones del usuario: " << remociones_usuario << '\n';
    cout << "Fichas eliminadas en total: " << total_eliminadas << '\n';
    cout << "Combinaciones totales: " << total_combinaciones << '\n';
    cout << "  - Horizontales: " << comb_horizontales << '\n';
    cout << "  - Verticales: " << comb_verticales << '\n';
    cout << "Cascadas generadas en este turno: " << ultimas_cascadas << '\n';
    cout << "Puntuacion actual: " << puntuacion << " pts\n";
    cout << "==================================================\n";
}