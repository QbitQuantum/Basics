int main(int argc, char **argv)
{
    int  infile,outfile,i,rc;
    long inBytes,outBytes;
    long numFiles;
    int  memNameLen;
    char *memNamePtr;
    int  opt;
    char tempfileName[L_tmpnam];
    char linkerString[2000];
    char *linkerPath;
    char inputFileName[1024];       // input file name
    long inLen;                     // input file len
    char *memDataPtr;               // pointer to data area
    char *fileDataPtr;              // pointer to file data
    long  fileOffset;               // current offset to file data
    int   currentArg = 0;
    FILE *inNamefile = NULL;
    memFSdata_t *memFSDataPtr;      // pointer to memFS data structure
    struct stat fileStat;

    int  fileOpt = 0;
    int  done = 0;
    int  verbose = 0;
    int   currentFiles = 0;
    char *listPtr=NULL;
    char *outFilePtr = NULL;
    char *imageInFilePtr = NULL;
    char fileName[] = "cnkmemfs.elf";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (2 > argc) {
       printf("%s requires at least 1 input argument\n",argv[0]);
       usage(argv[0]);
       exit(-1);
    }

    opterr = 0;
    while ((opt = getopt (argc, argv, "vhf:o:l:")) != -1) {
       switch (opt)
         {
          case 'o':
            outFilePtr = optarg;
            break;
          case 'f':
            imageInFilePtr = optarg;
            fileOpt = 1;
            break;
          case 'l':
            listPtr = optarg;
            break;
          case 'v':
            verbose = 1;
            break;
          case 'h':
            usage(argv[0]);
            return 0;
          case '?':
            if ((optopt == 'o') || (optopt == 'f') || (optopt == 'l'))
              printf ("Option -%c requires an argument.\n", optopt);
            else
              printf ("invalid option -%c \n", optopt);
            usage(argv[0]);
            exit(-1); 

          }
    }

    // check input parms for sanity

    if (NULL != listPtr && 3<argc)  {
       printf("List option is mutually exclusive with other arguments\n");
       usage(argv[0]);
       exit(-1);
    } else if (NULL != listPtr) {
       // do list and out of here 
       dumpelf(listPtr);
       return 0;
    }

    // check other parms

    if (argc > optind && 1 == fileOpt) {
       printf("Cannot have both file option and argument list\n");
       usage(argv[0]);
       exit(-1);
    }

    if (argc == optind && 0 == fileOpt) {
       printf("The file option or an argument list must be specified\n");
       usage(argv[0]);
       exit(-1);
    }

    if (0 == fileOpt) {
       // input files are command line arguments
       numFiles = argc-optind;
       if (NUM_FILES < numFiles) {
          printf("Too many file arguments\n");
          exit(-1);
       }
    }

    // set elf output file name
    if (NULL == outFilePtr) outFilePtr = fileName;

    // set temp output file name
    tmpnam(tempfileName);

    // set linker path
    linkerPath = getenv("BGQ_LINKERPATH");
    if (NULL == linkerPath) {
       printf("BGQ_LINKERPATH environment variable not set attempting to use\n%s\n",defaultLinker);
       linkerPath=defaultLinker;
    }

    if (verbose) {
        printf("temp file = %s\n",tempfileName);
        printf("output file name = %s\n",outFilePtr);
        printf("linker path = %s\n",linkerPath);

    }
//
// set up memory file system structure
//
    if (NULL == (memDataPtr = malloc(MAX_MEMFILE))) {  // allocate and point to data area
       perror("error allocating work area");
       exit(-1);
    }

    memFSDataPtr = (memFSdata_t*) memDataPtr;   // point to memFS data structure
    memset(memDataPtr,0x00,sizeof(memFSdata_t));  // clear directory area

    fileOffset = sizeof(memFSdata_t);          // start of data is after the header
    fileDataPtr = memDataPtr + fileOffset;

    // set up input type
    if (1 == fileOpt) {
       // input from file
       inNamefile=fopen(imageInFilePtr,"r" );
       if (NULL == inNamefile){
          perror("open error on member name file");
          printf("File in error is %s \n",imageInFilePtr);
          exit(-1);
       }
    } else {
       // input from command line
       currentArg = optind;
    }

//
// copy input files and build directory entries
//
    do {
       i = currentFiles;     // next directory entry slot
       if (0 == fileOpt) {
          // input from arg list
          getnextarg(argv, currentArg, inputFileName, sizeof(inputFileName)-1);
          currentFiles++;
          currentArg++;
          if (currentArg == argc) done = 1;
       } else {
          // get input from file
          rc = getnextentry(inNamefile,inputFileName, sizeof(inputFileName)-1);
          if (0 == rc) {
             currentFiles++;
             if (NUM_FILES < currentFiles)  {
                printf("Too many input files\n");
                exit(-1);
             }
          } else 
             break;       // last entry already processed
       }

       // isolate file name
       memNamePtr = strrchr(inputFileName,'/');       // find end of path
       if (!memNamePtr) 
          memNamePtr = inputFileName;   // name in same dir
       else
          memNamePtr++;                 // skip leading /
       memNameLen = strlen(memNamePtr);
       if (NAME_LEN<memNameLen) {
          printf("input file %s file name too long\n",argv[i+1]);
          exit(-1);
       }
       // copy input file to memFS
       rc = stat(inputFileName,&fileStat);
       if (-1 == rc) {
          perror("error on stat");
          printf("File in error is %s\n",inputFileName);
          exit(-1);
       }
       inLen = fileStat.st_size;
       if (MAX_MEMFILE<(fileOffset + inLen)) {
          printf("memFs not large enough for file %s\n",inputFileName);
          exit(-1);
       }

       infile=open(inputFileName,O_RDONLY );
       if (-1 == infile){
          perror("open error on input");
          printf("File in error is %s \n",inputFileName);
          exit(-1);
       }
       inBytes = read(infile,fileDataPtr,inLen);
       if (inBytes != inLen){
          perror("read error ");
          printf("File in error is %s \n",inputFileName);
          exit(-1);
       }
       if (close(infile)) {
          printf("FileClose on %s failed\n",inputFileName);
          exit(1);
       }
       // build directory entry for file
       memcpy(memFSDataPtr->entry[i].name,memNamePtr,memNameLen);
       memFSDataPtr->entry[i].nameLen = htonl(memNameLen);
       memFSDataPtr->entry[i].fileOffset  = htonl(fileOffset);
       memFSDataPtr->entry[i].fileSize = htonl(inLen);
       // set up for next file
       fileOffset += inLen;
       fileDataPtr += inLen;
    }  while(!done);     // end of input file(s) processing
//
// build rest of header for memFS image
//
    memcpy(memFSDataPtr->id,MEMFS_ID,8);
    memFSDataPtr->totalFSsize = htonl(fileOffset);
    memFSDataPtr->totalFSfiles = htonl(currentFiles);
    
//
// create memFS image file
//
    outfile=creat(tempfileName, mode);
    if (-1 == outfile){
       perror("File create error");
       printf("File in error is temp work area  %s\n",tempfileName);
       exit(-1);
    }
    outBytes = write(outfile,memDataPtr,fileOffset);
    if (outBytes != fileOffset){
       perror("Write error ");
       printf("File in error is temp work area %s\n",tempfileName);
    }
    close(outfile);

    if (verbose)
       dumpdir(memFSDataPtr);
    else
       printf("Total memFS image size is %ld \n",fileOffset);

    free(memDataPtr);           // done with in storage version

    // call linker to create elf wrapper
    sprintf(linkerString,"%s -Tdata=0xc0000000 --entry=0xc0000000 -n -b binary -o %s %s",
              linkerPath,outFilePtr,tempfileName);
    rc = system(linkerString);
    if (0 == rc)
       printf("elf image file %s created\n",outFilePtr); 
    else
       printf("elf image file %s create failed\n",outFilePtr);

    unlink(tempfileName);     // get rid of tempfile

    return 0;
}