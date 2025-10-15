# Trabajo_con_OpenMP
# Computación Paralela (CPA)
## Trabajo práctico 1: Paralelización con OpenMP
### Curso 2025/26

## Índice
1. [Introducción](#1-introducción)
2. [Ejercicio 1: Memoria de los ejercicios de prácticas](#2-ejercicio-1-memoria-de-los-ejercicios-de-prácticas)
3. [Ejercicio 2: Método de Jacobi](#3-ejercicio-2-método-de-jacobi)
4. [Ejercicio 3: Suma de números de Fibonacci menores que un valor dado](#4-ejercicio-3-suma-de-números-de-fibonacci-menores-que-un-valor-dado)
5. [Ejercicio 4: Suma de los cuadrados perfectos existentes hasta un número dado](#5-ejercicio-4-suma-de-los-cuadrados-perfectos-existentes-hasta-un-número-dado)
6. [Instrucciones de realización](#6-instrucciones-de-realización)

---

## 1. Introducción

El objetivo de este trabajo, además de documentar las tareas realizadas en las sesiones de prácticas, consiste en aplicar técnicas de computación paralela utilizando OpenMP sobre varios problemas clásicos.

Se valorará especialmente la originalidad en el enfoque de la solución, la exhaustividad y claridad en las explicaciones proporcionadas, así como la aportación de evidencias que demuestren el trabajo realizado (como comentarios en el código, salidas de prueba, análisis de resultados, o comparativas de rendimiento en versiones secuencial y paralela).

**Nota:** el código fuente necesario para la realización del trabajo se encuentra disponible en PoliformaT.

---

## 2. Ejercicio 1: Memoria de los ejercicios de prácticas

Realizar una memoria del trabajo realizado en la práctica 1 (incluyendo las tres sesiones). Se debe documentar todo el proceso realizado, con explicaciones, comandos utilizados, código fuente y capturas de la salida proporcionada por los distintos programas (tanto en las ejecuciones en el cluster como en las ejecuciones fuera del mismo).

---

## 3. Ejercicio 2: Método de Jacobi

El programa implementa el método iterativo de Jacobi para aproximar la solución del sistema lineal de ecuaciones **A · x = b**, donde A es una matriz cuadrada de tamaño N × N, x es el vector incógnita y b es el vector de términos independientes.

La matriz A se genera aleatoriamente de forma que sea diagonalmente dominante, lo cual es una condición necesaria para favorecer la convergencia del método. El vector b también se rellena con valores aleatorios, mientras que el vector x se inicializa con ceros.

Al finalizar todas las iteraciones, el programa muestra el tiempo total de ejecución, la cantidad de iteraciones realizadas y algunos valores del vector x como referencia.

### 3.1. Código fuente

**Implementación secuencial del método de Jacobi con iteraciones fijas:**
```c
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
```

**Implementación paralela del método de Jacobi (a completar):**
```c
void jacobi_paralela(double **A, double *b, double *x, int n) {
    double x_new[n];
    
    // COMPLETAR
}
```

### 3.2. Tareas a realizar

Las siguientes tareas deben ser documentadas exhaustivamente en la memoria de la práctica, tanto mediante texto como mediante capturas, redactando al final una conclusión sobre el ejercicio.

1. Completar la versión paralela del algoritmo.
2. Ejecutar el algoritmo en kahan para N = 1000, N = 5000 y N = 10000; y 1, 2, 4, 8 y 16 hilos. Elaborar tres gráficas (una para cada tamaño de N) comparando los tiempos obtenidos, y redactar una breve explicación de los resultados.

---

## 4. Ejercicio 3: Suma de números de Fibonacci menores que un valor dado

### 4.1. La secuencia de Fibonacci

La secuencia de Fibonacci se define de la siguiente manera:
```
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2) para n ≥ 2
```

### 4.2. Planteamiento del problema

Este ejercicio consiste en calcular la suma de los primeros n términos de la sucesión de Fibonacci, donde el valor de n puede ser definido por el usuario. Para ello, se plantea un enfoque en dos etapas: primero se generan todos los términos de la sucesión y se almacenan en un array, y posteriormente se realiza la suma de dichos valores.

A diferencia de otros problemas que requieren detener el proceso al alcanzar un valor límite, en este caso se conoce de antemano el número exacto de elementos que deben procesarse. Esto nos permite diseñar un esquema de paralelización más sencillo y eficiente, ya que no es necesario realizar comprobaciones dinámicas ni establecer condiciones de parada dentro del bucle.

### 4.3. Código fuente

**Generación de los primeros n términos de Fibonacci:**
```c
void generar_fibonacci(unsigned long long *fib, int n) {
    if (n > 0) fib[0] = 0;
    if (n > 1) fib[1] = 1;
    
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}
```

**Suma secuencial de los elementos del array:**
```c
unsigned long long suma_fibonacci_secuencial(unsigned long long *fib, int n) {
    unsigned long long suma = 0;
    for (int i = 0; i < n; i++) {
        suma += fib[i];
    }
    return suma;
}
```

**Suma paralela (a completar):**
```c
unsigned long long suma_fibonacci_paralela(unsigned long long *fib, int n) {
    unsigned long long suma = 0;
    
    // COMPLETAR
    
    return suma;
}
```

### 4.4. Tareas a realizar

Las siguientes tareas deben ser documentadas exhaustivamente en la memoria de la práctica, tanto mediante texto como mediante capturas, redactando al final una conclusión sobre el ejercicio.

1. Completar la versión paralela del algoritmo.
2. Ejecutar el algoritmo en kahan para n = 1000000000, n = 10000 y 4 hilos. ¿Qué conclusión obtienes de la comparación de tiempos para ambos tamaños de n?
3. Para n = 1000000000, probar distintas planificaciones: static, dynamic con al menos 3 tamaños de chunk.
4. Utilizando la planificación óptima obtenida en el apartado anterior, ejecutar la versión paralela en kahan para n = 2000000000 y distinto número de hilos (1, 2, 4, 8, 16). Elaborar una gráfica comparando los tiempos obtenidos, y redactar una breve explicación de los resultados.
5. ¿Con qué dificultades te encontrarías si quisieses paralelizar la función `generar_fibonacci()`?

---

## 5. Ejercicio 4: Suma de los cuadrados perfectos existentes hasta un número dado

### 5.1. Cuadrado perfecto

Un número es cuadrado perfecto si tiene una raíz cuadrada exacta entera. Ejemplo:

- 1 (raíz: 1)
- 4 (raíz: 2)
- 9 (raíz: 3)
- 16 (raíz: 4)
- 25 (raíz: 5), etc.

### 5.2. Planteamiento del problema

Este ejercicio consiste en encontrar el mayor número cuadrado perfecto estrictamente menor que un valor límite proporcionado por el usuario, así como contar cuántos cuadrados perfectos existen en el rango desde 1 hasta dicho límite.

En primer lugar, dado un número entero positivo límite, se desea contar cuántos números enteros entre 1 y límite (ambos inclusive) son cuadrados perfectos. Un número es cuadrado perfecto si existe un número entero cuya raíz cuadrada exacta es igual a dicho número.

En segundo lugar, dado un número entero positivo límite, se desea encontrar el mayor número cuadrado perfecto estrictamente menor que límite. Como se explica anteriormente, un número es cuadrado perfecto si existe un número entero cuya raíz cuadrada exacta es igual a dicho número.

### 5.3. Código fuente

**Función que determina si un número es cuadrado perfecto:**
```c
int es_cuadrado(unsigned long long n) {
    unsigned long long r = sqrt(n);
    return r * r == n;
}
```

**Función secuencial que cuenta cuántos números son cuadrados perfectos:**
```c
unsigned long long contar_cuadrados(unsigned long long limite) {
    unsigned long long count = 0;
    for (unsigned long long i = 1; i <= limite; i++) {
        if (es_cuadrado(i)) {
            count++;
        }
    }
    return count;
}
```

**Versión paralela incompleta para contar cuadrados perfectos:**
```c
unsigned long long contar_cuadrados_paralelo(unsigned long long limite) {
    unsigned long long count = 0;
    
    // COMPLETAR
    return count;
}
```

**Función secuencial que busca el mayor cuadrado perfecto:**
```c
unsigned long long cuadrado_grande(unsigned long long limite) {
    for (unsigned long long i = limite; i >= 1; i--) {
        if (es_cuadrado(i)) {
            return i;
        }
    }
    return 0;
}
```

**Versión paralela para encontrar el mayor cuadrado perfecto (a completar):**
```c
unsigned long long cuadrado_grande_paralelo(unsigned long long limite) {
    // COMPLETAR
    return 0;
}
```

### 5.4. Tareas a realizar

Las siguientes tareas deben ser documentadas exhaustivamente en la memoria de la práctica, tanto mediante texto como mediante capturas, redactando al final una conclusión sobre el ejercicio.

1. Completar la versión paralela del algoritmo que cuenta el número de cuadrados perfectos que se pueden encontrar desde 1 hasta un límite.
2. Completar la versión paralela del algoritmo que busca el mayor cuadrado perfecto menor que un determinado límite.
3. Ejecutar ambos algoritmos en kahan para n = 100000000 y 4 hilos.
4. Para `contar_cuadrados_paralelo()` probar distintas planificaciones: static, dynamic con al menos 3 tamaños de chunk.
5. Compara los resultados obtenidos de la versión paralela con la secuencial de `contar_cuadrados`, ¿qué algoritmo es más rápido? ¿por qué?

---

## 6. Instrucciones de realización

**IMPORTANTE.** Para la realización del trabajo deben tenerse en cuenta las siguientes instrucciones:

- Los trabajos se realizarán en grupos de dos personas. Indicar ambos nombres en la portada.
- Deben entregarse como máximo en la fecha indicada en PoliformaT.
- El formato de entrega de la memoria será PDF obligatoriamente.
- El código fuente que se solicita en algunos apartados debe incluirse en la memoria.
- Se deben incluir capturas de pantalla de todas las ejecuciones de los algoritmos, es decir, capturar la salida en pantalla (no simplemente copiar el contenido de la salida).
- La función principal de los ficheros de código fuente no debe modificarse a no ser que sea estrictamente necesario, justificando en la memoria las modificaciones realizadas.
- Además, debe explicarse explícitamente lo que se pide en cada uno de los apartados.
- El trabajo es propio de cada grupo, no se permite la aportación de capturas de pantalla y/o explicaciones entre distintos grupos.
