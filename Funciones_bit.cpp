#include "Funciones_bit.h"

int Bytes_nec(int fila, int columna)
{
    int totalBits = fila * columna * 3 ;
    return (totalBits + 7) / 8;
}

unsigned char *Pack_memoria(int bytes_rser)
{
    unsigned char *memory = new unsigned char[bytes_rser];
    for (int index = 0; index < bytes_rser; ++index)
        memory[index] = 0;
    return memory;
}

void Delete_memoria(unsigned char *&memory)
{
    delete[] memory;
    memory = nullptr;
}

unsigned char Obtener_ficha(const unsigned char *memory, int Capacid_bytes, int Posicion) {
    int bit_inicio = Posicion * 3;
    int Posc_byte = bit_inicio / 8;
    int inic_ficha = bit_inicio % 8;


    if (Posc_byte >= Capacid_bytes) return 0;

    if (inic_ficha <= 5) {

        return (memory[Posc_byte] >> inic_ficha) & 0b111;
    } else {

        int bits_primer_byte = 8 - inic_ficha;
        unsigned char parte1 = (memory[Posc_byte] >> inic_ficha);
        unsigned char mascara1 = (1 << bits_primer_byte) - 1;
        parte1 &= mascara1;

        unsigned char parte2 = 0;
        if (Posc_byte + 1 < Capacid_bytes) {
            parte2 = memory[Posc_byte + 1];
            int bits_segundo_byte = 3 - bits_primer_byte;
            unsigned char mascara2 = (1 << bits_segundo_byte) - 1;
            parte2 &= mascara2;
        }

        return parte1 | (parte2 << bits_primer_byte);
    }
}

void asignar_ficha(unsigned char *memory, int Capacid_bytes, int Posicion, unsigned char valor_f) {
    valor_f &= 0b111;

    int bit_inicio = Posicion * 3;
    int Posc_byte = bit_inicio / 8;
    int inic_ficha = bit_inicio % 8;


    if (Posc_byte >= Capacid_bytes) return;

    if (inic_ficha <= 5) {

        memory[Posc_byte] &= ~(0b111 << inic_ficha);
        memory[Posc_byte] |= (valor_f << inic_ficha);
    } else {

        int bits_primer_byte = 8 - inic_ficha;
        int bits_segundo_byte = 3 - bits_primer_byte;


        unsigned char mascara1 = (1 << bits_primer_byte) - 1;
        memory[Posc_byte] &= ~(mascara1 << inic_ficha);
        memory[Posc_byte] |= ((valor_f & mascara1) << inic_ficha);


        if (Posc_byte + 1 < Capacid_bytes) {
            unsigned char mascara2 = (1 << bits_segundo_byte) - 1;
            memory[Posc_byte + 1] &= ~mascara2;
            memory[Posc_byte + 1] |= (valor_f >> bits_primer_byte);
        }
    }
}

void limpiar_no_use(unsigned char *memoria, int bytes_reservados, int filas, int columnas) {
    int bits_totales = filas * columnas * 3;
    int bytes_activos = (bits_totales + 7) / 8;
    int bits_validos_ultimo_byte = bits_totales % 8;


    if (bytes_activos > 0 && bits_validos_ultimo_byte != 0) {
        unsigned int mascara_valida = (1 << bits_validos_ultimo_byte) - 1;
        memoria[bytes_activos - 1] &= static_cast<unsigned char>(mascara_valida);
    }

    for (int idx = bytes_activos; idx < bytes_reservados; ++idx) {
        memoria[idx] = 0;
    }
}

