/** Main program: copies a file.
    @param argc Number of command-line arguments (including program name).
    @param argv Array of pointers to character arays holding arguments.
    @return 0 if successful, 1 if fail.
*/
int main(int argc, char* argv[]) {  
  char** infilenames; // Names of files.
  char* outfilename;
  int fileCount;
  int returnstatus;
  int paramIndex;
  char method;
  int bufferSize;
  int i; //An iterator
  struct timeval tcpstart;
  struct timeval tcpfinish;

  if (argc < 3) {
    usage(argv[0]); // Must have at least 3 arguments
    return 1;
  }

  //search for copy type
  if ((paramIndex = searchArrayForString(argv,argc,"-c")) != -1) {
    if (paramIndex+1 == argc) {
      printf("Missing parameter. Program terminated.\n");
      return 1;
    }
    method = atoi(argv[paramIndex+1]);
    if (method != 1 && method != 2 && method != 3) {
      printf("Invalid copymethod argument. Valid options are 1, 2, or 3. You entered \"%s\". Program Terminated.\n",argv[paramIndex+1]);
      return 1;
    }
  } else {
    method = 3; //set default method
  }

  //Set buffer size
  if (method == 3) {
    if ((paramIndex = searchArrayForString(argv,argc,"-b")) != -1) {
      if (paramIndex+1 == argc) {
	printf("Missing parameter. Program terminated.\n");
	return 1;
      }
      bufferSize = atoi(argv[paramIndex+1]);
      if (bufferSize <= 0) {
	printf("Invalid buffer Size. Program terminatred\n");
	return 1;
      }
    } else {
      bufferSize = 1024; //set default buffer size
    }
  }

  //find file names
  if ((paramIndex = findFirstFile(argv,argc)) == -1) {
    printf("No file names entered. Program Terminated.\n");
    return 1;
  }
  if ((fileCount = countInputFiles(argv,argc)) < 1) {
    printf("At least two file names or locations must be specified. Program terminated\n");
    return 1;
  }
  infilenames = (char**) malloc(sizeof(char*)*fileCount); //Make space for a list of the files to copy
  //Fill an array of files to copy
  for (i = 0; i < fileCount; i++) {
    infilenames[i] = argv[paramIndex + i];
  }
  outfilename = argv[paramIndex + fileCount];
 
  //Copy the files based on the current method
  gettimeofday(&tcpstart,NULL);
  switch(method) {
  case 1:
    returnstatus = copyfile1(infilenames, outfilename, fileCount);
    break;
  case 2:
    returnstatus = copyfile2(infilenames, outfilename, fileCount);
    break;
  case 3:
    returnstatus = copyfile3(infilenames, outfilename, fileCount, bufferSize);
    break; 
  }
  gettimeofday(&tcpfinish,NULL);

  struct timeval* tcpDifference =  timeDifference(&tcpstart, &tcpfinish);

  if (!returnstatus) {
    printf("\nCopy started: %d seconds and %d microseconds from UTC start.\n",tcpstart.tv_sec,tcpstart.tv_usec);
    printf("Copy finished: %d seconds and %d microseconds from UTC start.\n",tcpfinish.tv_sec,tcpfinish.tv_usec);
    printf("Time for Copy: %d seconds and %d microseconds.\n",tcpDifference->tv_sec,tcpDifference->tv_usec);
  }

  free(tcpDifference);
  free(infilenames);
  return returnstatus;
}