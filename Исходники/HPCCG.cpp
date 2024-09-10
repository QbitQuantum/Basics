int
compute_residual(const int n, const double * const v1, const double * const v2,
    double * const residual)
{
  double local_residual = 0.0;
  PERFLOG(compute_residual,IN(n));
  for (int i = 0; i < n; i++)
  {
    double diff = fabs(v1[i] - v2[i]);
    if (diff > local_residual)
      local_residual = diff;
  }
#ifdef USING_SSTMAC
  // a little compute modeling
  SSTMAC_compute_loop(0, n, 2/3.0/1.5);
#endif


  PERFSTOP(compute_residual,IN(n));
  // Use MPI's reduce function to collect all partial sums

  double global_residual = 0;


  MPI_Allreduce(&local_residual, &global_residual, 1, MPI_DOUBLE, MPI_SUM,
      MPI_COMM_WORLD);
  *residual = global_residual;


  return (0);
}