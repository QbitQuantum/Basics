double time_force_calc(int default_samples)
{
  int rds = timing_samples > 0 ? timing_samples : default_samples;
  int i;

  if (mpi_integrate(0, 0))
    return -1;

  /* perform force calculation test */
  markTime();
  for (i = 0; i < rds; i++) {
    if (mpi_integrate(0, -1))
      return -1;
  }
  markTime();
  return diffTime()/rds;
}