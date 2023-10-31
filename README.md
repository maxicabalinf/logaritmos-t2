# logaritmos-t2
## Compilación
Este proyecto usa CMake para compilar sus ejecutables. Puede correr el siguiente comando desde la raíz del proyecto para generar los ejecutables:
    
    # shell
    cmake -B build -S ./; cmake --build build

## Componentes del proyecto
* `stats`: Implementa el cálculo de estadísticas para una muestra de experimentos.
* `sorting`: Funciones de ordenamiento
* `comparison`: Ejecuta el experimento para comparar Radix sort con Quicksort