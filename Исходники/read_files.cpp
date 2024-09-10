int get_transition(HMMER_PROFILE *hmm, const char* hmm_Path) 
{
  int i;

  char* BEGIN = "  COMPO   ";
  FilePointer = fopen(hmm_Path, "r");
  if(FilePointer == NULL) {
    printf("Fatal error: Cannot open or find <.hmm> file\n");
    getchar();
    return fileERROR;
  } else {
    //printf(".hmm file open well_trans\n");
  }

  /* 1. locate the line of 1st stage */
  char* locate = (char*)malloc(11 * sizeof(char));  //why 11? since we need use 'fgets' to search BEGIN
  do{
    fgets(locate, 11, FilePointer);
    if(strcmp(locate, BEGIN))
      nextLine(FilePointer, 1);
  }while(strcmp(locate, BEGIN) && !feof(FilePointer));

  nextLine(FilePointer, 2);                         //move to the 'transition' line...

  char* t_Temp = (char*)malloc(72 * sizeof(char));  //why 72? since we need use 'fgets' to get TRAN line
  char* p;

  /* 2. Process node 0 */
  fgets(t_Temp, 72, FilePointer);

  p = strtok(t_Temp, "  ");
  hmm->tran_32bits[0][MM] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[0][MI] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[0][MD] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[0][IM] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[0][II] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[0][DM] = 1.0f;

  hmm->tran_32bits[0][DD] = 0;

  nextLine(FilePointer, 3);             //move to next 'transition' line... 

  /* 3. Process node 1 to M-1 */
  for(i = 1; i < hmm->M; i++) {         //不去用 i = 0 (B) 和 i = length + 1 (E), 其中 E 的空间应该是永远都用不上的 

    fgets(t_Temp, 72, FilePointer);     //需要测试一下：p 设置在rolling外是不是可以？ 答案是肯定的，可以！！下一次用fgets时会覆盖掉原来的 72 个空间

    p = strtok(t_Temp, "  ");
    hmm->tran_32bits[i][MM] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][MI] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][MD] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][IM] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][II] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][DM] = expf(-1.0 * (float)atof(p));
    p = strtok(NULL, "  ");
    hmm->tran_32bits[i][DD] = expf(-1.0 * (float)atof(p));

    nextLine(FilePointer, 3); //move to next 'transition' line...
  }

  /* 4. Process node M */
  fgets(t_Temp, 72, FilePointer);

  p = strtok(t_Temp, "  ");
  hmm->tran_32bits[hmm->M][MM] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[hmm->M][MI] = expf(-1.0 * (float)atof(p));

  hmm->tran_32bits[hmm->M][MD] = expf(-1.0 * (float)atof(p));

  p = strtok(NULL, "        *  ");
  hmm->tran_32bits[hmm->M][IM] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");
  hmm->tran_32bits[hmm->M][II] = expf(-1.0 * (float)atof(p));
  p = strtok(NULL, "  ");

  hmm->tran_32bits[hmm->M][DM] = 1.0f;
    
  hmm->tran_32bits[hmm->M][DD] = 0;

  /* 3. free memory */
  fclose(FilePointer);
  free(locate);
  free(t_Temp);

  return fileOK;
}