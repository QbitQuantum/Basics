void *LLW_train_thread(void *th_data) {

	// Recover data
	struct ThreadData *data =  (struct ThreadData *)th_data;
	const int thread_id = data->thread_id;
	const int nprocs = data->nprocs;	
	struct Model *model = data->model;
	struct KernelCache *kernelcache = data->kernelcache;
	long chunk_size = data->chunk_size;
	const double accuracy = data->accuracy;
	double **gradient = data->gradient;
	double **H_alpha = data->H_alpha;
	double *best_primal_upper_bound = data->best_primal_upper_bound;
	int *activeset = data->activeset;
	long *nb_SV = data->nb_SV;	
	double *lp_rhs = data->lp_rhs;
	FILE *fp = data->logfile_ptr;	
	
	pthread_mutex_unlock(&thread_data_mutex);	// Release thread_data for next thread 
	 
	// Local variables
	int do_eval;
	char yesno;
	long long return_status = -1;	
	
	// Prepare the cache
	struct TrainingCache cache;
	cache.chunk_size =  chunk_size;
	LLW_alloc_memory(&cache, model->Q, model->nb_data, chunk_size);
	cache.kc = kernelcache;
	cache.activeset = activeset;
	cache.lp_rhs = lp_rhs;
	
	double **delta = matrix(chunk_size, model->Q);
	double previous_ratio = 0.0;
	double improvement = 1.0;	
	double theta_opt;
	int jump = false;
			
	if(accuracy == 0)
		do_eval = 0;
	else 
		do_eval = 1;
	
	/*
		Prepare parallel gradient computations:
		- the gradient vector is split into NUMTHREADS_GRAD parts (along i)
		- each part is updated by a different thread
	*/
	// max number of threads for gradient updates is nprocs
	pthread_t *grad_threads = (pthread_t *)malloc(sizeof(pthread_t) * nprocs); 

	// start with 1 thread (main load on kernel evaluations)
	int numthreads_grad = 1;		

	void *status; 			
	int rc; 		
	long k;	
	struct ThreadGradient_data *grad_data = (struct ThreadGradient_data *)malloc(sizeof(struct ThreadGradient_data) * nprocs);


	// Disable parallel gradient computation for small data sets
	int parallel_gradient_update = 1;
	if(model->nb_data < 5000 || nprocs == 1)
		parallel_gradient_update = 0;

	if(parallel_gradient_update) {
		for(k=0;k<nprocs;k++) {
			grad_data[k].gradient = gradient;
			grad_data[k].H_alpha = H_alpha;
			grad_data[k].cache = &cache;
			grad_data[k].model = model;
		}		
		grad_data[0].start_i = 1;
		grad_data[0].end_i = model->nb_data / numthreads_grad;	
		for(k=1;k<numthreads_grad-1;k++) {	
			grad_data[k].start_i = grad_data[k-1].end_i + 1;
			grad_data[k].end_i = grad_data[k].start_i + model->nb_data / numthreads_grad -1;
		}
		if(numthreads_grad>1) {
			grad_data[numthreads_grad-1].start_i = grad_data[numthreads_grad-2].end_i + 1;
			grad_data[numthreads_grad-1].end_i = model->nb_data;
		}	
	}
#ifdef _WIN32
	// Init POOL
	TP_WORK ** work;
	
	if(parallel_gradient_update) {
		
		work = malloc(sizeof(TP_WORK *) * nprocs);
		for(k=0;k<nprocs;k++)
			work[k] = CreateThreadpoolWork(LLW_update_gradient_thread2, (void *) &grad_data[k], NULL);
	}
#endif
		
	// Switch to nprocs/4 threads for gradient update when 25% of the kernel matrix is cached
	int percentage_step = 1;
	long percentage = model->nb_data / 4;
	int next_numthreads_grad = nprocs/4;
	if(next_numthreads_grad == 0) 
		next_numthreads_grad = 1;
	
	// Main loop
	int thread_stop = 0;
	do {	
	  	if((TRAIN_SMALL_STEP < TRAIN_STEP) && (model->iter%TRAIN_SMALL_STEP) == 0) {
		    	printf(".");
			fflush(stdout);
	  	}
	  
 	  	// Select a random chunk of data to optimize 
		select_random_chunk(&cache,model);
				
		// Compute the kernel submatrix for this chunk
  		compute_K(&cache,model);			
  	
		// Enter Critical Section (using and modifying the model)
		pthread_mutex_lock(&(model->mutex)); 
		
		jump = LLW_solve_lp(gradient, &cache, model);
	  	
	  	if(jump == false)
	    		jump = LLW_check_opt_sol(gradient,&cache,model);
	    		
		if(jump == false) {
			
	      	LLW_compute_delta(delta,&cache,model);
	    	theta_opt = LLW_compute_theta_opt(delta, &cache, model);
	    	
	    	if (theta_opt > 0.0) { 
			
				*nb_SV += LLW_compute_new_alpha(theta_opt,&cache,model);
				
				if(parallel_gradient_update) {
				
					// Update gradient in parallel 
		   			for(k=0;k<numthreads_grad;k++) {
					#ifdef _WIN32
						SubmitThreadpoolWork(work[k]);
					#else
						rc = pthread_create(&grad_threads[k], NULL, LLW_update_gradient_thread, (void *) &grad_data[k]);	
					#endif
					}			
					// Wait for gradient computations to terminate
					for(k=0;k<numthreads_grad;k++) {
					#ifdef _WIN32
						WaitForThreadpoolWorkCallbacks(work[k], FALSE);
					#else
						rc = pthread_join(grad_threads[k],&status);
					#endif
					}
				}
				else {
					// old-style non-threaded gradient update (for small data sets)
					LLW_update_gradient(gradient,H_alpha, &cache,model); 
				}
			}
   		}
				    
		if((do_eval && (model->iter%TRAIN_STEP) == 0) || EVAL || STOP || (do_eval && model->ratio >= accuracy) )  
		    {    	   	
			if(fp != NULL)
				fprintf(fp,"%ld ",model->iter);
	
			if(EVAL)
				printf("\n\n*** Evaluating the model at iteration %ld...\n",model->iter);
								 
			// Evaluate how far we are in the optimization
			// (prints more info if interrutped by user)
			previous_ratio = model->ratio;
			model->ratio = MSVM_eval(best_primal_upper_bound, gradient, H_alpha, NULL, model, EVAL, fp);

			print_training_info(*nb_SV, model);
		
			improvement = model->ratio - previous_ratio;			

			if(EVAL) // if interrupted by user (otherwise let the ratio decide if we go on training)
			  {			  	
				printf("\n *** Do you want to continue training ([y]/n)? ");
				yesno = getchar();
				if(yesno=='n') {
					STOP = 1;
				}
				EVAL = 0; // reset interruption trigger
			  }		
		    }
	    
	    	// Release kernel submatrix in cache
		release_K(&cache);
							
		// Check if a sufficient % of the kernel matrix is cached
		if( parallel_gradient_update && cache.kc->max_idx >= percentage ) {	
			// and switch thread to compute gradient upates instead of kernel rows if it is		
			thread_stop = switch_thread(nprocs, &numthreads_grad, &next_numthreads_grad, &percentage,  &percentage_step, grad_data, thread_id, model->nb_data);				
			// (threads are actually stopped to leave the CPUs
			//  to other threads that will compute gradient updates)
		}				
	
  		model->iter++;

		// Release mutex: End of critical section
		pthread_mutex_unlock(&(model->mutex));			
   		
	} while(model->iter <= MSVM_TRAIN_MAXIT && (!do_eval || (model->ratio < accuracy && improvement != 0.0)) && !STOP && !thread_stop);  
 	
  	// Release mutex: End of critical section (see below)
	pthread_mutex_unlock(&(model->mutex));

#ifdef _WIN32
	if(parallel_gradient_update){
		for(k=0;k<numthreads_grad;k++)
			CloseThreadpoolWork(work[k]);
	}	
#endif
  	// compute return_status
	if(do_eval && (model->ratio >= accuracy || improvement==0.0))
		return_status = 0; // optimum reached or no more improvement. 
		
  	// Free memory
	LLW_free_memory(&cache);
	free(delta[1]);free(delta);
	free(grad_threads);
	free(grad_data);
	
	pthread_exit((void*)return_status);
}