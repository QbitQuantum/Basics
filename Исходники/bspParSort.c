void bspParSort(){

  int Log2(int x);
  void mergeSort(int x, int *temp1);
  void merge2(int *arr1, int *arr2, int size);

  int *localArr; /* local array in each processor */
  int i,j,k; /* index variables */
  int n_divide_p; /* Avoid multiple computation */
  int n; /* Number of elements to be sorted */
  int szLocalArray; /* Size of local array */
  double time0, time1; /* Time */
  FILE *ifp = 0; /* Reader to read sequence of numbers to be sorted */

  bsp_begin(P);
  int p= bsp_nprocs(); /* Number of processors obtained */ 
  int s= bsp_pid();    /* Processor number */ 

  //Get number of elements to be sorted
  if(s==0){
    ifp = fopen("sort","r");
    if(ifp == NULL){
      fprintf(stderr, "Can't open input file!\n");
      exit(1);
    }
    fscanf(ifp, "%i", &n);
  }

  // Make sure every processor knows everything
  bsp_push_reg(&n,sizeof(int));
  bsp_sync();
  bsp_get(0,&n,0,&n,sizeof(int));
  bsp_sync();
  bsp_pop_reg(&n);

  //Setup distribution 
  n_divide_p = n/p;
  szLocalArray = n/pow(2,ceil(Log2(s+1)));
  localArr = vecalloci(szLocalArray);
  bsp_push_reg(localArr,sizeof(int)*szLocalArray);

  if(s==0){ 
    printf("Distribution start\n"); fflush(stdout); 
  }

  bsp_sync();
  int value;
  if(s==0){
    //allocate to array on proc 0
    for(i=0; i< n_divide_p; i++){
      fscanf(ifp, "%i", &value);
      localArr[i]=value;      
    }
    //Send to arrays on other processors
    for(i=1; i< p; i++){
      for(j=0;j<n_divide_p;j++){
        fscanf(ifp, "%i", &value);
        bsp_put(i,&value,localArr,j*sizeof(int),sizeof(int));
      }
    }
    fclose(ifp);
  }
  bsp_sync();
  if(s==0){ 
    printf("Distribution done\n"); fflush(stdout); 
  }

  //Distribution done and we can start time measurement 
  if(s==0){
    printf("Time start\n"); fflush(stdout);
  }
  time0 = bsp_time();

  //Locally sort each array
  if(s==0){
    printf("Local sort\n"); fflush(stdout);
  }
  mergeSort(n_divide_p, localArr);
  bsp_sync();

  //Merging 
  int *temp = malloc(sizeof(int)*pow(2,Log2(p))*n_divide_p);
  for(j=1;j<Log2(p)+1;j++){
    if(s<p/pow(2,j)){
      for(k=0;k<pow(2,j-1)*n_divide_p;k++){
        bsp_get(s+(p/pow(2,j)),localArr,k*sizeof(int),&(temp[k]),sizeof(int));
      }
    }
    bsp_sync();

    if(s<p/pow(2,j)){
      merge2(localArr, temp, n_divide_p*pow(2,j-1));
    }

    bsp_sync();
    if(s==0){ 
      printf("Round %i out of %i rounds of merging done (on proc 0)\n",j,Log2(p)); fflush(stdout); 
    }
  }
  if(s==0){
    printf("Sorting done\n"); fflush(stdout);
  }
  bsp_sync();
 
  //Print sorted array - expensive if sample is big
  /*
  if(s==0){
    printf("Sorted sequence is:\n");
    for(i=0; i<szLocalArray; i++){
      printf("%i ",localArr[i]); fflush(stdout);
    }
    printf("\n"); fflush(stdout);
  }
  */

  //Parallel algorithm ends
  time1 = bsp_time();
  if(s==0){
    printf("Time stop\n"); fflush(stdout);
  }

  //Report time to user
  if(s==0){
    printf("Sorting took %.6lf seconds.\n", time1-time0); fflush(stdout);
  }
  
  //Clean up
  free(temp);
  bsp_pop_reg(localArr); free(localArr);

  bsp_end();
} /* End bspParSort */