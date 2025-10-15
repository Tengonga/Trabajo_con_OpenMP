/*-------------------------------------------------------------------------
CPA: Trabajo1.
Fichero: cuadradoperfecto.c
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>

// ---------------------------------------------
// Función que determina si un número es cuadrado perfecto
int es_cuadrado(unsigned long long n) {
    unsigned long long r = sqrt(n);
    return r * r == n;
}

// ---------------------------------------------
// Versión secuencial: mayor cuadrado perfecto menor que límite
unsigned long long cuadrado_grande(unsigned long long limite) {
    for (unsigned long long i = limite; i >= 1; i--) {
        if (es_cuadrado(i)) {
            return i;
        }
    }
    return 0;
}

// ---------------------------------------------
// Versión paralela: mayor cuadrado perfecto menor límite
unsigned long long cuadrado_grande_paralelo(unsigned long long limite) {
    //COMPLETAR
    return resultado;
}



// ---------------------------------------------
// Versión secuencial: contar cuadrados perfectos hasta límite
unsigned long long contar_cuadrados(unsigned long long limite) {
    unsigned long long count = 0;
    for (unsigned long long i = 1; i <= limite; i++) {
        if (es_cuadrado(i)) {
            count++;
        }
    }
    return count;
}

// ---------------------------------------------
// Versión paralela: contar cuadrados perfectos usando OpenMP
unsigned long long contar_cuadrados_paralelo(unsigned long long limite) {
    unsigned long long count = 0;

    //COMPLETAR
    return count;
}

// ---------------------------------------------
// Función principal
int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fecha_hora[30];
    strftime(fecha_hora, sizeof(fecha_hora), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Fecha y hora: %s\n", fecha_hora);

    const char *usuario = getlogin();
    if (usuario && strlen(usuario) > 0) {
        printf("Usuario: %s\n", usuario);
    } else {
        usuario = getenv("USER");
        printf("Usuario: %s\n", usuario);
    }

    unsigned long long limite = 100000000; // Valor por defecto
    if (argc > 1) {
        limite = strtoull(argv[1], NULL, 10);
    }

    printf("Límite: %llu\n", limite);

    // -------------------- Pruebas secuenciales
    double t1 = omp_get_wtime();
    unsigned long long res1 = cuadrado_grande(limite);
    double t2 = omp_get_wtime();
    printf("[Secuencial] Mayor cuadrado perfecto menor o igual a %llu: %llu (%.6f s)\n", limite, res1, t2 - t1);

    t1 = omp_get_wtime();
    unsigned long long count1 = contar_cuadrados(limite);
    t2 = omp_get_wtime();
    printf("[Secuencial] Cantidad de cuadrados perfectos: %llu (%.3f s)\n", count1, t2 - t1);

    // -------------------- Pruebas paralelas
    t1 = omp_get_wtime();
    unsigned long long res2 = cuadrado_grande_paralelo(limite);
    t2 = omp_get_wtime();
    printf("[Paralelo]   Mayor cuadrado perfecto menor o igual a %llu: %llu (%.6f s)\n", limite, res2, t2 - t1);

    t1 = omp_get_wtime();
    unsigned long long count2 = contar_cuadrados_paralelo(limite);
    t2 = omp_get_wtime();
    printf("[Paralelo]   Cantidad de cuadrados perfectos: %llu (%.3f s)\n", count2, t2 - t1);

    return 0;
}