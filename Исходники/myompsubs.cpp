void lap(int N, double scl, double *vecin, double *vecout){

	// thread variables
	int nthds, tid;

	// compute variables
	int stride, start, stop, ii;

	/* Fork a team of threads giving them their own copies of variables */
	#pragma omp parallel private(nthds, tid, stride, start, stop, ii) shared(N, scl, vecin, vecout)
	{
		// compute thread variables
		nthds = omp_get_num_threads();
		tid = omp_get_thread_num();

		// compute stride
		stride = ceil((long double)N/nthds);

		// compute start and stop
		start = tid*stride;
		stop = (int)fminl((long double)(tid+1)*stride,(long double)N);

		// print info
		//printf("id, stride, start, stop = %d, %10d, %10d, %10d\n",tid,stride,start,stop);

		// multiply vecin by lap and write to vecout
		for(ii=start;ii<stop;ii++){
			if(ii == 0){
				vecout[ii] = (2.0*vecin[ii] - vecin[ii+1])/scl;
			}
			else if(ii == N-1){
				vecout[ii] = (2.0*vecin[ii] - vecin[ii-1])/scl;
			}
			else if(ii < N){
				vecout[ii] = (2.0*vecin[ii] - vecin[ii+1] - vecin[ii-1])/scl;
			}
		}

	}  /* All threads join master thread and disband */

}