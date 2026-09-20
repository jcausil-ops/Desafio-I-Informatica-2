#ifndef LOGICA_JUEGO_H
#define LOGICA_JUEGO_H
static int Bytes_marcado_nec(int posiciones);
void Marcar_posicion(unsigned char *marcas, int posicion);
static bool Esta_marcado(const unsigned char *marcas, int posicion);
static void Marcar_secuencia_horizontal(unsigned char *marcas, int fila, int columnas,int col_inicio, int longitud);
static void Marcar_secuencia_vertical(unsigned char *marcas, int col, int columnas,int fila_inicio, int longitud);
bool Buscar_coincidencias(const unsigned char *memoria, int Capacid_bytes, int filas, int columnas,unsigned char *marcas, int &horizontales, int &verticales);
int Eliminar_fichas_marcadas(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,const unsigned char *marcas);
int Resolver_cascadas(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                      int &total_eliminadas, int &total_combinaciones,
                      int &comb_horizontales, int &comb_verticales,
                      long long &puntuacion);
void tablero_limpio(unsigned char *memoria, int Capacid_bytes, int filas, int columnas);
bool Eliminar_ficha_jugador(unsigned char *memoria, int Capacid_bytes, int filas, int columnas,
                            int fila, int columna, int &remociones_usuario, int &total_eliminadas,
                            int &total_combinaciones, int &comb_horizontales,
                            int &comb_verticales, long long &puntuacion, int &ultimas_cascadas);
void Mostrar_estado(int filas, int columnas, int Capacid_bytes, int remociones_usuario,
                    int total_eliminadas, int total_combinaciones, int comb_horizontales,
                    int comb_verticales, int ultimas_cascadas, long long puntuacion);
#endif // LOGICA_JUEGO_H
