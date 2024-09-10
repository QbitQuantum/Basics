void *thread_main(void *arg) {
  thread_data_t *td = (thread_data_t*) arg;
  int i;
  int64_t start,total;
#if GASNET_PAR
  gasnet_image_t *imagearray = test_malloc(nodes * sizeof(gasnet_image_t));
  for (i=0; i<nodes; ++i) { imagearray[i] = threads_per_node; }
  gasnet_coll_init(imagearray, td->mythread, NULL, 0, 0);
  test_free(imagearray);
#else
  gasnet_coll_init(NULL, 0, NULL, 0, 0);
#endif


  MYBARRIER();
  if (td->mythread == 0) {
      printf("Running barrier test with %i iterations...\n",iters);
      fflush(stdout);
  }
  
  MYBARRIER();
  
  start = TIME();
  for (i=0; i < iters; i++) {
    gasnet_coll_barrier_notify(GASNET_TEAM_ALL, i, GASNET_BARRIERFLAG_IMAGES);            
    GASNET_Safe(gasnet_coll_barrier_wait(GASNET_TEAM_ALL, i, GASNET_BARRIERFLAG_IMAGES)); 
  }
  total = TIME() - start;

  MYBARRIER();

  if (td->mythread == 0) {
      printf("Total time: %8.3f sec  Avg Named Barrier latency: %8.3f us\n",
        ((float)total)/1000000, ((float)total)/iters);
      fflush(stdout);
  }
  MYBARRIER();

  start = TIME();
  for (i=0; i < iters; i++) {
    gasnet_coll_barrier_notify(GASNET_TEAM_ALL, 0, GASNET_BARRIERFLAG_ANONYMOUS | GASNET_BARRIERFLAG_IMAGES);            
    GASNET_Safe(gasnet_coll_barrier_wait(GASNET_TEAM_ALL, 0, GASNET_BARRIERFLAG_ANONYMOUS | GASNET_BARRIERFLAG_IMAGES)); 
  }
  total = TIME() - start;

  MYBARRIER();

  if (td->mythread == 0) {
      printf("Total time: %8.3f sec  Avg Anon. Barrier latency: %8.3f us\n",
        ((float)total)/1000000, ((float)total)/iters);
      fflush(stdout);
  }

  MYBARRIER();
  
  return NULL;
}