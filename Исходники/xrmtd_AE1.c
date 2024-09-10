/***************************End of Declaration**************************************************************/
int main(int argc, char *argv[])
{
  int originalsize;
  FILE *pFile;
  
	if(argc >=5 && argv[4] != NULL)
	{
		deltaFile = fopen(argv[4],"wb");
	}
  // size of sym_t is 4 bytes
  pFile = fopen (argv[1],"rb");

  FILE *txtfile1 = fopen("rela1.txt","w+");
  FILE *txtfile2 = fopen("rela2.txt","w+");
  FILE *addrFreq = fopen(argv[5],"w+");
  if (pFile!=NULL)
  {
    fseek (pFile, 0, SEEK_END);
    originalsize = ftell (pFile); 
    
    originalsize /= sizeof(sym_t); // in terms of # of symbols
    rewind (pFile);
  }

  beta = atoi(argv[3]);

  originalfile=(sym_t*)malloc((originalsize + 1)*sizeof(sym_t));

  int c , i;
  i=0;

  fread(originalfile, sizeof(sym_t), originalsize, pFile);
  // need to do so??	
  originalfile[originalsize].offset=originalfile[originalsize].address=0;

  rewind(pFile);
  sort(originalfile,0,originalsize-1);
  for (i=0; i<originalsize; i++) {
    //sym_t mysym;
    //fread(&mysym, sizeof(sym_t), 1, pFile);

    fprintf(txtfile1, "%04X %04X\n", originalfile[i].offset, originalfile[i].address);
  }
  fclose(txtfile1);
  /* open  the new file and read it into an array   */
  
  FILE * qFile;
  int newsize;

  qFile = fopen (argv[2],"rb");

  if (qFile!=NULL){
    fseek (qFile, 0, SEEK_END);
    newsize=ftell (qFile); newsize /= sizeof(sym_t);
    rewind (qFile);
  }

  // read new file into an array
  newfile=(sym_t *)malloc((newsize + 1)*sizeof(sym_t));

  int j = 0;

  fread(newfile, sizeof(sym_t), newsize, qFile);
  // need to do so??	
  newfile[newsize].offset=newfile[newsize].address=0;

  rewind(qFile);
  sort(newfile,0,newsize-1);
  target_addr * head =  (target_addr*)malloc(sizeof(target_addr));
  head->next = NULL;
  for (i=0; i<newsize; i++) {
	  addAddr(newfile[i].address,head);
    fprintf(txtfile2, "%04X %04X\n", newfile[i].offset, newfile[i].address);
  }
  target_addr* tail = head->next;
  while(tail !=NULL)
  {
	  fprintf(addrFreq,"%04X\t%d\n",tail->address,tail->count);
	  tail = tail->next;
  }
  fclose(addrFreq);
  fclose(txtfile2);

  // Segment size 

  // printf("Segment size is  %d  \n" , sizeof(Segment));
  // printf("Char size is  %d  \n" , sizeof(char));
  // printf("Int size is  %d  \n" , sizeof(int));

  // initialize file_size_global
  file_size_global = newsize ; // in terms of # of symbols
  new_size_global = newsize ;  // in terms of # of symbols

  int maxsize = (originalsize>newsize)?originalsize:newsize; // in terms of # of symbols

  // printf("maxsize is : %d  \n", maxsize);
  
  //Initialize Table C
  Table_C = (sym_t**)malloc((originalsize) * sizeof(sym_t *));

  if(Table_C == NULL)
  {
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
	
  for(i = 0; i < originalsize; i++)
  {
    Table_C[i] = (sym_t*)malloc(newsize * sizeof(sym_t));
    if(Table_C[i] == NULL)
    {
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
  }

  // StoreCommon Segments
  printf("originalsize %d\n", originalsize*sizeof(sym_t));
  printf("newsize %d\n", newsize*sizeof(sym_t));


  StoreCommonSeg(Table_C, originalfile, newfile, originalsize, newsize);

  
  printf("SegCounter %d \n",Seg_counter );

  //
  //Segment * tmp = (&Seghead) -> next ;
  //for( i = 0; i < Seg_counter ; i++ ) {
	 // printf("The %d Seg's length=%d StartingX is %d , Ending X is %d , StartingY is %d, EndingY is %d (%d,%d) \n", tmp->num,tmp->Ending_Y-tmp->Starting_Y, tmp->Starting_X , tmp->Ending_X, tmp->Starting_Y, tmp->Ending_Y,
  //      tmp->offset, tmp->address);
  //  tmp = tmp -> next ;
  //}
  

  // run MDCD
  N = newsize;
  Local_Optimum = (int *) malloc( (N+1) * sizeof(int));
  S = (int *) malloc( (N+1) * sizeof(int));

  Message = (char **) malloc((N+1) * sizeof(char *)) ;
  cmd = (cmd_t*)malloc((N+1)*sizeof(cmd_t));
  for( i = 0 ; i < N+1 ; i++) {
    Message[i] = (char *) malloc(300 * sizeof(char));
  }
  //char   Message[N+1][300]; 
  //int beta;
  //int Transfer_length;
  Local_Optimum[0] = 0;
  Message[0] = "Here is the beginning of the new code image" ;
  cmd[0].type = -1;
  cmd[0].length =-1;
  cmd[0].inew=-1;
  cmd[0].iold = -1;
  //printf("%s", Message[0]);
  S[0] = 0;
  //printf("\n %d \n", beta);
  runMDCD(newfile);
  //for(i=1;i<N+1;i++)
  //{
	 // printf("%s\n",Message[i]);
  //}
  //PrintMessage1(N);
  PrintMessage(N);
  printf("delta %d\n",Transfer_length);
  // system("PAUSE");
  
  for(i = 0; i < originalsize; i++)
    free(Table_C[i]);
  free(Table_C);

  return 0;
}