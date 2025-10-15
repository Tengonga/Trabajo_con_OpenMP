/*-------------------------------------------------------------------------
CPA: Trabajo1.
Fichero: jacobi.c
-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>

#define MAX_ITERS 100

// Genera la matriz y el vector
void generar_sistema(double **A, double *b, int n) {
    srand(0);

    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = rand() / (double)RAND_MAX;
                suma += fabs(A[i][j]);
            } else {
                A[i][j] = 0.0;
            }
        }
        A[i][i] = suma + 1.0;
        b[i] = rand() / (double)RAND_MAX;
    }
}

// Método de Jacobi
void jacobi(double **A, double *b, double *x, int n) {
    double x_new[n];

    for (int iter = 0; iter < MAX_ITERS; iter++) {
        for (int i = 0; i < n; i++) {
            double suma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    suma += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - suma) / A[i][i];
        }

        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
        }
    }
}

// Método de Jacobi paralelo
void jacobi_paralelo(double **A, double *b, double *x, int n) {
    double x_new[n];

    //COMPLETAR
}

// Programa principal
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

    unsigned long long n = 10000; // Valor por defecto
    if (argc > 1) {
        n = strtoull(argv[1], NULL, 10);
    }

    printf("Límite: %llu\n", n);

    double **A = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
    }
    double *b = malloc(n * sizeof(double *));
    double *x = malloc(n * sizeof(double *));

    generar_sistema(A, b, n);
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    double start = omp_get_wtime();
    jacobi(A, b, x, n);
    double end = omp_get_wtime();

    printf("Tiempo de ejecución: %.2f segundos\n", end - start);
    printf("x[0] = %.6f, x[n-1] = %.6f\n", x[0], x[n-1]);

    for (int i = 0; i < n; i++) {
	x[i] = 0.0;
    }

    start = omp_get_wtime();
    jacobi_paralelo(A, b, x, n);
    end = omp_get_wtime();

    printf("Tiempo de ejecución: %.2f segundos\n", end - start);
    printf("x[0] = %.6f, x[n-1] = %.6f\n", x[0], x[n-1]);

    return 0;
}