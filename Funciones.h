#ifndef FUNCIONES_H
#define FUNCIONES_H

struct Board{
    int filas,columnas,bytes_reservados;
    unsigned char* dinam = nullptr;
};

void tablero(Board &board, int f, int c);

#endif // FUNCIONES_H