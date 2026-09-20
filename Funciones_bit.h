#ifndef FUNCIONES_BIT_H
#define FUNCIONES_BIT_H
const unsigned char ficha0 = 0b000, ficha_1 = 0b001,ficha2 = 0b010,ficha_3 = 0b011;
const unsigned char ficha_4 = 0b100, ficha_5 = 0b101, Libre= 0b110, nulo = 0b111;

int Bytes_nec(int fila, int columa);
unsigned char *Pack_memoria(int bytes_rser);
void Delete_memoria(unsigned char *&memory);
unsigned char Obtener_ficha(const unsigned char *memory, int Capacid_bytes, int Posicion);
void asignar_ficha(unsigned char *memory, int Capacid_bytes, int Posicion, unsigned char valor_f);
void limpiar_no_use(unsigned char *memoria, int bytes_reservados, int filas, int columnas);
#endif // FUNCIONES_BIT_H
