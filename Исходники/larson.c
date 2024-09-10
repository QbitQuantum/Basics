void runthreads(long sleep_cnt, int min_threads, int max_threads, int chperthread, int num_rounds)
{
  thread_data  de_area[MAX_THREADS] ;
  int           nperthread ;
  int           sum_threads ;
  int           sum_allocs ;
  int           sum_frees ;
  double        duration ;
  long ticks_per_sec ;
  long start_cnt, end_cnt ;
  _int64        ticks ;
  double        rate_1=0, rate_n ;
  double        reqd_space ;
  ptrdiff_t     used_space ;
  int           prevthreads ;
  int           i ;

  QueryPerformanceFrequency( &ticks_per_sec ) ;

  memset(&de_area[0], 0, sizeof(thread_data)) ;

  prevthreads = 0 ;
  for(num_threads=min_threads; num_threads <= max_threads; num_threads++ )
    {

      warmup(&blkp[prevthreads*chperthread], (num_threads-prevthreads)*chperthread );

      nperthread = chperthread ;
      stopflag   = FALSE ;
		
      for(i=0; i< num_threads; i++){
	de_area[i].threadno    = i+1 ;
	de_area[i].NumBlocks   = num_rounds*nperthread;
	de_area[i].array       = &blkp[i*nperthread] ;
	de_area[i].blksize     = &blksize[i*nperthread] ;
	de_area[i].asize       = nperthread ;
	de_area[i].min_size    = min_size ;
	de_area[i].max_size    = max_size ;
	de_area[i].seed        = lran2(&rgen) ; ;
	de_area[i].finished    = 0 ;
	de_area[i].cAllocs     = 0 ;
	de_area[i].cFrees      = 0 ;
	de_area[i].cThreads    = 0 ;
	de_area[i].finished    = FALSE ;
	lran2_init(&de_area[i].rgen, de_area[i].seed) ;

	_beginthread(exercise_heap, 0, &de_area[i]) ;  

      }

      QueryPerformanceCounter( &start_cnt) ;

      //printf ("Sleeping for %ld seconds.\n", sleep_cnt);
      Sleep(sleep_cnt * 1000L) ;
      stopflag = TRUE ;

      for(i=0; i<num_threads; i++){
	while( !de_area[i].finished ){
		sched_yield();
	}
      }


      QueryPerformanceCounter( &end_cnt) ;

      sum_frees = sum_allocs =0  ;
      sum_threads = 0 ;
      for(i=0;i< num_threads; i++){
	sum_allocs    += de_area[i].cAllocs ;
	sum_frees     += de_area[i].cFrees ;
	sum_threads   += de_area[i].cThreads ;
	printf("area %d: %d allocs, %d threads\n",i,de_area[i].cAllocs,de_area[i].cThreads);
	de_area[i].cAllocs = de_area[i].cFrees = 0;
      }

 
      ticks = end_cnt - start_cnt ;
     duration = (double)ticks/ticks_per_sec ;

      for( i=0; i<num_threads; i++){
	if( !de_area[i].finished )
	  printf("Thread at %d not finished\n", i) ;
      }


      rate_n = sum_allocs/duration ;
      if( rate_1 == 0){
	rate_1 = rate_n ;
      }
		
      reqd_space = (0.5*(min_size+max_size)*num_threads*chperthread) ;
      used_space = mem_usage();
      
      printf ("Throughput = %8.0f operations per second.\n", sum_allocs / duration);
      printf ("Memory used = %ld bytes, required %.0lf, ratio %lf\n",used_space,reqd_space,used_space/reqd_space);

#if 0
      printf("%2d ", num_threads ) ;
      printf("%6.3f", duration  ) ;
      printf("%6.3f", rate_n/rate_1 ) ;
      printf("%8.0f", sum_allocs/duration ) ;
      printf(" %6.3f %.3f", (double)used_space/(1024*1024), used_space/reqd_space) ;
      printf("\n") ;
#endif

      Sleep(5000L) ; // wait 5 sec for old threads to die

      prevthreads = num_threads ;

      printf ("Done sleeping...\n");

    }
}