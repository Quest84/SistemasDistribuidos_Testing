#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>
int main (int argc, char *argv[]) {

    /* Variables para almacenar la información */
    int nthreads, tid, procs, maxt, inpar, dynamic, nested;
    /* Inicia la region paralela */
    #pragma omp parallel private(nthreads, tid)    
    {
        /* Obtiene el número de hilos */
        tid = omp_get_thread_num();
        /* Sólo el hilo maestro hace esto */
        if (tid == 0) {
            printf("Thread %d obtener información del entorno...\n", tid);
            /* obtener información del entorno */
            procs = omp_get_num_procs();
            /* obt iene el número de threads */
            nthreads = omp_get_num_threads();
            /* Obtiene el número máximo de threads */ 
            maxt = omp_get_max_threads();
            /* Obtiene cuandos threads trabajan en paralelo */
            inpar = omp_in_parallel();
            /* Obtiene la cantidad de hilos dinámicos habilitados */
            dynamic = omp_get_dynamic();
            /* Devuelve si el paralelismo anidado está habilitado */
            nested = omp_get_nested();
            /* Imprime información del entorno */
            printf("Numero de procesadores = %d\n", procs);
            printf("Numero de hilos = %d\n", nthreads);
            printf("Max Hilos = %d\n", maxt);
            printf("Trabaja en paralelo? = %d\n", inpar);
            printf("Los hilos dinamicos estan habilitados? = %d\n", dynamic);
            printf("Soporta paralelismo? = %d\n", nested);
        }
    }

    return 0;
}
