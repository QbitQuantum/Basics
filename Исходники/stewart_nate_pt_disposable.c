/*
 * Hook into main program.
 */
int main( int argc, char **argv ) {

	/*
	 * Variables used for time and clock
	 */
	time_t startTime, endTime;
	clock_t clockTime;

	int numThreads;
	int i, j;
	if( argc == 4 ) {
		epsilon = atof(argv[1]);
		affectRate = atof(argv[2]);
		numThreads = atoi(argv[3]);
	} else {
		printf("Invalid command line arguments. Please supply all parameters in the below format.\n");
		printf("%s [<epsilon> <affect_rate> <num_threads>]\n", argv[0]);
		return -1;
	}

	/*
	 * Declare the pthreads on the heap
	 */
	pthread_t *threads = malloc(sizeof(pthread_t) * numThreads);
	
	/*
	 * Read the data file into the boxes structure 
	 */
	int numGridBoxes, numRows, numCols;
	scanf("%d %d %d", &numGridBoxes, &numRows, &numCols); // header file
	simpleBox *boxes = malloc(sizeof(simpleBox) * numGridBoxes);
	if(getInput(boxes, numGridBoxes) != 0) { // The rest of the data file
		printf("Failed to read checksum on last line.\n");
		return -1;	
	}
 
	/*
	 * Create the grid and transfer the useful information from the boxes into the grid
	 */
	gridBox *grid = malloc(sizeof(gridBox) * numGridBoxes);
	transferToGrid(grid, boxes, numGridBoxes);

    /*
     * Free the memory of all simple boxes
     */
    for( i = 0; i < numGridBoxes; i++ ) {
        for( j = 0; j < 4; j++) {
			if( boxes[i].nei[j].num > 0 ) {
				free(boxes[i].nei[j].ids);
			}
		}
    }
    free(boxes);
    
	/* 
	 * Compute the max/min temps for initial values
	 */
   	double *newTemps = malloc(sizeof(double) * numGridBoxes);
	double maxTemp, minTemp;
	int iter = 0; // number of iterations
	
	/*
	 * Insert the temps in the grid structure with the newTemps array
	 * Grab the max and min temperatures
	 */
	for( i = 0; i < numGridBoxes; i++) {
		newTemps[i] = grid[i].temp;
	}
	getMinMax(newTemps, numGridBoxes, &maxTemp, &minTemp);

	/*
	 * Construct the storage box for all threads
	 * We will be blocking the gridboxes instead of cyclic distribution.
	 * For example: 
	 * 		Thread 1: compute grid boxes [0 to (numGridBoxes / numThreads)]
	 */
	threadStorage *storage = malloc(sizeof(threadStorage) * numThreads);
	{
		int start;
		int spacing = numGridBoxes / numThreads;
		for( i = 0, start = 0; i < numThreads; i++, start += spacing ) {
			storage[i].id = i;
			storage[i].newTemps = &newTemps[start];
			storage[i].grid = &grid[start];
			storage[i].numGridBoxes = numGridBoxes / numThreads;
		}
		// Very last thread must pick up the remainder if numGridBoxes/numThreads is not an even integer
		storage[numThreads - 1].numGridBoxes += numGridBoxes - (spacing * numThreads);
	}

	/*
     * Time to do the math.
     * Compute the AMR Dissipation to convergence
     */
	time(&startTime);
	clockTime = clock();
	while( (maxTemp - minTemp) > (epsilon * maxTemp) ) {
	
		iter++;
	
		/* 
		 * Spawn off all threads
		 */
		for( i = 0; i < numThreads; i++){
			int errno = pthread_create(&threads[i], NULL, threadEntry, &storage[i]);
			if( errno ) {
				fprintf(stdout, "Iteration %5d | Error creating thread %3d| ERROR: %5d\n", iter, i, errno);
			}
		}

		/* 
		 * Join all threads
		 */
		for( i = 0; i < numThreads; i++){
			int errno = pthread_join(threads[i], NULL);
			if( errno ) {
				fprintf(stdout, "Iteration %5d | Error joining thread %3d| ERROR: %5d\n", iter, i, errno);
			}
		}
		
		// Grab the max and min temperatures 
		getMinMax(newTemps, numGridBoxes, &maxTemp, &minTemp);

		// Update the temps in the grid structure with the newTemps array
		for( i = 0; i < numGridBoxes; i++) {
			grid[i].temp = newTemps[i];
		}

	}

	/*
	 * Stop the timers
	 */
	time(&endTime);
	clockTime = clock() - clockTime;

	printf("*********************************************************************\n");
	printf("Num Threads: %3d\n", numThreads);
	printf("dissipation converged in %d iterations,\n", iter);
	printf("\twith max DSV\t= %lf and min DSV\t= %lf\n", maxTemp, minTemp);
	printf("\taffect rate\t= %lf;\tepsilon\t= %lf\n", affectRate, epsilon);
	printf("\n");
	printf("elapsed convergence loop time\t(clock): %lu\n", clockTime);
	printf("elapsed convergence loop time\t (time): %.f\n", difftime(endTime, startTime));
	printf("*********************************************************************\n");

    /*
     * Free the memory of all grid boxes, the temporary 'newTemps' variable, the threads, and the storage box
     */
    for( i = 0; i < numGridBoxes; i++ ) {
		free(grid[i].neiTemps);
		free(grid[i].neiCD);
    }
    free(grid);
	free(newTemps);
	free(threads);
	free(storage);

	return 0;
}