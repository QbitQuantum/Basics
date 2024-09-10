void * worker(void * args)
{
	workerargs* wargs = (workerargs*) args;

	int start = wargs->start;
	int end = wargs->end;
	double dampener = wargs->dampener;
	double constant = wargs->constant;

	// double * curr_scores = wargs->curr_scores;
	// double * prev_scores = wargs->prev_scores;
	// int * index_edge = wargs->index_edge;

	// int * page_inlinks = wargs->page_inlinks;
	// int * inlinks = wargs->inlinks;
	// double * outlinks = wargs->outlinks;

	for (;;) /* Calculates the curr_score as many times as it needs */
	{
		int edge;

		if ((start < g_npages) && (g_nedges > 0)) //padding test
			edge = index_edge[start]; /* for edge count */

		/* Swap */
		// double* tmp = prev_scores;
		// prev_scores = curr_scores;
		// curr_scores = tmp;

		double thread_conv = 0.0;

		for (int i = start; i < end; ++i) /* Calculation for each page */
		{
			if (i >= g_npages)
				break; 

			double sum = 0.0;

			for (int j = 0; j < page_inlinks[i]; ++j) /* Calculation for each inlink */
			{
				sum += prev_scores[inlinks[edge]] * outlinks[edge];
				//printf("<%d: %f = %f * %f>\n", i, prev_scores[inlinks[edge]] / outlinks[edge], prev_scores[inlinks[edge]], outlinks[edge]);
				++edge;
			}

			curr_scores[i] = constant + dampener * sum;

			/* Non-SSE calculation of tread_convergence */
			//thread_conv += (curr_scores[i] - prev_scores[i])*(curr_scores[i] - prev_scores[i]);
			//printf("Thread %d: %f\n", wargs->i, thread_conv);
			
			/* SSE Calculation of tread convergence */
			//Go to line 104
		}

		/* AVX version */
		int nblocks = (end - start) * 0.25;
		// printf("<thread: %d> <nblocks: %d> <start: %d> <end: %d>\n", wargs->i, nblocks, start, end);
		for (int i = 0; i < nblocks; i++)
		{
			__m256d* curr_block = (__m256d*) &curr_scores[start]; // Cast it instead. 
			__m256d* prev_block = (__m256d*) &prev_scores[start];

			__m256d m1 = _mm256_sub_pd(curr_block[i], prev_block[i]);
			__m256d m2 = _mm256_mul_pd(m1, m1);

			thread_conv += m2[0] + m2[1] + m2[2] + m2[3];
		}

		g_sumDiff[wargs->i] = thread_conv; /* Putting the tread_conv so that the main thread can read it. */
		// wargs->curr_scores = curr_scores; /* This is just calibrating the curr_scores for the main thread */

		pthread_barrier_wait(&score_barrier); /* Inform that the score is done calculating everything for this run */
		
		/* Put manager function here (if I want one thread to work as a manager as well */
		/* if (wargs->i == 0) //manager thread */

		pthread_barrier_wait(&conv_barrier); /* Wait until converge calculation is complete */

		if (g_hasConverged)
		{
			break;
		}
	}

	return NULL;
}