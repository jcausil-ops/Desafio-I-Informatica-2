cmake_minimum_required(VERSION 3.16)

project(Desafio1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio1 main.cpp
    Funciones.h
    Funciones.cpp
    random.cpp
    random.h
)

include(GNUInstallDirs)
install(TARGETS Desafio1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
