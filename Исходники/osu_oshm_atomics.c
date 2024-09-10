double
benchmark_inc_longlong (struct pe_vars v, union data_types *buffer,
                        unsigned long iterations)
{
    int64_t begin, end; 
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * drand48(), sizeof(union data_types
                [ITERATIONS]));

    shmem_barrier_all();

    if (v.me < v.pairs) {
        begin = TIME();
        for (i = 0; i < iterations; i++) {
            shmem_longlong_inc(&(buffer[i].longlong_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    shmem_double_sum_to_all(&sum_rate, &rate, 1, 0, 0, v.npes, pwrk1, psync1);
    shmem_double_sum_to_all(&sum_lat, &lat, 1, 0, 0, v.npes, pwrk2, psync2);
    print_operation_rate(v.me, "shmem_longlong_inc", sum_rate/1e6, sum_lat/v.pairs);

    return 0;
}