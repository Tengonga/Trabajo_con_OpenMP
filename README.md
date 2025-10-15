# Práctica 1: Paralelización con OpenMP

## Computación Paralela (CPA) - Curso 2024/25

---

## 📋 Descripción General

Esta práctica consta de **3 sesiones** enfocadas en el aprendizaje de paralelización con OpenMP a través de diferentes problemas computacionales. Cada sesión trabaja con conceptos progresivamente más avanzados de programación paralela.

---

## 🗂️ Estructura de la Práctica

### **Sesión 1: Integración Numérica**
- **Archivos:** `integral.c`
- **Objetivo:** Aprender a compilar programas OpenMP y paralelizar bucles sencillos
- **Concepto:** Cálculo numérico de integrales usando el método de los rectángulos

### **Sesión 2: Procesamiento de Imágenes**
- **Archivos:** `imagenes.c`, `peppers.ppm`, `peppers-1k.ppm`
- **Objetivo:** Implementar filtrado de imágenes en paralelo
- **Concepto:** Aplicar filtros de media ponderada con OpenMP

### **Sesión 3: Números Primos**
- **Archivos:** `primo_grande.c`, `primo_numeros.c`
- **Objetivo:** Implementar algoritmos paralelos con reparto explícito de trabajo
- **Concepto:** Búsqueda y conteo de números primos

---

## 🚀 Configuración Inicial

### Requisitos
- Sistema operativo Linux
- Compilador GCC con soporte OpenMP
- Acceso al cluster **kahan** (para ejecuciones con múltiples cores)
- Escritorio remoto DSIC-LINUX: https://polilabsvpn.upv.es/

### Crear estructura de carpetas
```bash
# Crear carpeta para el código fuente
mkdir -p W/cpa/prac1
cd W/cpa/prac1
```

---

## 📝 Sesión 1: Integración Numérica

### Compilación básica
```bash
gcc -Wall -o integral integral.c -lm
```

### Compilación con OpenMP
```bash
gcc -fopenmp -Wall -o pintegral pintegral.c -lm
```

### Ejecución local
```bash
# Con 4 hilos, usando la variante 1
OMP_NUM_THREADS=4 ./pintegral 1

# Con 500000 rectángulos
OMP_NUM_THREADS=4 ./pintegral 1 500000
```

### Ejecución en el cluster kahan

#### 1. Conectarse al cluster
```bash
ssh -Y -l login@alumno.upv.es kahan.dsic.upv.es
```

#### 2. Preparar directorio de trabajo
```bash
mkdir prac1
cd prac1
gcc -Wall -fopenmp -o pintegral ~/W/cpa/prac1/pintegral.c -lm
```

#### 3. Crear fichero de trabajo (jobopenmp.sh)
```bash
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=5:00
#SBATCH --partition=cpa

OMP_NUM_THREADS=16 ./pintegral 1
```

#### 4. Lanzar trabajo
```bash
sbatch ~/W/cpa/prac1/jobopenmp.sh
```

#### 5. Ver resultados
```bash
cat slurm-620.out  # Donde 620 es el número de trabajo
```

### Conceptos clave
- Directivas `#pragma omp parallel for`
- Cláusulas `private` y `reduction`
- Función `omp_get_wtime()` para medir tiempos
- Función `omp_get_max_threads()` para obtener número de hilos

---

## 🖼️ Sesión 2: Procesamiento de Imágenes

### Compilación
```bash
gcc -fopenmp -Wall -o imagenes imagenes.c -lm
```

### Copiar archivos al cluster
```bash
cp ~/W/cpa/prac1/*.ppm ~/prac1/
```

### Verificar resultados
```bash
# Comparar salida con referencia
cmp peppers-fil.ppm ref.ppm
```

### Estrategia de paralelización
Analizar los 5 bucles anidados:
1. **Bucle de pasos** (externo)
2. **Bucle de filas**
3. **Bucle de columnas**
4. **Bucle de radio por filas**
5. **Bucle de radio por columnas**

