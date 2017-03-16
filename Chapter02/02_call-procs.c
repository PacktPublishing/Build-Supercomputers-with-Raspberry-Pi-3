#include <stdio.h> 
#include <mpi.h>   

int main(int argc, char** argv)
{
  /* MPI Variables */
  int  num_processes;
  int  curr_rank;
  char proc_name[MPI_MAX_PROCESSOR_NAME];
  int  proc_name_len;

  /* Initialize MPI */
  MPI_Init(&argc, &argv);

  /* acquire number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

  /* acquire rank of the current process */
  MPI_Comm_rank(MPI_COMM_WORLD, &curr_rank);

  /* acquire processor name for the current thread */
  MPI_Get_processor_name(proc_name, &proc_name_len);

  /* output rank , no of processes, and process name */
  printf("Calling process %d out of %d on %s\r\n", curr_rank, num_processes, proc_name);

  /* clean up, done with MPI */
  MPI_Finalize();

  return 0;
}
