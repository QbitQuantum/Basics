int
main(int argc, char **argv)
{
	int i,ps,ps_cnt=2;
	int *target;
	int *source;
	int me, npes, elements=N_ELEMENTS, loops=DFLT_LOOPS;
    char *pgm;
	double start_time, time_taken;

	start_pes(0);
	me = _my_pe();
	npes = _num_pes();

    if ((pgm=strrchr(argv[0],'/')))
        pgm++;
    else
        pgm = argv[0];

    while ((i = getopt (argc, argv, "hve:l:p:s")) != EOF) {
        switch (i)
        {
          case 'v':
              Verbose++;
              break;
          case 'e':
              if ((elements = atoi_scaled(optarg)) <= 0) {
                  fprintf(stderr,"ERR: Bad elements count %d\n",elements);
                  return 1;
              }
              break;
          case 'l':
              if ((loops = atoi_scaled(optarg)) <= 0) {
                  fprintf(stderr,"ERR: Bad loop count %d\n",loops);
                  return 1;
              }
              break;
          case 'p':
              if ((ps_cnt = atoi_scaled(optarg)) <= 0) {
                  fprintf(stderr,"ERR: Bad pSync[] elements %d\n",loops);
                  return 1;
              }
              break;
          case 's':
              Serialize++;
              break;
          case 'h':
              if (me == 0)
                  usage(pgm);
              return 0;
          default:
              if (me == 0) {
                  fprintf(stderr,"%s: unknown switch '-%c'?\n",pgm,i);
                  usage(pgm);
              }
              return 1;
        }
    }

	ps_cnt *= _SHMEM_BCAST_SYNC_SIZE;
	pSync = shmalloc( ps_cnt * sizeof(long) );

	for (i = 0; i < ps_cnt; i++)
	  pSync[i] = _SHMEM_SYNC_VALUE;

	source = (int *) shmalloc( elements * sizeof(*source) );

	target = (int *) shmalloc( elements * sizeof(*target) );
	for (i = 0; i < elements; i += 1) {
	    source[i] = i + 1;
	    target[i] = -90;
	}

    if (me==0 && Verbose)
        fprintf(stderr,"ps_cnt %d loops %d nElems %d\n",
                        ps_cnt,loops,elements);

	shmem_barrier_all();

	for(time_taken = 0.0, ps = i = 0; i < loops; i++) {

	    start_time = shmem_wtime();

	    shmem_broadcast32(target, source, elements, 0, 0, 0, npes, &pSync[ps]);

        if (Serialize) shmem_barrier_all();

	    time_taken += (shmem_wtime() - start_time);

        if (ps_cnt > 1 ) {
	        ps += _SHMEM_BCAST_SYNC_SIZE;
	        if ( ps >= ps_cnt ) ps = 0;
        }
	}

	if(me == 0 && Verbose) {
        printf("%d loops of Broadcast32(%ld bytes) over %d PEs: %7.3f secs\n",
            loops, (elements*sizeof(*source)), npes, time_taken);
        elements = (elements * loops * sizeof(*source)) / (1024*1024);
        printf("  %7.5f secs per broadcast() @ %7.4f MB/sec\n",
               (time_taken/(double)loops), ((double)elements / time_taken) );
    }

    if (Verbose > 1)  fprintf(stderr,"[%d] pre B1\n",me);

	shmem_barrier_all();

    if (Verbose > 1)  fprintf(stderr,"[%d] post B1\n",me);

	shfree(pSync);
	shfree(target);
	shfree(source);

	return 0;
}