cmake_minimum_required(VERSION 3.29)
project(Trabajo_con_OpenMP C)

set(CMAKE_C_STANDARD 11)

add_executable(Trabajo_con_OpenMP
    src/cuadradoperfecto.c
    src/jacobi.c
    src/sumafibonacci.c
        src/Pintegral.c
        src/integral.c
        src/imagenes.c)
