#include "random.h"
#include <random>


unsigned char randomFicha()
{
    static std::random_device rd;
    static std::mt19937 mtEngine(rd());
    static std::uniform_int_distribution<int> tileDist(0, 5);

    return static_cast<unsigned char>(tileDist(mtEngine));
}

