#ifndef FUNC_TABLERO_H
#define FUNC_TABLERO_H

static const char* simbol_ficha(unsigned char ficha);
static void Nuevo_tablero(unsigned char *&memoria, int &Capacid_bytes,unsigned char *nueva_memoria, int nueva_capacidad);
unsigned char *Crear_tablero(int filas, int columnas, int &Capacid_bytes);
void Llenar_tablero(unsigned char *memoria, int Capacid_bytes, int filas, int columnas);
void Imprim_tablero(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas);
void Imp_tablero_binario(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas);
void gravedad_relleno(unsigned char *memoria, int Capacid_bytes, int filas, int columnas);
bool Agregar_fila(unsigned char *&memoria, int &Capacid_bytes, int &filas, int columnas, int posicion);
bool Eliminar_fila(unsigned char *&memoria, int &Capacid_bytes, int &filas, int columnas, int posicion);
bool Agregar_columna(unsigned char *&memoria, int &Capacid_bytes, int filas, int &columnas, int posicion);
bool Eliminar_columna(unsigned char *&memoria, int &Capacid_bytes, int filas, int &columnas, int posicion);

#endif // FUNC_TABLERO_H
