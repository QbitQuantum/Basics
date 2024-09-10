inline void stm_tune_scheduler(){
	TX_GET;
	int m=max_allowed_running_transactions;
	stm_time_t now=STM_TIMER_READ();
	stm_time_t total_tx_wasted_time=0;
	stm_time_t total_tx_time=0;
	stm_time_t total_no_tx_time=0;
	stm_time_t total_tx_spin_time=0;
	memset(conflicts_per_active_transactions, 0, (max_concurrent_threads+1) * sizeof(long));
	memset(committed_per_active_transactions, 0, (max_concurrent_threads+1) * sizeof(long));
	memset(wasted_time_k, 0, (max_concurrent_threads+1) * sizeof(stm_time_t));
	memset(useful_time_k, 0, (max_concurrent_threads+1) * sizeof(stm_time_t));
	long total_committed_transactions_by_collector_threads=0;
	long total_committed_transactions=0;
	long total_aborted_transactions=0;
	float average_running_transactions=0;

	tx->total_no_tx_time+=now - tx->start_no_tx_time ;
	stm_tx_t *thread=_tinystm.threads;
	int i=0;
	while(thread!=NULL){
		total_tx_time+=thread->total_useful_time;
		total_no_tx_time+=thread->total_no_tx_time;
		total_tx_wasted_time+=thread->total_wasted_time;
		total_tx_spin_time+=thread->total_spin_time;
		total_committed_transactions_by_collector_threads+=thread->committed_transactions_as_a_collector_thread;
		total_committed_transactions+=thread->committed_transactions;
		total_aborted_transactions+=thread->aborted_transactions;

		for(i=0;i<max_concurrent_threads+1;i++){
			wasted_time_k[i]+=thread->total_tx_wasted_per_active_transactions[i];
			//printf("\nwasted_time_k[%i] %llu", i, thread->total_tx_wasted_per_active_transactions[i]);
			useful_time_k[i]+=thread->total_tx_useful_per_active_transactions[i];
			committed_per_active_transactions[i]+=thread->total_tx_committed_per_active_transactions[i];
			average_running_transactions+=(float)i * (float) thread->total_tx_committed_per_active_transactions[i];
			conflicts_per_active_transactions[i]+=thread->total_conflict_per_active_transactions[i];
		}
		reset_local_stats(thread);
		thread=thread->next;
	}
	//for(i=0;i<max_concurrent_threads+1;i++) printf("\nwasted_time_k[%i] %llu", i, wasted_time_k[i]);
	//printf("\ntotal_tx_time %llu, total_tx_wasted_time %llu, total_no_tx_time %llu, total_committed_transactions_by_collector_threads %i", total_tx_time, total_tx_wasted_time, total_no_tx_time, total_committed_transactions_by_collector_threads);
	average_running_transactions=average_running_transactions/(float)total_committed_transactions_by_collector_threads;
	float *mu_k=(float*)malloc((max_concurrent_threads+1) * sizeof(float));
	float lambda = 1.0 / (((float) total_no_tx_time/(float)1000000000)/(float) total_committed_transactions_by_collector_threads);
	for (i=0;i<max_concurrent_threads+1;i++){
		if((wasted_time_k[i]>0 || useful_time_k[i]>0) && committed_per_active_transactions[i] > 0){
			mu_k[i]= 1.0 / ((((float) wasted_time_k[i] / (float)1000000000) / (float)committed_per_active_transactions[i]) + (((float) useful_time_k[i]/(float)1000000000) / (float) committed_per_active_transactions[i]));
			//printf("\nk:%i\tmu_k: %f, %llu, %llu, %llu", i, mu_k[i], wasted_time_k[i], useful_time_k[i], committed_per_active_transactions[i]);
		}else{
			mu_k[i]= 1.0 / ((((float)total_tx_wasted_time/(float)1000000000)/(float)total_committed_transactions_by_collector_threads)+(((float)total_tx_time/(float)1000000000) / (float) total_committed_transactions_by_collector_threads));
			//printf("\nk:%i\tmu_k: %f - average", i, mu_k[i]);
		}
	}

	float th = get_throughput(lambda,mu_k,m);
	float th_minus_1=0.0,th_plus_1=0.0,th_minus_2=0.0;
	if(m>3){
		th_minus_1=get_throughput(lambda,mu_k,m-1);
		th_minus_2=get_throughput(lambda,mu_k,m-2);
	}else if(m>2)th_minus_1=get_throughput(lambda,mu_k,m-1);
	if(th_minus_2 >= th && th_minus_2 >= th_minus_1 && m>3) {
		max_allowed_running_transactions-=2;
		//printf("\nSelected th_minus_2");
	}else if(th_minus_1>=th){
		max_allowed_running_transactions--;
		//printf("\nSelected th_minus_1");
	}else if(m<max_concurrent_threads){
		float average_restarted_transactions= (float)conflicts_per_active_transactions[m]/(float)committed_per_active_transactions[m];
		float p_a_k = average_restarted_transactions /(1.0 + average_restarted_transactions);
		float p_a_1 = 1- pow(1-p_a_k,1.0/(double)(m-1));
		float average_restarted_transactions_plus_1 = ((1.0 - pow((1.0 - p_a_1),m))/ pow((1-p_a_1),m));
		float w_m=0.0,u_m=0.0;
		if(conflicts_per_active_transactions[m]>0)
			w_m=((float)wasted_time_k[m]/(float)1000000000)/(float)conflicts_per_active_transactions[m];
		else if(total_aborted_transactions>0)w_m=((float)total_tx_wasted_time/(float)1000000000)/(float)total_aborted_transactions;
		if(committed_per_active_transactions[m]>0)
			u_m = ((float)useful_time_k[m]/(float)1000000000)/(float)committed_per_active_transactions[m];
		else u_m = ((float)total_tx_time/(float)1000000000)/(float)total_committed_transactions_by_collector_threads;
		mu_k[m + 1]= 1.0/((w_m * average_restarted_transactions_plus_1) + u_m );
		th_plus_1 = get_throughput(lambda,mu_k,m + 1);
		if(th_plus_1 > 1.1* th) {
			max_allowed_running_transactions++;
			//printf("\nSelected th_plus_1");
		} else {
			//printf("\nSelected th");
		}
	}//

	tx->start_no_tx_time=STM_TIMER_READ();
	//printf("\nPredicted: %f|%f|%f|%f, measured: %f, max txs: %i", th_minus_2, th_minus_1, th, th_plus_1, (float)total_committed_transactions/((float)(now-last_tuning_time)/(float)1000000000), max_allowed_running_transactions);
	//printf("\tTotal commits: %i (as a collector: %i)",total_committed_transactions, total_committed_transactions_by_collector_threads);
	//printf("\nlambda: %f mu: %f", lambda, 1.0 / ((((float)total_tx_wasted_time/(float)1000000000)/(float)total_committed_transactions_by_collector_threads)+(((float)total_tx_time/(float)1000000000) / (float) total_committed_transactions_by_collector_threads)));
	//printf("\naverage_running_transactions: %f", average_running_transactions, 1.0);
	//fflush(stdout);
	last_tuning_time=STM_TIMER_READ();
}