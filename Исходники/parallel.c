int main(int argc, char **argv)
{
  double wall_start = MPI_Wtime();
  Real *diag, **b, **bt, **z;
  Real pi, h, omp_local_max, local_max, global_max;
  int i, j, omp_id;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  omp_tot_threads = omp_get_max_threads();

  /* the total number of grid points in each spatial direction is (n+1) */
  /* the total number of degrees-of-freedom in each spatial direction is (n-1) */
  /* this version requires n to be a power of 2 */

  if (argc < 2) {
    if (mpi_rank == 0){
      printf("need a problem size\n");
    }
    MPI_Finalize();
    return 0;
  }

  n  = atoi(argv[1]);
  m  = n-1;
  // mpi_work is the amount of work needed to be done by each mpi node. The last
  // mpi node may do slightly less work than the others, but that's the closest
  // we'll get to proper load balancing.
  mpi_work = 1 + ((m - 1) / mpi_size);
  nn = 4*n;

  diag = createRealArray (m);
  b    = createReal2DArray (mpi_work, mpi_size*mpi_work);
  bt   = createReal2DArray (mpi_work, mpi_size*mpi_work);
  z    = createReal2DArray (omp_tot_threads, nn);

  h    = 1./(Real)n;
  pi   = 4.*atan(1.);
  
  #pragma omp parallel for private(i)
  for (i=0; i < m; i++) {
    diag[i] = 2.*(1.-cos((i+1)*pi/(Real)n));
  }

  #pragma omp parallel for private(j, i)
  for (j=0; j < mpi_work; j++) { // MPI
    for (i=0; j + mpi_work * mpi_rank < m && i < m; i++) { // OMP
      b[j][i] = h*h;
    }
  }

  #pragma omp parallel for private(omp_id, i)
  for (j=0; j < mpi_work; j++) { // MPI cut + OMP
    omp_id = omp_get_thread_num();
    fst_(b[j], &n, z[omp_id], &nn);
  }
  
  transpose (bt,b);

  #pragma omp parallel for private(i, omp_id) schedule(static)
  for (i=0; i < mpi_work; i++) { // MPI cut + OMP
    omp_id = omp_get_thread_num();
    fstinv_(bt[i], &n, z[omp_id], &nn);
  }

  #pragma omp parallel for private(j, i)
  for (j=0; j < mpi_work; j++) { // MPI
    for (i=0; i < m; i++) {
      bt[j][i] = bt[j][i]/(diag[i]+diag[j + mpi_work * mpi_rank]);
    }
  }

  #pragma omp parallel for private(i, omp_id) schedule(static)
  for (i=0; i < mpi_work; i++) { // MPI cut + OMP
    omp_id = omp_get_thread_num();
    fst_(bt[i], &n, z[omp_id], &nn);
  }

  transpose (b,bt);

  #pragma omp parallel for private(j, omp_id)
  for (j=0; j < mpi_work; j++) { // MPI cut + OMP
    omp_id = omp_get_thread_num();
    fstinv_(b[j], &n, z[omp_id], &nn);
  }

  local_max = 0.0;
  omp_local_max = 0.0;

  #pragma omp parallel shared(local_max) private(j,i) firstprivate(omp_local_max)
  {
    // MPI, work in range (and handle last node overflow)
    #pragma omp for nowait
    for (j=0; j < mpi_work; j++) {
      for (i=0; j + mpi_work * mpi_rank < m && i < m; i++) {
        if (b[j][i] > omp_local_max) omp_local_max = b[j][i];
      }
    }
    #pragma omp critical
    {
      if (omp_local_max > local_max) {
        local_max = omp_local_max;
      }
    }
  }

  MPI_Reduce(&local_max, &global_max, 1,
             MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
               
  free(diag);
  free(b[0]);
  free(b);
  free(bt[0]);
  free(bt);
  free(z[0]);
  free(z);
  MPI_Finalize();
  
  double wall_end = MPI_Wtime();

  if (mpi_rank == 0) {
    printf (" umax = %e, time = %.3fs \n", global_max,wall_end-wall_start);
    printf(" mpi_size = %d, omp_max_threads = %d, n = %d\n", mpi_size, omp_tot_threads, n);
  }
}