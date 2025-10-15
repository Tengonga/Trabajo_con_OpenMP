/*-------------------------------------------------------------------------
CPA: Trabajo1.
Fichero: sumafibonacci.c
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>

// ----------------------------------------------------
// Función iterativa que genera todos los términos de Fibonacci hasta n
void generar_fibonacci(unsigned long long *fib, int n) {
    if (n > 0) fib[0] = 0;
    if (n > 1) fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

// ----------------------------------------------------
// Suma secuencial de los elementos del array
unsigned long long suma_fibonacci_secuencial(unsigned long long *fib, int n) {
    unsigned long long suma = 0;
    for (int i = 0; i < n; i++) {
        suma += fib[i];
    }
    return suma;
}

// ----------------------------------------------------
// Suma paralela de los elementos del array
unsigned long long suma_fibonacci_paralela(unsigned long long *fib, int n) {
    unsigned long long suma = 0;

    //COMPLETAR

    return suma;
}

// ----------------------------------------------------
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

    unsigned long long n = 500000000; // Valor por defecto

    if (argc > 1) {
        n = atoi(argv[1]);
        if (n <= 0) {
            printf("Error: el número de términos debe ser mayor que 0.\n");
            return 1;
        }
    }

    printf("Número de términos de Fibonacci: %llu\n", n);

    unsigned long long *fib = malloc(n * sizeof(unsigned long long));
    if (!fib) {
        fprintf(stderr, "Error al asignar memoria.\n");
        return 1;
    }

    // Generar la secuencia
    double t1 = omp_get_wtime();
    generar_fibonacci(fib, n);
    double t2 = omp_get_wtime();
    printf("Generación completada en %.6f segundos.\n", t2 - t1);

    // Suma secuencial
    t1 = omp_get_wtime();
    unsigned long long suma_seq = suma_fibonacci_secuencial(fib, n);
    t2 = omp_get_wtime();
    printf("[Secuencial] Suma = %llu, tiempo = %.6f segundos\n", suma_seq, t2 - t1);

    // Suma paralela
    t1 = omp_get_wtime();
    unsigned long long suma_par = suma_fibonacci_paralela(fib, n);
    t2 = omp_get_wtime();
    printf("[Paralelo]   Suma = %llu, tiempo = %.6f segundos\n", suma_par, t2 - t1);

    free(fib);

    return 0;
}