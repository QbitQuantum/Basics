void readData(double *adLookUp, char* szDataFile, t_Flows* ptFlows, t_Params *ptParams)
{
  char szLine[MAX_LINE_LENGTH];
  char *szTok;
  int nN = 0, nM = 0;
  double *adData = NULL;
  double *adF    = NULL;
  int    *anF    = NULL;
  int    *anLengths = NULL;
  char *pcError = NULL;
  int i = 0, j = 0, nE = 0;
  FILE *ifp = NULL;

  ifp = fopen(szDataFile, "r");

  if(ifp){
    /*read header line*/
    fgets(szLine, MAX_LINE_LENGTH, ifp);
    /*get read number*/
    szTok = strtok(szLine, DELIM);
    nN = strtol(szTok,&pcError, 10);
    if(*pcError != '\0')
      goto formatError;

    /*get flow number*/
    szTok = strtok(NULL,DELIM);
    nM = strtol(szTok,&pcError, 10);
    if(*pcError != '\0')
      goto formatError;
    
    adData = (double *) malloc(nN*nM*sizeof(double));
    if(!adData)
      goto memoryError;

    adF = (double *) malloc(nN*nM*sizeof(double));
    if(!adF)
      goto memoryError;

    anF = (int *) malloc(nN*nM*sizeof(int));
    if(!anF)
      goto memoryError;

    anLengths = (int *) malloc(nN*sizeof(int));
    if(!anLengths)
      goto memoryError;

    for(i = 0; i < nN; i++){
      fgets(szLine, MAX_LINE_LENGTH, ifp);
      
      szTok = strtok(szLine, DELIM);

      if(ptParams->bNoIndex == FALSE){ 
	szTok = strtok(NULL, DELIM);
      }

      anLengths[i] = strtol(szTok, &pcError,10);
      if(*pcError != '\0')
	goto formatError;
    
      nE = anLengths[i] % 4;
      anLengths[i] -= nE;
          printf("%d %d %d %d\n",i, anLengths[i], nE, nM);
      for(j = 0; j < anLengths[i]; j++){
	double dF = 0.0;

	szTok = strtok(NULL, DELIM);
	dF = strtod(szTok, &pcError);
	//	printf("%d %s %f\n",j, szTok,dF);
	if(dF >= 9.99){
	  //fprintf(stderr,"%d %d %f too large max flow 9.99\n",i,j,dF);
	  dF = 9.99;
	  fflush(stderr);
	}

	adData[i*nM + j] = dF;
	anF[i*nM + j] =  (int) floor((dF + DELTA)/PRECISION);
	if(anF[i*nM + j] < 0){
	  anF[i*nM + j] = 0;
	}
	if(anF[i*nM + j] > BINS - 1){
	  anF[i*nM + j] = BINS - 1;
	}

	adF[i*nM + j] = distM1(adLookUp, dF);
	
	if(*pcError != '\0')
	  goto formatError;
      }

      for(; j < nM; j++){
	double dF = 0.0;
	adData[i*nM + j] = dF;
	anF[i*nM + j] =  (int) floor((dF + DELTA)/PRECISION);
	adF[i*nM + j] = distM1(adLookUp, dF);
	
      }
    }

    fclose(ifp);
  }
  else{
    printf("Failed to open file %s in readData\n",szDataFile);
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  ptFlows->anLengths = anLengths;
  ptFlows->adData    = adData;
  ptFlows->adF       = adF;
  ptFlows->anF       = anF;
  ptFlows->nN = nN; ptFlows->nM = nM;
  return;
 memoryError:
  fprintf(stderr, "Failed allocating memory in readData\n");
  fflush(stderr);
  exit(EXIT_FAILURE);

 formatError:
  fprintf(stderr, "Incorrect input format error\n");
  fflush(stderr);
  exit(EXIT_FAILURE);
}