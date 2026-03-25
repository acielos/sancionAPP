cmake_minimum_required(VERSION 4.0)
project(sancionAPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(sancionAPP main.cpp
        GestorSanciones.cpp
        GestorSanciones.h
        tipos.h
)
