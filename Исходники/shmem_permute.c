void _PERM_IR(_permmap* const pm) {
  const int one = 1;
  int * rindbase;
  int * lindbase;
  int * const restrict lsize = (int *)shmalloc(_PROCESSORS * sizeof(int));
  int * const restrict rsize = (int *)shmalloc(_PROCESSORS * sizeof(int));
  int * restrict * const restrict lind = pm->lind;
  int * restrict * const restrict rind = pm->rind;
  char * restrict * const restrict rptr = pm->rptr;
  int * const restrict rflag = pm->rflag;
  int* addr;
  int i, j;

  for (i = 0; i < _PROCESSORS; i++) {
    lsize[i] = lind[i] ? lind[i][0] : 0;
    rsize[i] = 0;
  }
  shmem_barrier_all();
  for (i = (_INDEX == _PROCESSORS - 1) ? 0 : _INDEX+1;
       i != _INDEX;
       i = (i == _PROCESSORS - 1) ? 0 : i++) {
    if (lsize[i] > 0) {
#ifdef _SHMEM_PERMUTE_DEBUG
      printf("%d sending count to %d\n", _INDEX, i);
  fflush(stdout);
#endif
      shmem_int_put(&(rsize[_INDEX]), &(lsize[i]), 1, i);
    }
  }
  rsize[_INDEX] = lsize[_INDEX];
  shmem_barrier_all();
#ifdef _SHMEM_PERMUTE_DEBUG
  sleep(_PROCESSORS);
#endif
  _PERM_CleanIndices(lsize, rsize, lind, rind, &lindbase, &rindbase);

#ifdef _SHMEM_PERMUTE_DEBUG
  sleep(_INDEX);
  printf("FROM PROCESSOR %d\n", _INDEX);
  printf("  LSIZE = ");
  for (i = 0; i < _PROCESSORS; i++) {
    printf("%d ", lsize[i]);
  }
  printf("\n");
  printf("  RSIZE = ");
  for (i = 0; i < _PROCESSORS; i++) {
    printf("%d ", rsize[i]);
  }
  printf("\n");

  printf("  PROCMAP: size = %d, # elts = %d, encoded = %d :: ", pm->procmap[0], pm->procmap[1], pm->procmap[2]);
   for (j = 3; j < pm->procmap[0]; j++) {
    printf("%d ", pm->procmap[j]);
  }
  printf("\n");
  for (i = 0; i < _PROCESSORS; i++) {
    if (lind[i] != 0) {
      printf("  TO PROCESSOR %d: ", i);
      printf("size = %d, # elts = %d, encoded = %d :: ", lind[i][0], lind[i][1], lind[i][2]);
      for (j = 3; j < lind[i][0]; j++) {
	printf("%d ", lind[i][j]);
      }
      printf("\n");
    }
  }
  printf("\n");
  fflush(stdout);
  sleep(_PROCESSORS-_INDEX);
#endif

  for (i = (_INDEX == _PROCESSORS - 1) ? 0 : _INDEX+1;
       i != _INDEX;
       i = (i == _PROCESSORS - 1) ? 0 : i++) {
    if (rsize[i] > 0) {
#ifdef _SHMEM_PERMUTE_DEBUG
      printf("%d sending rind address to %d\n", _INDEX, i);
  fflush(stdout);
#endif
      rflag[_INDEX] = 0;
      shmem_put((void*)&(rptr[_INDEX]), (void*)&(rind[i]), 1, i);
    }
  }
#ifdef _SHMEM_PERMUTE_DEBUG
  sleep(_PROCESSORS);
#endif
  for (i = (_INDEX == 0) ? _PROCESSORS-1 : _INDEX-1;
       i != _INDEX;
       i = (i == 0) ? _PROCESSORS-1 : i--) {
    if (lsize[i] > 0) {
#ifdef _SHMEM_PERMUTE_DEBUG
      printf("%d waiting for rind address from %d, sending lind\n", _INDEX, i);
  fflush(stdout);
#endif
      shmem_wait((long*)&(rptr[i]), 0);
      addr = (int*)rptr[i];
      rptr[i] = 0;
      shmem_int_put(addr, lind[i], lsize[i], i);
    }
  }
#ifdef _SHMEM_PERMUTE_DEBUG
  sleep(_PROCESSORS);
#endif
  shmem_fence();
  for (i = (_INDEX == 0) ? _PROCESSORS-1 : _INDEX-1;
       i != _INDEX;
       i = (i == 0) ? _PROCESSORS-1 : i--) {
    if (lsize[i] > 0) {
#ifdef _SHMEM_PERMUTE_DEBUG
      printf("IR %d sending one to %d\n", _INDEX, i);
  fflush(stdout);
#endif
      shmem_int_put(&(rflag[_INDEX]), &one, 1, i);
    }
  }
  if (lsize[_INDEX] > 0) {
    memcpy(rind[_INDEX], lind[_INDEX], lsize[_INDEX]*sizeof(int));
  }
  pm->lindbase = lindbase;
  pm->rindbase = rindbase;
  shfree(lsize);
  shfree(rsize);
}