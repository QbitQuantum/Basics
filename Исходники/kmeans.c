/*---< main() >-------------------------------------------------------------*/
int setup(int argc, char **argv) {
	int		opt;
	extern char   *optarg;
	char   *filename = 0;
	float  *buf;
	char	line[1024];
	int		isBinaryFile = 0;

	float	threshold = 0.001;		/* default value */
	int		max_nclusters=5;		/* default value */
	int		min_nclusters=5;		/* default value */
	int		best_nclusters = 0;
	int		nfeatures = 0;
	int		npoints = 0;
	float	len;

	float **features;
	float **cluster_centres=NULL;
	int		i, j, index;
	int		nloops = 1;				/* default value */

	int		isRMSE = 0;		
	float	rmse;

	int		isOutput = 0;
	//float	cluster_timing, io_timing;		

	//ocd_init(&argc, &argv, NULL);
	//ocd_options opts = ocd_get_options();
	//platform_id = opts.platform_id;
	//device_id = opts.device_id;

	/* obtain command line arguments and change appropriate options */
	while ( (opt=getopt(argc,argv,"i:t:m:n:l:bro"))!= EOF) {
		switch (opt) {
			case 'i': filename=optarg;
				  break;
			case 'b': isBinaryFile = 1;
				  break;            
			case 't': threshold=atof(optarg);
				  break;
			case 'm': max_nclusters = atoi(optarg);
				  break;
			case 'n': min_nclusters = atoi(optarg);
				  break;
			case 'r': isRMSE = 1;
				  break;
			case 'o': isOutput = 1;
				  break;
			case 'l': nloops = atoi(optarg);
				  break;
			case '?': usage(argv[0]);
				  break;
			default: usage(argv[0]);
				 break;
		}
	}

	if (filename == 0) usage(argv[0]);

	/* ============== I/O begin ==============*/
	/* get nfeatures and npoints */
	//io_timing = omp_get_wtime();
	if (isBinaryFile) {		//Binary file input
		int infile;
		if ((infile = open(filename, O_RDONLY, "0600")) == -1) {
			fprintf(stderr, "Error: no such file (%s)\n", filename);
			exit(1);
		}
		read(infile, &npoints,   sizeof(int));
		read(infile, &nfeatures, sizeof(int));        

		/* allocate space for features[][] and read attributes of all objects */
		buf         = (float*) memalign(AOCL_ALIGNMENT,npoints*nfeatures*sizeof(float));
		features    = (float**)memalign(AOCL_ALIGNMENT,npoints*          sizeof(float*));
		features[0] = (float*) memalign(AOCL_ALIGNMENT,npoints*nfeatures*sizeof(float));
		for (i=1; i<npoints; i++)
			features[i] = features[i-1] + nfeatures;

		read(infile, buf, npoints*nfeatures*sizeof(float));

		close(infile);
	}
	else {
		FILE *infile;
		if ((infile = fopen(filename, "r")) == NULL) {
			fprintf(stderr, "Error: no such file (%s)\n", filename);
			exit(1);
		}		
		while (fgets(line, 1024, infile) != NULL)
			if (strtok(line, " \t\n") != 0)
				npoints++;			
		rewind(infile);
		while (fgets(line, 1024, infile) != NULL) {
			if (strtok(line, " \t\n") != 0) {
				/* ignore the id (first attribute): nfeatures = 1; */
				while (strtok(NULL, " ,\t\n") != NULL) nfeatures++;
				break;
			}
		}        

		/* allocate space for features[] and read attributes of all objects */
		buf         = (float*) memalign(AOCL_ALIGNMENT,npoints*nfeatures*sizeof(float));
		features    = (float**)memalign(AOCL_ALIGNMENT,npoints*          sizeof(float*));
		features[0] = (float*) memalign(AOCL_ALIGNMENT,npoints*nfeatures*sizeof(float));
		for (i=1; i<npoints; i++)
			features[i] = features[i-1] + nfeatures;
		rewind(infile);
		i = 0;
		while (fgets(line, 1024, infile) != NULL) {
			if (strtok(line, " \t\n") == NULL) continue;            
			for (j=0; j<nfeatures; j++) {
				buf[i] = atof(strtok(NULL, " ,\t\n"));             
				i++;
			}            
		}
		fclose(infile);
	}
	//io_timing = omp_get_wtime() - io_timing;

	printf("\nI/O completed\n");
	printf("\nNumber of objects: %d\n", npoints);
	printf("Number of features: %d\n", nfeatures);	
	/* ============== I/O end ==============*/

	// error check for clusters
	if (npoints < min_nclusters)
	{
		printf("Error: min_nclusters(%d) > npoints(%d) -- cannot proceed\n", min_nclusters, npoints);
		exit(0);
	}

	srand(7);												/* seed for future random number generator */	
	memcpy(features[0], buf, npoints*nfeatures*sizeof(float)); /* now features holds 2-dimensional array of features */
	free(buf);

	/* ============ Initialize OpenCL Environment ============ */

	initCL();

	/* ======================= core of the clustering ===================*/

	//cluster_timing = omp_get_wtime();		/* Total clustering time */
	cluster_centres = NULL;
	index = cluster(npoints,				/* number of data points */
			nfeatures,				/* number of features for each point */
			features,				/* array: [npoints][nfeatures] */
			min_nclusters,			/* range of min to max number of clusters */
			max_nclusters,
			threshold,				/* loop termination factor */
			&best_nclusters,			/* return: number between min and max */
			&cluster_centres,		/* return: [best_nclusters][nfeatures] */  
			&rmse,					/* Root Mean Squared Error */
			isRMSE,					/* calculate RMSE */
			nloops);				/* number of iteration for each number of clusters */		

	//cluster_timing = omp_get_wtime() - cluster_timing;
    

	/* =============== Command Line Output =============== */

	/* cluster center coordinates
	   :displayed only for when k=1*/
	if((min_nclusters == max_nclusters) && (isOutput == 1)) {
		printf("\n================= Centroid Coordinates =================\n");
		for(i = 0; i < max_nclusters; i++){
			printf("%d:", i);
			for(j = 0; j < nfeatures; j++){
				printf(" %.2f", cluster_centres[i][j]);
			}
			printf("\n\n");
		}
	}

	len = (float) ((max_nclusters - min_nclusters + 1)*nloops);

    //printf("Number of Iteration: %d\n", nloops);
    //printf("Time for I/O: %.5fsec\n", io_timing);
    //printf("Time for Entire Clustering: %.5fsec\n", cluster_timing);

	if(min_nclusters != max_nclusters){
		if(nloops != 1){									//range of k, multiple iteration
			//printf("Average Clustering Time: %fsec\n",
			//		cluster_timing / len);
			printf("Best number of clusters is %d\n", best_nclusters);				
		}
		else{												//range of k, single iteration
			//printf("Average Clustering Time: %fsec\n",
			//		cluster_timing / len);
			printf("Best number of clusters is %d\n", best_nclusters);				
		}
	}
	else{
		if(nloops != 1){									// single k, multiple iteration
			//printf("Average Clustering Time: %.5fsec\n",
			//		cluster_timing / nloops);
			if(isRMSE)										// if calculated RMSE
				printf("Number of trials to approach the best RMSE of %.3f is %d\n", rmse, index + 1);
		}
		else{												// single k, single iteration				
			if(isRMSE)										// if calculated RMSE
				printf("Root Mean Squared Error: %.3f\n", rmse);
		}
	}


	/* free up memory */
#ifndef __FPGA__
	free(features[0]);
	free(features);    
#endif
	return(0);
}