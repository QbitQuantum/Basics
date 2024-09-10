int main(int argc, char *argv[])
{
    int i = 0, rank, size;
    int skip, numprocs;
    static double avg_time = 0.0, max_time = 0.0, min_time = 0.0;
    static double latency = 0.0;
    int64_t t_start = 0, t_stop = 0, timer=0;
    char *buffer=NULL;
    int max_msg_size = 1048576, full = 0;
    int t;

    for ( t = 0; t < _SHMEM_BCAST_SYNC_SIZE; t += 1) pSyncBcast1[t] = _SHMEM_SYNC_VALUE;
    for ( t = 0; t < _SHMEM_BCAST_SYNC_SIZE; t += 1) pSyncBcast2[t] = _SHMEM_SYNC_VALUE;
    for ( t = 0; t < _SHMEM_REDUCE_SYNC_SIZE; t += 1) pSyncRed1[t] = _SHMEM_SYNC_VALUE;
    for ( t = 0; t < _SHMEM_REDUCE_SYNC_SIZE; t += 1) pSyncRed2[t] = _SHMEM_SYNC_VALUE;

    start_pes(0);
    rank = _my_pe();
    numprocs = _num_pes();

    if (process_args(argc, argv, rank, &max_msg_size, &full)) {
        return 0;
    }
    
    if(numprocs < 2) {
        if(rank == 0) {
            fprintf(stderr, "This test requires at least two processes\n");
        }
        return -1;
    }
    print_header(rank, full);

    buffer = shmalloc(max_msg_size * sizeof(char));
    if(NULL == buffer) {
        fprintf(stderr, "malloc failed.\n");
        exit(1);
    }
    
    memset(buffer,1, max_msg_size);

    for(size=1; size <=max_msg_size/sizeof(uint32_t); size *= 2) {
        if(size > LARGE_MESSAGE_SIZE) {
            skip = SKIP_LARGE;
            iterations = iterations_large;
        }
        else {
            skip = SKIP;
        }

        timer=0;        
        for(i=0; i < iterations + skip ; i++) {
            t_start = TIME();
            if(i%2)
                shmem_broadcast32(buffer, buffer, size, 0, 0, 0, numprocs, pSyncBcast1);
            else
                shmem_broadcast32(buffer, buffer, size, 0, 0, 0, numprocs, pSyncBcast2);
            t_stop = TIME();

            if(i>=skip){
                timer+=t_stop-t_start;
            } 
            shmem_barrier_all();
        }
        shmem_barrier_all();            
        latency = (1.0 * timer) / iterations;

        shmem_double_min_to_all(&min_time, &latency, 1, 0, 0, numprocs, pWrk1, pSyncRed1);
        shmem_double_max_to_all(&max_time, &latency, 1, 0, 0, numprocs, pWrk2, pSyncRed2);
        shmem_double_sum_to_all(&avg_time, &latency, 1, 0, 0, numprocs, pWrk1, pSyncRed1);
        avg_time = avg_time/numprocs;

        print_data(rank, full, size*sizeof(uint32_t), avg_time, min_time, max_time, iterations);
    }

    shfree(buffer);  
    return EXIT_SUCCESS;
}