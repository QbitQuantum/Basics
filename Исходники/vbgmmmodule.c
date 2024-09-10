int driver(const char* szFileStub, int nKStart, int nLMin, unsigned long lSeed, int nMaxIter, double dEpsilon, int bCOut)
{
  t_Params           tParams;
  t_Data             tData;
  gsl_rng            *ptGSLRNG     = NULL;
  const gsl_rng_type *ptGSLRNGType = NULL;
  int i = 0, k = 0, nD = 0, nN = 0;
  char szOFile[MAX_FILE_NAME_LENGTH];
  FILE *ofp = NULL;
  t_VBParams tVBParams;
  t_Cluster  *ptBestCluster = NULL;
  gsl_matrix *ptTemp = NULL;
  gsl_matrix *ptTVar = NULL;
  /*initialise GSL RNG*/
  gsl_rng_env_setup();

  gsl_set_error_handler_off();
  
  ptGSLRNGType = gsl_rng_default;
  ptGSLRNG     = gsl_rng_alloc(ptGSLRNGType);
  
  /*get command line params*/
  tParams.nKStart  = nKStart;
  tParams.nLMin    = nLMin;
  tParams.nMaxIter = nMaxIter;
  tParams.dEpsilon = dEpsilon;
  tParams.lSeed    = lSeed;

  setParams(&tParams,szFileStub);

  /*read in input data*/
  readInputData(tParams.szInputFile, &tData);

  readPInputData(tParams.szPInputFile, &tData);

  nD = tData.nD;
  nN = tData.nN;

  ptTemp = gsl_matrix_alloc(tData.nT,nD);
  ptTVar = gsl_matrix_alloc(tData.nT,tData.nT);

  setVBParams(&tVBParams, &tData);
  
  ptBestCluster = (t_Cluster *) malloc(sizeof(t_Cluster));

  ptBestCluster->nN = nN;
  ptBestCluster->nK = tParams.nKStart;
  ptBestCluster->nD = nD;
  ptBestCluster->ptData = &tData;
  ptBestCluster->ptVBParams = &tVBParams;
  ptBestCluster->lSeed = tParams.lSeed;
  ptBestCluster->nMaxIter = tParams.nMaxIter;
  ptBestCluster->dEpsilon = tParams.dEpsilon;

  if(bCOut > 0){
	ptBestCluster->szCOutFile = szFileStub;
  }
  else{
	ptBestCluster->szCOutFile = NULL;
  }
  runRThreads((void *) &ptBestCluster);

  compressCluster(ptBestCluster);

  calcCovarMatrices(ptBestCluster,&tData);

  sprintf(szOFile,"%sclustering_gt%d.csv",tParams.szOutFileStub,tParams.nLMin);
  writeClusters(szOFile,ptBestCluster,&tData);

  sprintf(szOFile,"%spca_means_gt%d.csv",tParams.szOutFileStub,tParams.nLMin);
  writeMeans(szOFile,ptBestCluster);

  sprintf(szOFile,"%smeans_gt%d.csv",tParams.szOutFileStub,tParams.nLMin);
  writeTMeans(szOFile,ptBestCluster,&tData);

  for(k = 0; k < ptBestCluster->nK; k++){
    sprintf(szOFile,"%spca_variances_gt%d_dim%d.csv",tParams.szOutFileStub,tParams.nLMin,k);
    
    writeSquareMatrix(szOFile, ptBestCluster->aptSigma[k], nD);
  
    /*not entirely sure this is correct?*/
    gsl_blas_dgemm (CblasNoTrans,CblasNoTrans,1.0,tData.ptTMatrix,ptBestCluster->aptSigma[k],0.0,ptTemp);
  
    gsl_blas_dgemm (CblasNoTrans,CblasTrans,1.0,ptTemp,tData.ptTMatrix,0.0,ptTVar);

    sprintf(szOFile,"%svariances_gt%d_dim%d.csv",tParams.szOutFileStub,tParams.nLMin,k);

    writeSquareMatrix(szOFile, ptTVar, nD);
  }

  sprintf(szOFile,"%sresponsibilities.csv",tParams.szOutFileStub);

  ofp = fopen(szOFile,"w");
  if(ofp){    

    for(i = 0; i < nN; i++){
      for(k = 0; k < ptBestCluster->nK - 1; k++){
	fprintf(ofp,"%f,",ptBestCluster->aadZ[i][k]);
      }
      fprintf(ofp,"%f\n",ptBestCluster->aadZ[i][ptBestCluster->nK - 1]);
    }

    fclose(ofp);
  }
  else{
    fprintf(stderr,"Failed openining %s in main\n", szOFile);
    fflush(stderr);
  }

  sprintf(szOFile,"%svbl.csv",tParams.szOutFileStub);

  ofp = fopen(szOFile,"w");
  if(ofp){    
    fprintf(ofp,"%d,%f,%d\n",ptBestCluster->nK,ptBestCluster->dVBL,ptBestCluster->nThread);

    fclose(ofp);
  }
  else{
    fprintf(stderr,"Failed openining %s in main\n", szOFile);
    fflush(stderr);
  }

  /*free up memory in data object*/
  destroyData(&tData);

  /*free up best BIC clusters*/

  destroyCluster(ptBestCluster);
  free(ptBestCluster);

  destroyParams(&tParams);
  gsl_rng_free(ptGSLRNG);
  gsl_matrix_free(tVBParams.ptInvW0);
  gsl_matrix_free(ptTemp);
  gsl_matrix_free(ptTVar);

  return EXIT_SUCCESS;
}