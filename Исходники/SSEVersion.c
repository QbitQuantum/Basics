int main(int argc,char *argv[])
{
  const char   *label[4] = {"Copy", "Scale","Add", "Triad"};
  const double bytes[4]  = {2 * sizeof(double) * N,
                            2 * sizeof(double) * N,
                            3 * sizeof(double) * N,
                            3 * sizeof(double) * N};
  double       rmstime[4] = {0},maxtime[4] = {0},mintime[4] = {FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};
  int          quantum;
  int          BytesPerWord,j,k,size;
  PetscInt     node = -1;
  double       scalar, t, times[4][NTIMES];
#if !STATIC_ALLOC
  double       *PETSC_RESTRICT a,*PETSC_RESTRICT b,*PETSC_RESTRICT c;
#endif

  PetscInitialize(&argc,&argv,0,help);
  MPI_Comm_size(PETSC_COMM_WORLD,&size);
  PetscOptionsGetInt(NULL,"-node",&node,NULL);
  /* --- SETUP --- determine precision and check timing --- */

  PetscPrintf(PETSC_COMM_WORLD,HLINE);
  BytesPerWord = sizeof(double);
  PetscPrintf(PETSC_COMM_WORLD,"This system uses %d bytes per DOUBLE PRECISION word.\n",
              BytesPerWord);

  PetscPrintf(PETSC_COMM_WORLD,HLINE);
  PetscPrintf(PETSC_COMM_WORLD,"Array size = %d, Offset = %d\n", N, OFFSET);
  PetscPrintf(PETSC_COMM_WORLD,"Total memory required = %.1f MB per process.\n",
              (3 * N * BytesPerWord) / 1048576.0);
  PetscPrintf(PETSC_COMM_WORLD,"Each test is run %d times, but only\n", NTIMES);
  PetscPrintf(PETSC_COMM_WORLD,"the *best* time for each is used.\n");

  /* Get initial value for system clock. */

#if !STATIC_ALLOC
  if (node == -1) {
    posix_memalign((void**)&a,64,N*sizeof(double));
    posix_memalign((void**)&b,64,N*sizeof(double));
    posix_memalign((void**)&c,64,N*sizeof(double));
  } else if (node == -2) {
    a = malloc(N*sizeof(double));
    b = malloc(N*sizeof(double));
    c = malloc(N*sizeof(double));
#if defined(HAVE_NUMA)
  } else {
    a = numa_alloc_onnode(N*sizeof(double),node);
    b = numa_alloc_onnode(N*sizeof(double),node);
    c = numa_alloc_onnode(N*sizeof(double),node);
#endif
  }
#endif
#if FAULT_TOGETHER
  for (j=0; j<N; j++) {
    a[j] = 1.0;
    b[j] = 2.0;
    c[j] = 0.0;
  }
#else
  for (j=0; j<N; j++) a[j] = 1.0;
  for (j=0; j<N; j++) b[j] = 2.0;
  for (j=0; j<N; j++) c[j] = 0.0;
#endif

  PetscPrintf(PETSC_COMM_WORLD,HLINE);

  if  ((quantum = checktick()) >= 1) PetscPrintf(PETSC_COMM_WORLD,"Your clock granularity/precision appears to be %d microseconds.\n", quantum);
  else PetscPrintf(PETSC_COMM_WORLD,"Your clock granularity appears to be less than one microsecond.\n");

  t = Second();
  for (j = 0; j < N; j++) a[j] = 2.0E0 * a[j];
  t = 1.0E6 * (Second() - t);

  PetscPrintf(PETSC_COMM_WORLD,"Each test below will take on the order"
              " of %d microseconds.\n", (int) t);
  PetscPrintf(PETSC_COMM_WORLD,"   (= %d clock ticks)\n", (int) (t/quantum));
  PetscPrintf(PETSC_COMM_WORLD,"Increase the size of the arrays if this shows that\n");
  PetscPrintf(PETSC_COMM_WORLD,"you are not getting at least 20 clock ticks per test.\n");

  PetscPrintf(PETSC_COMM_WORLD,HLINE);

  PetscPrintf(PETSC_COMM_WORLD,"WARNING -- The above is only a rough guideline.\n");
  PetscPrintf(PETSC_COMM_WORLD,"For best results, please be sure you know the\n");
  PetscPrintf(PETSC_COMM_WORLD,"precision of your system timer.\n");
  PetscPrintf(PETSC_COMM_WORLD,HLINE);

  /* --- MAIN LOOP --- repeat test cases NTIMES times --- */

  scalar = 3.0;
  for (k=0; k<NTIMES; k++) {
    MPI_Barrier(PETSC_COMM_WORLD);
    /* ### COPY: c <- a ### */
    times[0][k] = Second();
    MPI_Barrier(PETSC_COMM_WORLD);
#if USE_MEMCPY
    memcpy(c,a,N*sizeof(double));
#elif SSE2
    for (j=0; j<N; j+=8) {
      _mm_stream_pd(c+j+0,_mm_load_pd(a+j+0));
      _mm_stream_pd(c+j+2,_mm_load_pd(a+j+2));
      _mm_stream_pd(c+j+4,_mm_load_pd(a+j+4));
      _mm_stream_pd(c+j+6,_mm_load_pd(a+j+6));
#  if PREFETCH_NTA
      _mm_prefetch(a+j+64,_MM_HINT_NTA);
#  endif
    }
#else
    for (j=0; j<N; j++) c[j] = a[j];
#endif
    MPI_Barrier(PETSC_COMM_WORLD);
    times[0][k] = Second() - times[0][k];

    /* ### SCALE: b <- scalar * c ### */
    times[1][k] = Second();
    MPI_Barrier(PETSC_COMM_WORLD);
#if SSE2
    {
      __m128d scalar2 = _mm_set1_pd(scalar);
      for (j=0; j<N; j+=8) {
        _mm_stream_pd(b+j+0,_mm_mul_pd(scalar2,_mm_load_pd(c+j+0)));
        _mm_stream_pd(b+j+2,_mm_mul_pd(scalar2,_mm_load_pd(c+j+2)));
        _mm_stream_pd(b+j+4,_mm_mul_pd(scalar2,_mm_load_pd(c+j+4)));
        _mm_stream_pd(b+j+6,_mm_mul_pd(scalar2,_mm_load_pd(c+j+6)));
#  if PREFETCH_NTA
        _mm_prefetch(c+j+64,_MM_HINT_NTA);
#  endif
      }
    }
#else
    for (j=0; j<N; j++) b[j] = scalar*c[j];
#endif
    MPI_Barrier(PETSC_COMM_WORLD);
    times[1][k] = Second() - times[1][k];

    /* ### ADD: c <- a + b ### */
    times[2][k] = Second();
    MPI_Barrier(PETSC_COMM_WORLD);
#if SSE2
    {
      for (j=0; j<N; j+=8) {
        _mm_stream_pd(c+j+0,_mm_add_pd(_mm_load_pd(a+j+0),_mm_load_pd(b+j+0)));
        _mm_stream_pd(c+j+2,_mm_add_pd(_mm_load_pd(a+j+2),_mm_load_pd(b+j+2)));
        _mm_stream_pd(c+j+4,_mm_add_pd(_mm_load_pd(a+j+4),_mm_load_pd(b+j+4)));
        _mm_stream_pd(c+j+6,_mm_add_pd(_mm_load_pd(a+j+6),_mm_load_pd(b+j+6)));
#  if PREFETCH_NTA
        _mm_prefetch(a+j+64,_MM_HINT_NTA);
        _mm_prefetch(b+j+64,_MM_HINT_NTA);
#  endif
      }
    }
#else
    for (j=0; j<N; j++) c[j] = a[j]+b[j];
#endif
    MPI_Barrier(PETSC_COMM_WORLD);
    times[2][k] = Second() - times[2][k];

    /* ### TRIAD: a <- b + scalar * c ### */
    times[3][k] = Second();
    MPI_Barrier(PETSC_COMM_WORLD);
#if SSE2
    {
      __m128d scalar2 = _mm_set1_pd(scalar);
      for (j=0; j<N; j+=8) {
        _mm_stream_pd(a+j+0,_mm_add_pd(_mm_load_pd(b+j+0),_mm_mul_pd(scalar2,_mm_load_pd(c+j+0))));
        _mm_stream_pd(a+j+2,_mm_add_pd(_mm_load_pd(b+j+2),_mm_mul_pd(scalar2,_mm_load_pd(c+j+2))));
        _mm_stream_pd(a+j+4,_mm_add_pd(_mm_load_pd(b+j+4),_mm_mul_pd(scalar2,_mm_load_pd(c+j+4))));
        _mm_stream_pd(a+j+6,_mm_add_pd(_mm_load_pd(b+j+6),_mm_mul_pd(scalar2,_mm_load_pd(c+j+6))));
#  if PREFETCH_NTA
        _mm_prefetch(b+j+64,_MM_HINT_NTA);
        _mm_prefetch(c+j+64,_MM_HINT_NTA);
#  endif
      }
    }
#else
    for (j=0; j<N; j++) a[j] = b[j]+scalar*c[j];
#endif
    MPI_Barrier(PETSC_COMM_WORLD);
    times[3][k] = Second() - times[3][k];
  }

  /* --- SUMMARY --- */

  for (k=0; k<NTIMES; k++)
    for (j=0; j<4; j++) {
      rmstime[j] = rmstime[j] + (times[j][k] * times[j][k]);
      mintime[j] = MIN(mintime[j], times[j][k]);
      maxtime[j] = MAX(maxtime[j], times[j][k]);
    }


  PetscPrintf(PETSC_COMM_WORLD,"%8s:  %11s  %11s  %11s  %11s  %11s\n","Function","Rate (MB/s)","Total (MB/s)","RMS time","Min time","Max time");
  for (j=0; j<4; j++) {
    rmstime[j] = sqrt(rmstime[j]/(double)NTIMES);
    PetscPrintf(PETSC_COMM_WORLD,"%8s: %11.4f  %11.4f  %11.4f  %11.4f  %11.4f\n", label[j], 1.0e-06*bytes[j]/mintime[j], size*1.0e-06*bytes[j]/mintime[j], rmstime[j], mintime[j], maxtime[j]);
  }
  PetscFinalize();
  return 0;
}