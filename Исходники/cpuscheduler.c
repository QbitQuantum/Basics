int main(){
	Queue *ready_queue;
	Queue *FCFS_queue, *RR_queue, *MRR_queue, *MHRR_queue;
	Queue *FCFS_pool, *RR_pool, *MRR_pool, *MHRR_pool;
	ready_queue = createQueue(MAX_SIZE_QUEUE);

	createJobPool();
	int i = 0;
	FILE *f;
	f = fopen("job_pool.txt", "r");

	// Copy the job pool data into another queue for each scheduling
    	// method and copy the queue of elements into another queue for
    	// each scheduling method
	printf("%s\n", "Generating jobs.");
    	FCFS_pool = createQueue(JOB_POOL_SIZE);
    	RR_pool = createQueue(JOB_POOL_SIZE);
    	MRR_pool = createQueue(JOB_POOL_SIZE);
    	MHRR_pool = createQueue(JOB_POOL_SIZE);

    	FCFS_queue = createQueue(MAX_SIZE_QUEUE);
    	RR_queue = createQueue(MAX_SIZE_QUEUE);
    	MRR_queue = createQueue(MAX_SIZE_QUEUE);
    	MHRR_queue = createQueue(MAX_SIZE_QUEUE);

    	for (i = 0; i < JOB_POOL_SIZE; i++){
    	    int quanta;
    	    fscanf(f, "%i", &quanta);
    	    enqueue(FCFS_pool, quanta);
    	    enqueue(RR_pool, quanta);
    	    enqueue(MRR_pool, quanta);
    	    enqueue(MHRR_pool, quanta);
    	}
	
    	// Transfer jobs to reach the steady state.
	printf("%s\n", "Transferring elements to reach the steady state.");
    	transfer(FCFS_queue, FCFS_pool, STEADY_STATE);
    	transfer(RR_queue, RR_pool, STEADY_STATE);
    	transfer(MRR_queue, MRR_pool, STEADY_STATE);
    	transfer(MHRR_queue, MHRR_pool, STEADY_STATE);
	
	srand(time(NULL));
	
    	// Now run each of the processes on the same exact data
	printf("%s\n", "Starting FCFS.");
    	FCFS(FCFS_queue, FCFS_pool);
	printf("%s\n", "Starting Round Robin");
    	RoundRobin(RR_queue, RR_pool);
	printf("%s\n", "Starting Modified Round Robin");
    	ModifiedRoundRobin(MRR_queue, MRR_pool);
	printf("%s\n", "Modified Half Round Robin");
    	ModifiedHalfedRoundRobin(MHRR_queue, MHRR_pool);

	printf("%s\n", "Freeing allocated memory.");
	// Free all allocated memory
	free(ready_queue);
	free(FCFS_queue);
	free(RR_queue);
	free(MRR_queue);
	free(MHRR_queue);
	free(FCFS_pool);
	free(RR_pool);
	free(MRR_pool);
	free(MHRR_pool);
	
	return 0;
}