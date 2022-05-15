#include <stdio.h>
#include <mpi.h>

/* 
 *  Compilación y ejecución:
 *      mpicc -o bin 1_barriers_sync.c && mpirun -np 2 ./bin 
 *
 * Directivas básicas de MPI:
 *  MPI_Init():
 *      This function initializes the MPI environment. 
 *      It takes in the addresses of the C++ command line 
 *      arguments argc and argv.
 *
 *  MPI_Comm_size():
 *      This function returns the total size of the environment 
 *      via quantity of processes. The function takes in the MPI 
 *      environment, and the memory address of an integer variable.
 *
 *  MPI_Comm_Rank():
 *      This function returns the process id of the processor that 
 *      called the function. The function takes in the MPI environment, 
 *      and the memory address of an integer variable.
 *
 *  MPI_Finalize():
 *      This function cleans up the MPI environment and ends MPI communications.
 *
 *  
 *  Sincronización:
 *      Herramienta escencial para la seguridad de los threads y para asegurar
 *      que ciertas seccioens de código son manejadas en ciertos puntos.
 *      
 *  MPI_Barrier( MPI_Comm comm ):
 *      Es un bloqueador de proesos que mantiene cada proceso a una cierta linea
 *      de código hasta uqe todos los procesos han alcanzado esa línea de código.
 */      

int main( int argc, char** argv ) {

    int process_Rank, size_Of_Cluster;

    // Inicializa el comunicador MPI
    MPI_Init( &argc, &argv );
    // Obtiene la cantidad de procesadores
    MPI_Comm_size( MPI_COMM_WORLD, &size_Of_Cluster );
    // Obtiene el rank de un proceso respectivamente
    MPI_Comm_rank( MPI_COMM_WORLD, &process_Rank );

    for( int i = 0; i < size_Of_Cluster; i++ ) {
        // Condición para asegurar que todos los procesos están sincronizados
        // cuando pasen por el loop
        if( i == process_Rank )
            printf( "Hola desde el proceso %d de %d\n", process_Rank, size_Of_Cluster );
    
    }
    MPI_Finalize();

    return 0;
}