Para cada bucle:
- ✅ Analizar dependencias entre iteraciones
- ✅ Determinar variables compartidas/privadas
- ✅ Implementar paralelización
- ✅ Verificar correctitud del resultado
- ✅ Medir tiempos de ejecución

### Recomendaciones
- Empezar con el bucle más interno
- Usar inicialmente 2 hilos para pruebas
- Evitar saturar la cola del cluster
- No usar `reduction` sobre miembros de struct

---

## 🔢 Sesión 3: Números Primos

### Parte 1: Buscar el primo más grande

#### Compilación
```bash
gcc -fopenmp -Wall -o primo_grande primo_grande.c -lm
```

#### Paralelización manual
Reparto cíclico de iteraciones entre hilos:
```c
#pragma omp parallel ...
{
    int id = omp_get_thread_num();
    int nhilos = omp_get_num_threads();
    
    for (i = 3 + 2*id; p && i <= s; i += 2*nhilos)
        if (n % i == 0) p = 0;
}
```

**Nota importante:** Usar `volatile int p;` para evitar problemas de optimización del compilador.

### Parte 2: Contar primos hasta un número grande

#### Estrategias de paralelización
1. **Opción A:** Paralelizar el bucle principal con función `primo()` secuencial
2. **Opción B:** Usar función `primo()` paralela (menos eficiente)

#### Planificaciones a probar
```bash
# Estática sin chunk
schedule(static)

# Estática con chunk 1
schedule(static, 1)

# Dinámica
schedule(dynamic)

# Usando variable de entorno
OMP_SCHEDULE="static,6" ./primo_numeros
```

---

## 📊 Toma de Tiempos

### Plantilla de resultados
```
Tiempo secuencial: _____________

Tiempo de versiones paralelas:
                Version 1    Version 2    ...
2 hilos         _________    _________    ...
8 hilos         _________    _________    ...
32 hilos        _________    _________    ...
```

### Medir tiempos en el código
```c
#include <omp.h>

double t1, t2;
t1 = omp_get_wtime();
// ... código a medir ...
t2 = omp_get_wtime();
printf("Tiempo: %f\n", t2-t1);
```

---

## 🛠️ Comandos Útiles del Cluster

```bash
# Ver estado de la cola
squeue

# Cancelar un trabajo
scancel 620

# Ver contenido de archivo
cat slurm-620.out

# Copiar archivos a W
cp slurm-620.out ~/W/cpa/prac1
```

---

## 📌 Opciones de Compilación

| Opción | Descripción |
|--------|-------------|
| `-fopenmp` | Habilitar soporte OpenMP |
| `-Wall` | Mostrar todas las advertencias |
| `-o archivo` | Especificar nombre del ejecutable |
| `-lm` | Enlazar librería matemática |

---

## ⚠️ Notas Importantes

- **No ejecutar programas largos en el front-end** del cluster, solo para compilar y lanzar trabajos
- Los ejecutables **no deben estar en la carpeta W**, usar `~/prac1`
- El cluster kahan tiene **4 nodos con 64 cores cada uno**
- Usar `#SBATCH --nodes=1` para programas OpenMP (memoria compartida)
- Los resultados de trabajos se guardan en archivos `slurm-JOBID.out`

---

## 🎯 Objetivos de Aprendizaje

- ✅ Compilar y ejecutar programas OpenMP
- ✅ Paralelizar bucles con `parallel for`
- ✅ Usar cláusulas `private`, `shared`, `reduction`
- ✅ Realizar reparto explícito de trabajo entre hilos
- ✅ Medir y analizar tiempos de ejecución
- ✅ Trabajar con el sistema de colas SLURM
- ✅ Comprender diferentes estrategias de planificación

---

## 📚 Recursos Adicionales

- Documentación cluster kahan: Material de la asignatura
- Formato PPM: Visualizar con `irfanview` o `display`
- Benchmarks de imágenes: https://links.uwaterloo.ca/Repository.html

---

## 👥 Soporte

Para dudas sobre el producto Claude o la API de Anthropic, consultar:
- Soporte general: https://support.claude.com
- Documentación API: https://docs.claude.com
