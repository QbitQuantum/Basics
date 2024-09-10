unsigned line_length(long long num_steps, double step, int slots) {
  // same as L151, volatile/debug if it doesn't work
  double sum[LINE_LENGTH_SLOTS]
    , computation_times[2][LINE_LENGTH_SLOTS - 1];
  int i, j;

  for(j = 0; j < slots - 1; ++j) {
    #pragma omp parallel num_threads(2)
    {
      double x;
      double clock_time;
    unsigned long long start_clock, stop_clock;
    
    start_clock = __rdtsc();
  

      int id = omp_get_thread_num()
        , slot = id + j;
      sum[slot] = 0.0;
      for (i = 0; i < num_steps; ++i) {
        x = (i + .5) * step;
    
        sum[slot] += 4.0 / (1. + x * x);
      }
      sum[slot] *= step;

    stop_clock = __rdtsc();
    clock_time = (double)(stop_clock - start_clock) / (3 * BILLION);
      computation_times[id][j] = clock_time; // (double)(stop.tv_sec - start.tv_sec) + (double)(stop.tv_usec - start.tv_usec) / MILLION;
    }
  printf("\n%d", j);
  for(i = 0; i < 2; ++i) {
      printf("\t%f", computation_times[i][j]);
    }
  }
  printf("\n");

  double avg = 0.0;
  for(j = 0; j < slots - 1; ++j) {
    computation_times[0][j] += computation_times[1][j];
    avg += computation_times[0][j];
  }
  avg /= slots - 1;

  int marker = 0;
  for(j = 0; j < slots - 1; ++j) {
    if(computation_times[0][j] / avg < 0.8) {
      if (marker > slots / 4) {
      return j - marker;
      }
      marker = j;
    }
  }

  return 0;
}