int
max_to_all(int me, int npes)
{
    int i, j, pass=0;

    memset(ok,0,sizeof(ok));

    for (i = 0; i < N; i++) {
        src0[i] = src1[i] = src2[i] = src3[i] = src4[i] = src5[i] = src6[i]
            = me + i;
    }
    shmem_barrier_all();

    shmem_short_max_to_all(     dst0, src0, N, 0, 0, npes, pWrk0, pSync);
    shmem_int_max_to_all(       dst1, src1, N, 0, 0, npes, pWrk1, pSync1);
    shmem_long_max_to_all(      dst2, src2, N, 0, 0, npes, pWrk2, pSync);
    shmem_float_max_to_all(     dst3, src3, N, 0, 0, npes, pWrk3, pSync1);
    shmem_double_max_to_all(    dst4, src4, N, 0, 0, npes, pWrk4, pSync);
    shmem_longdouble_max_to_all(dst5, src5, N, 0, 0, npes, pWrk5, pSync1);
    shmem_longlong_max_to_all(  dst6, src6, N, 0, 0, npes, pWrk6, pSync);
  
    if (me == 0) {
	    for (i = 0,j=-1; i < N; i++,j++) {
	      if(dst0[i] != npes+j) ok[0] = 1;
		  if(dst1[i] != npes+j) ok[1] = 1;
		  if(dst2[i] != npes+j) ok[2] = 1;
		  if(dst3[i] != npes+j) ok[3] = 1;
		  if(dst4[i] != npes+j) ok[4] = 1;
		  if(dst5[i] != npes+j) ok[5] = 1;
		  if(dst6[i] != npes+j) ok[6] = 1;
	    }

	    if(ok[0]==1){
	        printf("Reduction operation shmem_short_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_short_max_to_all: Passed\n");
            pass++;
		}
		if(ok[1]==1){
	        printf("Reduction operation shmem_int_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_int_max_to_all: Passed\n");
            pass++;
		}
		if(ok[2]==1){
	        printf("Reduction operation shmem_long_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_long_max_to_all: Passed\n");
            pass++;
		}
		if(ok[3]==1){
	        printf("Reduction operation shmem_float_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_float_max_to_all: Passed\n");
            pass++;
		}
		if(ok[4]==1){
	        printf("Reduction operation shmem_double_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_double_max_to_all: Passed\n");
            pass++;
		}
		if(ok[5]==1){
	      printf("Reduction operation shmem_longdouble_max_to_all: Failed\n");
		}  
	    else{
	       Vprintf("Reduction operation shmem_longdouble_max_to_all: Passed\n");
           pass++;
		}
		if(ok[6]==1){
	        printf("Reduction operation shmem_longlong_max_to_all: Failed\n");
		}  
	    else{
	        Vprintf("Reduction operation shmem_longlong_max_to_all: Passed\n");
            pass++;
		}
		Vprintf("\n");
    }
    if (Serialize) shmem_barrier_all();

    return (pass == 7 ? 1 : 0);
}