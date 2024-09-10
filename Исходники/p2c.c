int main (int argc, char *argv[])
{
  char cpxName[BUF],ampName[BUF],phsName[BUF]; /* File Names                  */
  FILE *fdCpx, *fdAmp, *pdPhs;            /* File Pointers                    */
  int line, sample;                       /* Line & sample indices for looping*/
  int percentComplete;                    /* Percent of data processed        */
  int ampBlockSize, phsBlockSize;         /* Number of samples gotten         */
  float *ampBuf, *aP, *phsBuf, *pP;       /* Output data buffers              */
  complexFloat *cpxBuf, *cP;              /* Input data buffers               */
  meta_parameters *inMeta, *outMeta;      /* In/Out meta structs              */
  int i, phaseImage=FALSE;

/* Make sure there are the correct number of args in the command line */
  if (argc < 3) { usage(argv[0]); }

/* Make sure input and output names are different */
  if (strcmp(argv[1],argv[2])==0) {
    printf("p2c: Input and output names cannot be the same. Exiting.\n");
    exit(EXIT_FAILURE);
  }
  
/* Get commandline args */
  create_name (ampName,argv[1],".amp"); 
  create_name (phsName,argv[1],".phase"); 
  create_name (cpxName,argv[2],".cpx");
  
  // Check whether phase image actually exists. If it does not exist, we will 
  // generate a phase image with a constant value on the fly.
  if (fileExists(phsName))
    phaseImage = TRUE;
  else
    printf("\nCould not find phase image! Generating constant phase image on "
	   "the fly ...\n");

/* Read the meta data. Write output meta with COMPLEX_* data type. */
  inMeta = meta_read(argv[1]);
  outMeta = meta_read(argv[1]);
  outMeta->general->data_type = meta_polar2complex(inMeta->general->data_type);
  meta_write(outMeta,argv[2]);

/* malloc buffers, check and open files */
  cpxBuf = (complexFloat *)MALLOC(sizeof(complexFloat)
                         * outMeta->general->sample_count * CHUNK_OF_LINES);
  ampBuf = (float *)MALLOC(sizeof(float)
                         * inMeta->general->sample_count * CHUNK_OF_LINES);
  phsBuf = (float *)MALLOC(sizeof(float)
                         * inMeta->general->sample_count * CHUNK_OF_LINES);
  fdCpx = fopenImage(cpxName, "wb");
  fdAmp = fopenImage(ampName, "rb");  
  pdPhs = fopenImage(phsName, "rb");  

/* Run thru the complex file, writing real data to amp and imag data to phase */
  printf("\n");
  percentComplete = 0;
  for (line=0; line<inMeta->general->line_count; line+=CHUNK_OF_LINES)
  {
    if ((line*100/inMeta->general->line_count == percentComplete)) {
      printf("\rConverting amp and phase to complex: %3d%% complete.",
             percentComplete++);
      fflush(NULL);
    }
    ampBlockSize = get_float_lines(fdAmp,inMeta,line,CHUNK_OF_LINES,ampBuf);
    if (phaseImage) {
      phsBlockSize = get_float_lines(pdPhs,inMeta,line,CHUNK_OF_LINES,phsBuf);
      if (ampBlockSize != phsBlockSize) {
	printf("\n");
	printf("p2c: Failed to get the same number of samples from amplitude and phase files.\n");
	printf("p2c: Exiting...\n\n");
	exit(EXIT_FAILURE);
      }
    }
    else {
      for (i=0; i<inMeta->general->sample_count*CHUNK_OF_LINES; i++)
	phsBlockSize = 0.0;
    }
    cP = cpxBuf;
    aP = ampBuf;
    pP = phsBuf;
    for (sample=0; sample<ampBlockSize; sample++) {
      cP->real = *aP * cos(*pP);
      cP->imag = *aP * sin(*pP);
      cP++;
      aP++;
      pP++;
    }
    put_complexFloat_lines(fdCpx,outMeta,line,CHUNK_OF_LINES,cpxBuf);
  }
  printf("\rConverted amp and phase to complex:  100%% complete.\n\n");

  /* close, free, halt */
  FCLOSE(fdCpx);
  FCLOSE(fdAmp);
  FCLOSE(pdPhs);
  FREE(cpxBuf);
  FREE(ampBuf);
  FREE(phsBuf);
  meta_free(inMeta);
  meta_free(outMeta);
  
  return 0;
}