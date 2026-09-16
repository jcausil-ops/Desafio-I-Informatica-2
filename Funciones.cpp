#include <iostream>

using namespace std;

 // "●", "○", "◎", "■", "□", "▲"
const unsigned char ficha0 = 0b000, ficha_1 = 0b001,ficha2 = 0b010,ficha_3 = 0b011;
const unsigned char ficha_4 = 0b100, ficha_5 = 0b101, ficha7 = 0b110, libre = 0b111;

struct Board{
    int filas,columnas,bytes_reservados;
    unsigned char* dinam;
};

void tablero(Board &board, int f, int c){
    board.filas = f;
    board.columnas = c;

    board.bytes_reservados = (((f*c*3)+7)/8);

    board.dinam = new unsigned char[board.bytes_reservados];
    for(int i=0;i<board.bytes_reservados;i++){
        board.dinam[i] = 0;
    }
}


