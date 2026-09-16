#include <iostream>
#include "Funciones.h"
using namespace std;

int main()
{
    Board board;
    int f =3 , c=4;
    tablero(board, f , c );
    cout << "\n--- Estado del Tablero ---" << endl;
    cout << "Filas: " << board.filas << endl;
    cout << "Columnas: " << board.columnas << endl;
    cout << "Bytes reservados: " << board.bytes_reservados << endl;

    // Comprobar que la memoria dinámica no sea nula
    if (board.dinam != NULL) {
        cout << "Memoria reservada e inicializada correctamente." << endl;
    }

    // 3. Liberación de memoria dinámica
    delete[] board.dinam;
    board.dinam = NULL;

    return 0;
}
