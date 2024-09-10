//  Main adapted to use command-line arguments with argument checking
//  NOTE:  defining [0] program name; [1] Number N of components;
//  [2] filename.aaf;
int main(int argumentCount, char *argumentVector[])
{
  //  First check for correct number of arguments
  //  printf("%ld\n",argumentCount);
  if ((argumentCount < 2) || (argumentCount > 3)) {
    usage();
    return 0;
  }
  //  Processing the second argument to be stored as global variable N
  char* Ns = argumentVector[1];
  char* expectedEnd = &Ns[strlen(Ns)];
  char* end = 0;
  long int N = strtoul(Ns, &end, 10);

  //  Testing for correct second argument
  if ((end != expectedEnd) || (N < 1)) {
    printf("The first argument was of the incorrect form. [%s]\n",
           argumentVector[1]);
    usage();
    return 0;
  }

  //  With no second argument, set output filename to CreateSequence<N>.aaf
  if (argumentCount == 2) {
    strncpy(niceFileName, Ns, FILENAME_MAX);
  } else  {
    //  Otherwise output to filename specified in the second argument
    //  NB this case must have argC ==3 from earlier check

    strncpy(niceFileName, argumentVector[2], FILENAME_MAX);
  }
  if (strstr(niceFileName, ".aaf") == 0)
    strcat (niceFileName, ".aaf");

  //  and then carry on...

  // Load the AAF library explicity to catch the common error
  // that the AAF DLL is not in the user's path, otherwise this
  // error looks like an error opening the file.
  //
  HRESULT hr = AAFLoad(0);
  if (!AAFRESULT_SUCCEEDED(hr)) {
    fprintf(stderr, "Error : Failed to load the AAF library, ");
    fprintf(stderr, "check environment variables -\n");
    fprintf(stderr, "  Windows    - $PATH\n");
    fprintf(stderr, "  Unix/Linux - $LD_LIBRARY_PATH\n");
    exit(hr);
  }

  aafWChar FileNameBuffer[MAX];
  mbstowcs(FileNameBuffer, niceFileName, MAX);

  aafWChar * pwFileName = FileNameBuffer;

  //  Give a nice output here too...
  printf("Creating file %s with %ld components.\n", niceFileName, N);
  checkFatal(CreateAAFFile(pwFileName, N));

  // Open the file and gather statistics
  ReadAAFFile(pwFileName);

  return(0);
}