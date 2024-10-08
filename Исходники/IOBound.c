int main(int argc, char* argv[]){

    int rv;
    int inputFD;
    int outputFD;
    char inputFilename[MAXFILENAMELENGTH];
    char outputFilename[MAXFILENAMELENGTH];
    char outputFilenameBase[MAXFILENAMELENGTH];

    ssize_t transfersize = 0;
    ssize_t blocksize = 0; 
    char* transferBuffer = NULL;
    ssize_t buffersize;

    ssize_t bytesRead = 0;
    ssize_t totalBytesRead = 0;
    int totalReads = 0;
    ssize_t bytesWritten = 0;
    ssize_t totalBytesWritten = 0;
    int totalWrites = 0;
    int inputFileResets = 0;
    int processes;
    
    transfersize = DEFAULT_TRANSFERSIZE;

    blocksize = DEFAULT_BLOCKSIZE;
    
    /* Set default number of processes */
    if(argc < 2){
      processes = 1;
    }
    if(argc > 1){
      	processes = atol(argv[1]);
	if(processes < 1){
	    fprintf(stderr, "Bad number of processes\n");
	    exit(EXIT_FAILURE);
	}
    }
    
    /* Set supplied input filename or default if not supplied */

    if(strnlen(DEFAULT_INPUTFILENAME, MAXFILENAMELENGTH) >= MAXFILENAMELENGTH){
      fprintf(stderr, "Default input filename too long\n");
      exit(EXIT_FAILURE);
    }
    strncpy(inputFilename, DEFAULT_INPUTFILENAME, MAXFILENAMELENGTH);

    /* Set supplied output filename base or default if not supplied */
    if(strnlen(DEFAULT_OUTPUTFILENAMEBASE, MAXFILENAMELENGTH) >= MAXFILENAMELENGTH){
      fprintf(stderr, "Default output filename base too long\n");
      exit(EXIT_FAILURE);
    }
    strncpy(outputFilenameBase, DEFAULT_OUTPUTFILENAMEBASE, MAXFILENAMELENGTH);
    
    /* Confirm blocksize is multiple of and less than transfersize*/
    if(blocksize > transfersize){
	fprintf(stderr, "blocksize can not exceed transfersize\n");
	exit(EXIT_FAILURE);
    }
    if(transfersize % blocksize){
	fprintf(stderr, "blocksize must be multiple of transfersize\n");
	exit(EXIT_FAILURE);
    }

    int pid = forkMe(processes);
    if(pid != 0){
      /* Allocate buffer space */
      buffersize = blocksize;
      if(!(transferBuffer = malloc(buffersize*sizeof(*transferBuffer)))){
	perror("Failed to allocate transfer buffer");
	exit(EXIT_FAILURE);
      }
      
      /* Open Input File Descriptor in Read Only mode */
      if((inputFD = open(inputFilename, O_RDONLY | O_SYNC)) < 0){
	perror("Failed to open input file");
	exit(EXIT_FAILURE);
      }
      
      /* Open Output File Descriptor in Write Only mode with standard permissions*/
      rv = snprintf(outputFilename, MAXFILENAMELENGTH, "%s-%d",
		    outputFilenameBase, getpid());    
      if(rv > MAXFILENAMELENGTH){
	fprintf(stderr, "Output filenmae length exceeds limit of %d characters.\n",
		MAXFILENAMELENGTH);
	exit(EXIT_FAILURE);
      }
      else if(rv < 0){
	perror("Failed to generate output filename");
	exit(EXIT_FAILURE);
      }
      if((outputFD =
	  open(outputFilename,
	       O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
	       S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0){
	perror("Failed to open output file");
	exit(EXIT_FAILURE);
      }
      
      /* Print Status */
      fprintf(stdout, "Reading from %s and writing to %s\n",
	      inputFilename, outputFilename);
      
      /* Read from input file and write to output file*/
      do{
	/* Read transfersize bytes from input file*/
	bytesRead = read(inputFD, transferBuffer, buffersize);
	if(bytesRead < 0){
	  perror("Error reading input file");
	  exit(EXIT_FAILURE);
	}
	else{
	  totalBytesRead += bytesRead;
	  totalReads++;
	}
	
	/* If all bytes were read, write to output file*/
	if(bytesRead == blocksize){
	  bytesWritten = write(outputFD, transferBuffer, bytesRead);
	  if(bytesWritten < 0){
	    perror("Error writing output file");
	    exit(EXIT_FAILURE);
	  }
	  else{
	    totalBytesWritten += bytesWritten;
	    totalWrites++;
	  }
	}
	/* Otherwise assume we have reached the end of the input file and reset */
	else{
	  if(lseek(inputFD, 0, SEEK_SET)){
	    perror("Error resetting to beginning of file");
	    exit(EXIT_FAILURE);
	  }
	  inputFileResets++;
	}
	
      }while(totalBytesWritten < transfersize);
      
      /* Output some possibly helpfull info to make it seem like we were doing stuff */
      fprintf(stdout, "Read:    %zd bytes in %d reads\n",
	      totalBytesRead, totalReads);
      fprintf(stdout, "Written: %zd bytes in %d writes\n",
	      totalBytesWritten, totalWrites);
      fprintf(stdout, "Read input file in %d pass%s\n",
	      (inputFileResets + 1), (inputFileResets ? "es" : ""));
      fprintf(stdout, "Processed %zd bytes in blocks of %zd bytes\n",
	      transfersize, blocksize);
      
      /* Free Buffer */
      free(transferBuffer);
      
      /* Close Output File Descriptor */
      if(close(outputFD)){
	perror("Failed to close output file");
	exit(EXIT_FAILURE);
      }
      
      /* Close Input File Descriptor */
      if(close(inputFD)){
	perror("Failed to close input file");
	exit(EXIT_FAILURE);
      }
    }
    return EXIT_SUCCESS;
}