static inline void free_barrier(
    barrier_t * const bar)
{
  size_t i;
  int volatile * mybar;

  mybar = bar->vec;

  /* check to make sure bar is not in use */
  for (i=0;i<bar->nthreads;++i) {
    while (mybar[i*IDX_OFFSET] != 0) {
      _mm_pause();  
    }
  }

  /* keep the compiler from whining about freeing volatile memory */
  dl_free((void*)bar->vec);
}