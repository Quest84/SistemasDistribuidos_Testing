#pragma warning(disable : 4996)
#include <mpi.h>
#include <stdio.h>
#define NRA 100      /* number of rows in matrix A */
#define NCA NRA    /* number of columns in matrix A */
#define NCB NRA    /* number of columns in matrix B */
#define MASTER 0   /* taskid of first task */
float a[NRA][NCA]; /* matrix A to be multiplied */
float b[NCA][NCB]; /* matrix B to be multiplied */
float c[NRA][NCB]; /* result matrix C */
int main(int argv, char* argc[])
{
    int size,    /* number of tasks in partition */
    taskid,  /* a task identifier */
    num_row, /*num_row of each task;*/
    i, j, k; /* misc */
    MPI_Status status;
    double startwtime, endwtime;
    MPI_Init(&argv, &argc);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    num_row = NRA / size;
    //init matrix a
    for (i = taskid * num_row; i < (taskid + 1) * num_row; i++)
       for (j = 0; j < NCA; j++)
           a[i][j] = i + j;
    //init matrix b
    for (i = 0; i < NCA; i++)
       for (j = 0; j < NCB; j++)
           b[i][j] = i * j;
    if (taskid == MASTER)
       startwtime = MPI_Wtime(); //begain compute time
    //computed matrix c
    for (k = 0; k < NCB; k++)
       for (i = taskid * num_row; i < (taskid + 1) * num_row; i++)
       {
           c[i][k] = 0.0;
           for (j = 0; j < NCA; j++)
                c[i][k] = c[i][k] + a[i][j] * b[j][k];
        }
    if (taskid > MASTER)
    {
        int row = taskid * num_row;
        MPI_Send(&c[row][0], num_row * NCB, MPI_FLOAT, MASTER, 99,
                 MPI_COMM_WORLD);
    }
    if (taskid == MASTER)
    {
        for (i = size - 1; i >= 1; i--)
        {
            int row = i * num_row;
            MPI_Recv(&c[row][0], num_row * NCB, MPI_FLOAT, i, 99,
                      MPI_COMM_WORLD, &status);
        }
        endwtime = MPI_Wtime(); //end compute time
        printf("wall clock time = %lf\n", endwtime - startwtime);
        for (i = 0; i < NCA; i++)
        {
             for (k = 0; k < NCB; k++)
                printf("c[%d][%d] = %.4f \t", i, k, c[i][k]);
             printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
