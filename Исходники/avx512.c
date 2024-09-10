void * avx512_fma(void *args_in)
{
    /* Thread input */
    struct thread_args *args;

    const int n_avx512 = VFMAPS_LATENCY;
    const __m512 add0 = _mm512_set1_ps((float) 1e-6);
    const __m512 mul0 = _mm512_set1_ps((float) (1. + 1e-6));
    __m512 r[n_avx512];

    // Declare as volatile to prevent removal during optimisation
    volatile float result;

    long r_max, i;
    int j;
    double runtime, flops;
    Stopwatch *t;

    /* Read inputs */
    args = (struct thread_args *) args_in;

    t = stopwatch_create(args->timer_type);

    for (j = 0; j < n_avx512; j++) {
        r[j] = _mm512_set1_ps((float) j);
    }

    /* Add over registers r0-r4, multiply over r5-r9, and rely on pipelining,
     * OOO execution, and latency difference (3 vs 5 cycles) for 2x FLOPs
     */

    runtime_flag = 0;
    r_max = 1;
    do {
        pthread_barrier_wait(&timer_barrier);
        t->start(t);
        for (i = 0; i < r_max; i++) {
            #pragma unroll(n_avx512)
            for (j = 0; j < n_avx512; j++)
                r[j] = _mm512_fmadd_ps(r[j], mul0, add0);
        }
        t->stop(t);
        runtime = t->runtime(t);

        /* Set runtime flag if any thread exceeds runtime limit */
        if (runtime > args->min_runtime) {
            pthread_mutex_lock(&runtime_mutex);
            runtime_flag = 1;
            pthread_mutex_unlock(&runtime_mutex);
        }

        pthread_barrier_wait(&timer_barrier);
        if (!runtime_flag) r_max *= 2;

    } while (!runtime_flag);

    /* In order to prevent removal of the prior loop by optimisers,
     * sum the register values and save the result as volatile. */

    for (j = 0; j < n_avx512; j++)
        r[0] = _mm512_add_ps(r[0], r[j]);
    result = reduce_AVX512(r[0]);

    /* (iter) * (16 instr / reg) * (2 flops / instr) * (n_avx512 reg / iter) */
    flops = r_max * 16 * 2 * n_avx512 / runtime;

    /* Cleanup */
    t->destroy(t);

    /* Thread output */
    args->runtime = runtime;
    args->flops = flops;
    args->bw_load = 0.;
    args->bw_store = 0.;

    pthread_exit(NULL);
}