main(int argc, char *argv[])
{
    int i, j, l;
    int ch;
    extern char *optarg;
    int edge;
    int size;
    int lu_arg[MAX_THREADS][3];
    
    /* ARMCI */
    void **ptr;
    double **ptr_loc;

    THREAD_LOCK_INIT(mutex);
    
    armci_msg_init(&argc,&argv);
    nproc = armci_msg_nproc();
    me = armci_msg_me();
    
    while ((ch = getopt(argc, argv, "n:b:p:t:d:h")) != -1) {
        switch(ch) {
            case 'n': n = atoi(optarg); break;
            case 'b': block_size = atoi(optarg); break;
            case 'p': nproc = atoi(optarg); break;
            case 't': th_per_p = atoi(optarg); break;
            case 'd': d = atoi(optarg); break;
            case 'h': {
                printf("Usage: LU, or \n");
        printf("       LU -nMATRIXSIZE -bBLOCKSIZE -pNPROC -tTH_PER_P\n");
                armci_msg_barrier();
                armci_msg_finalize();
                exit(0);
            } 
        }
    }

    if(th_per_p>MAX_THREADS) {
        th_per_p=MAX_THREADS;
        if(me==0)printf("Warning: cannot run more than %d threads, adjust MAX_THREADS",MAX_THREADS);
    }

    if (d) {
        fprintf(stderr, "%d: %d\n", me, getpid());
        sleep(d);
    }

    nthreads = th_per_p * nproc;
    if(me == 0) {
        printf("\n Blocked Dense LU Factorization\n");
        printf("     %d by %d Matrix\n", n, n);
        printf("     %d Processors\n", nproc);
        printf("     %d thread(s) per processor, %d threads total\n", th_per_p, nthreads);
        printf("     %d by %d Element Blocks\n", block_size, block_size);
        printf("\n");
    }
    
    num_rows = (int) sqrt((double) nthreads);
    for (;;) {
        num_cols = nthreads/num_rows;
        if (num_rows*num_cols == nthreads)
            break;
        num_rows--;
    }
    
    nblocks = n/block_size;
    if (block_size * nblocks != n) {
        nblocks++;
    }
    
    num = (nblocks * nblocks)/nthreads;
    if((num * nthreads) != (nblocks * nblocks))
        num++;

    edge = n%block_size;
    if (edge == 0) {
        edge = block_size;
    }
#ifdef DEBUG
    if(me == 0)
        for (i=0;i<nblocks;i++) {
            for (j=0;j<nblocks;j++) 
                printf("%d ", block_owner(i, j));
            printf("\n");
        }
    armci_msg_barrier();
/*    armci_msg_finalize(); */
/*    exit(0); */
#endif
    
    for (l = 0; l < th_per_p; l++) {
        me_th[l] = me * th_per_p + l;
        for (i=0;i<nblocks;i++) {
            for (j=0;j<nblocks;j++) {
                if(block_owner(i,j) == me_th[l]) {
                    if ((i == nblocks-1) && (j == nblocks-1)) {
                        size = edge*edge;
                    }
                    else if ((i == nblocks-1) || (j == nblocks-1)) {
                        size = edge*block_size;
                    }
                    else {
                        size = block_size*block_size;
                    }
                    thread_doubles[l] += size;
                }
            }
        }
        proc_bytes += thread_doubles[l] * sizeof(double);
    }

    /* initialize ARMCI */
    ARMCI_Init();
    ptr = (void **)malloc(nproc * sizeof(void *));
    ARMCI_Malloc(ptr, proc_bytes);

    a = (double **)malloc(nblocks*nblocks*sizeof(double *));
    if (a == NULL) {
        fprintf(stderr, "Could not malloc memory for a\n");
        exit(-1);
    }
    ptr_loc = (double **)malloc(nthreads*sizeof(double *));
    for (i = 0; i < nproc; i++) {
        ptr_loc[i * th_per_p] = (double *)ptr[i];
        for (j = 1; j < th_per_p; j++)
            ptr_loc[i * th_per_p + j] = ptr_loc[i * th_per_p + j - 1] + thread_doubles[j - 1];
    }
    for(i=0; i<nblocks;i ++) {
        for(j=0; j<nblocks; j++) {
            a[i+j*nblocks] = ptr_loc[block_owner(i, j)];
            if ((i == nblocks-1) && (j == nblocks-1)) {
                size = edge*edge;
            } else if ((i == nblocks-1) || (j == nblocks-1)) {
                size = edge*block_size;
            } else {
                size = block_size*block_size;
            }
            ptr_loc[block_owner(i, j)] += size;
        }
    }
#if 0
    for(i=0; i<nblocks*nblocks;i ++) printf("%d: a[%d]=%p\n", me, i, a[i]);
    fflush(stdout);
#endif
    
    /* initialize the array */
    init_array();
    
    /* barrier to ensure all initialization is done */
    armci_msg_barrier();

    /* to remove cold-start misses, all processors touch their own data */
/*    for (l = 0; l < th_per_p; l++) touch_array(block_size, me_th[l]); */
    armci_msg_barrier();

    if(doprint) {
        if(me == 0) {
            printf("Matrix before LU decomposition\n");
            print_array(me); 
        }
        armci_msg_barrier();
    }

#if 1
    for (i = 0; i < nblocks; i++)
        for (j = 0; j < nblocks; j++)
            print_block_dbg(a[i + j * nblocks], "proc %d, a[%d, %d]:\n", me, i, j);
#endif

    TH_INIT(nproc,th_per_p);

    /* Starting the timer */
    if(me == 0) start_timer();

    for (l = 0; l < th_per_p; l++) {
        lu_arg[l][0] = n;
        lu_arg[l][1] = block_size;
        lu_arg[l][2] = l;
        THREAD_CREATE(threads + l, lu, lu_arg[l]);
    }
    
    for (l = 0; l < th_per_p; l++) THREAD_JOIN(threads[l], NULL);
    armci_msg_barrier();

    /* Timer Stops here */
    if(me == 0) 
        printf("\nRunning time = %lf milliseconds.\n\n",  elapsed_time());

    if(doprint) {        
        if(me == 0) {
            printf("after LU\n");
            print_array(me);
        }
        armci_msg_barrier();
    }
    
    /* done */
    ARMCI_Free(ptr[me]);
    ARMCI_Finalize();
    armci_msg_finalize();

    THREAD_LOCK_DESTROY(mutex);
}