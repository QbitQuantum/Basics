    unsigned int ReadSeedFile( void ) {
	FILE *seedfp = NULL;
	int i, io_state, n = peNum;
	unsigned int *iseed, seed; 

	// Check we have actually been initialised:
	if( !Is_Initialised ) CommsInit();

#ifdef MPISCU_DEBUG
	fprintf_all(logFile,"MPISCU::ReadSeedFile: Opening seed file %s.\n", seedFileName);
#endif

	// Create the seeds buffer:
	iseed = new unsigned int[n+1];
    
	// Open the file:
	seedfp = Fopen(seedFileName, "r" );
	if( seedfp == NULL ) 
	    RaiseError("SCUReadSeedFile: could not open seed file!\n");
    
	// Read in n seeds:
	i = 0; while( i < n && fscanf(seedfp,"%u",&(iseed[i])) != EOF ) i++;
    
	// Close the file:
	Fclose(seedfp); seedfp = NULL;
    
	// Die if the file ended before all seeds had been read in:
	if( i < n )
	    RaiseError("SCUReadSeedFile: not enough seeds have been supplied in the seed file!");
	// XXX, EXTREME warning.  This killed one thread and then hung.
    
	// Get the seed which belongs to this PE:
	seed = iseed[peRank];

	// Delete the seeds buffer:
	delete [] iseed;

	// Return this PE's seed:
	return seed;
    }