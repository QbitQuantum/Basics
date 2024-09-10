/*
  Function: peerRead
  
  Reads a matrix in PEER format.
  
  first file contain :
  > NumberOfFiles
  > file1
  > file2
  > ...

  each file contains:
  > %ld%ld          (globaln localn)
  > %ld             (local nnzeros)
  four elements from col by line, nnzeros local elements in total,
  four elements from row by line, nnzeros local elements in total,
  four elements from val by line, nnzeros local elements in total,
  four elements from rhs by line, nnzeros local elements in total,

  for each part, last line can be with 1, 2 ,3 or 4 elements.

  Parameters:
    filename - Path to file to read from
    Nrow     - Number of rows						 
    Ncol     - Number of columns					 
    Nnzero,  - Number of non zeros					 
    col      - Index of first element of each column in *row* and *val* 
    row      - Row of eah element				       	 
    val      - Value of each element				       	 
    Type     - Type of the matrix				       	 
    RhsType  - Type of the right-hand-side.			         
    rhs      - right-hand-side term(s)
*/
void peerRead(char const      *filename, 
	      pastix_int_t    *Nrow, 
	      pastix_int_t    *Ncol, 
	      pastix_int_t    *Nnzero, 
	      pastix_int_t   **col, 
	      pastix_int_t   **row, 
	      pastix_float_t **val, 
	      char           **Type, 
	      char           **RhsType, 
	      pastix_float_t **rhs)
{
  FILE *infile;
  pastix_int_t iterfile;
  char line[BUFSIZ];
  pastix_int_t rowlocal,rowglobal;
  pastix_int_t nzlocal,nzglobal;
  long filenamenumber;
  char **filenametab;
  const pastix_int_t nbreltperline=4; /* nbr of elt per line */
  long tempint1,tempint2,tempint3,tempint4;
  long double tempfloat1, tempfloat2, tempfloat3, tempfloat4;

  *Nnzero=0;
  *Type = (char *) malloc(4*sizeof(char));
  *RhsType = (char *) malloc(4*sizeof(char));

  (*Type)[0] = 'R';
  (*Type)[1] = 'U';
  (*Type)[2] = 'A';
  (*Type)[3] = '\0';
  (*RhsType)[0] = 'A';
  (*RhsType)[2] = 'A';
  (*RhsType)[3] = '\0';


#ifdef TYPE_COMPLEX 
  fprintf(stderr, "\nWARNING: This drivers reads non complex matrices, imaginary part will be 0\n\n");
#endif

  /* Read rsaname */
  infile = fopen(filename, "r");
  if (infile==NULL)
    {
      fprintf(stderr,"cannot load %s\n", filename);
      exit(EXIT_FAILURE);
    }
  FGETS(line, BUFSIZ, infile);
  sscanf(line, "%ld", &filenamenumber); /* Read number of filename */
  filenametab = (char **) malloc(filenamenumber*sizeof(char *));
  for (iterfile=0; iterfile<filenamenumber; iterfile++)
    {
      filenametab[iterfile] = (char *) malloc(64*sizeof(char));
      FGETS(line, BUFSIZ, infile);
      sscanf(line, "%s", filenametab[iterfile]);
    }
  fclose(infile);
  
  /* Calcul nnz global */
  for (iterfile=0; iterfile<filenamenumber; iterfile++)
    {
      infile = fopen(filenametab[iterfile], "r");
      if (infile==NULL)
	{
	  fprintf(stderr,"cannot load %s\n", filenametab[iterfile]);
	  exit(EXIT_FAILURE);
	}
      FGETS(line, BUFSIZ, infile);
      sscanf(line, "%ld%ld", &tempint1,&tempint2);
      *Nrow = tempint1;
      rowlocal = tempint2;
      fprintf(stderr, "Nrow %ld rowlocal %ld\n", (long) *Nrow, (long) rowlocal);
      FGETS(line, BUFSIZ, infile);
      sscanf(line, "%ld", &tempint1);
      nzlocal = tempint1;
      fprintf(stderr, "nzlocal %ld\n", (long) nzlocal);
      fclose(infile);
    
      *Nnzero += nzlocal;
    }
  *Ncol = *Nrow;
  fprintf(stderr, "Nnzero global %ld\n", (long int) *Nnzero);

  /* memory alloc */
  (*col) = (pastix_int_t *) malloc((*Nrow+1)*sizeof(pastix_int_t));
  if ((*col) == NULL)
    fprintf(stderr, "peerRead : Not enough memory for *col\n");
  (*row) = (pastix_int_t *) malloc(*Nnzero*sizeof(pastix_int_t));
  if ((*row) == NULL)
    fprintf(stderr, "peerRead : Not enough memory for *row\n");
  (*val) = (pastix_float_t *) malloc(*Nnzero*sizeof(pastix_float_t));
  if ((*val) == NULL)
    fprintf(stderr, "peerRead : Not enough memory for *val\n");
  (*rhs) = (pastix_float_t *) malloc(*Nrow*sizeof(pastix_float_t));
  if ((*rhs) == NULL)
    fprintf(stderr, "peerRead : Not enough memory for *rhs\n");

  rowglobal=0;
  nzglobal=0;
  for (iterfile=0; iterfile<filenamenumber; iterfile++)
    {
      pastix_int_t iterelt;
      
      infile = fopen(filenametab[iterfile], "r");
      if (infile==NULL)
	{
	  fprintf(stderr,"cannot load %s\n", filenametab[iterfile]);
	  exit(EXIT_FAILURE);
	}
      FGETS(line,BUFSIZ,infile);
      sscanf(line, "%ld%ld", &tempint1, &tempint2);
      *Nrow = tempint1;
      rowlocal = tempint2;
      FGETS(line,BUFSIZ,infile);
      sscanf(line, "%ld", &tempint1);
      nzlocal = tempint1;

      /* read col */
      for (iterelt=0; iterelt<rowlocal+1+1-nbreltperline;iterelt++)
	{
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld %ld %ld", &tempint1, &tempint2, &tempint3, &tempint4);
	  (*col)[iterelt+rowglobal]   = (pastix_int_t)tempint1+nzglobal;
	  (*col)[iterelt+rowglobal+1] = (pastix_int_t)tempint2+nzglobal;
	  (*col)[iterelt+rowglobal+2] = (pastix_int_t)tempint3+nzglobal;
	  (*col)[iterelt+rowglobal+3] = (pastix_int_t)tempint4+nzglobal;
	  iterelt+=3;
	}
      
      switch (rowlocal-iterelt+1)
	{
	case 1:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld",&tempint1);
	  (*col)[iterelt+rowglobal] += (pastix_int_t)tempint1+nzglobal;
	  iterelt++;
	  break;
	case 2:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld", &tempint1, &tempint2);
	  (*col)[iterelt+rowglobal]   = (pastix_int_t)tempint1+nzglobal;
	  (*col)[iterelt+rowglobal+1] = (pastix_int_t)tempint2+nzglobal;
	  iterelt+=2;
	  break;
	case 3:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld %ld", &tempint1, &tempint2, &tempint3);
	  (*col)[iterelt+rowglobal]   = (pastix_int_t)tempint1+nzglobal;
	  (*col)[iterelt+rowglobal+1] = (pastix_int_t)tempint2+nzglobal;
	  (*col)[iterelt+rowglobal+2] = (pastix_int_t)tempint3+nzglobal;
	  iterelt+=3;
	  break;
	}


      /* read row */
      for (iterelt=0; iterelt<nzlocal+1-nbreltperline; iterelt++)
	{
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld %ld %ld", &tempint1,&tempint2,&tempint3,&tempint4);
	  (*row)[iterelt+nzglobal]   = (pastix_int_t)tempint1;
	  (*row)[iterelt+nzglobal+1] = (pastix_int_t)tempint2;
	  (*row)[iterelt+nzglobal+2] = (pastix_int_t)tempint3;
	  (*row)[iterelt+nzglobal+3] = (pastix_int_t)tempint4;
	  iterelt+=3;
	}
      switch (nzlocal-iterelt)
	{
	case 1:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld",&tempint1);
	  (*row)[iterelt+nzglobal] = (pastix_int_t)tempint1;
	  iterelt++;
	  break;
	case 2:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld", &tempint1, &tempint2);
	  (*row)[iterelt+nzglobal]   = (pastix_int_t)tempint1;
	  (*row)[iterelt+nzglobal+1] = (pastix_int_t)tempint2;
	  iterelt+=2;
	  break;
	case 3:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%ld %ld %ld", &tempint1, &tempint2, &tempint3);
	  (*row)[iterelt+nzglobal]   = (pastix_int_t)tempint1;
	  (*row)[iterelt+nzglobal+1] = (pastix_int_t)tempint2;
	  (*row)[iterelt+nzglobal+2] = (pastix_int_t)tempint3;
	  iterelt+=3;
	  break;
	}

      /* read val */
      for (iterelt=0; iterelt<nzlocal+1-nbreltperline; iterelt++)
	{
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf %Lf %Lf",&tempfloat1,&tempfloat2,&tempfloat3,&tempfloat4);
	  (*val)[iterelt+nzglobal]   = (pastix_float_t)tempfloat1;
	  (*val)[iterelt+nzglobal+1] = (pastix_float_t)tempfloat2;
	  (*val)[iterelt+nzglobal+2] = (pastix_float_t)tempfloat3;
	  (*val)[iterelt+nzglobal+3] = (pastix_float_t)tempfloat4;
	  iterelt+=3;
	}
      switch (nzlocal-iterelt)
	{
	case 1:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf",&tempfloat1);
	  (*val)[iterelt+nzglobal] = (pastix_float_t)tempfloat1;
	  iterelt++;
	  break;
	case 2:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf",&tempfloat1,&tempfloat2);
	  (*val)[iterelt+nzglobal]   = (pastix_float_t)tempfloat1;
	  (*val)[iterelt+nzglobal+1] = (pastix_float_t)tempfloat2;
	  iterelt+=2;
	  break;
	case 3:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf %Lf",&tempfloat1,&tempfloat2,&tempfloat3);
	  (*val)[iterelt+nzglobal]   = (pastix_float_t)tempfloat1;
	  (*val)[iterelt+nzglobal+1] = (pastix_float_t)tempfloat2;
	  (*val)[iterelt+nzglobal+2] = (pastix_float_t)tempfloat3;
	  iterelt+=3;
	  break;
	}
      nzglobal += nzlocal;

      /* read rhs */
      for (iterelt=0; iterelt<rowlocal+1-nbreltperline; iterelt++)
	{
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf %Lf %Lf",&tempfloat1,&tempfloat2,&tempfloat3,&tempfloat4);
	  (*rhs)[iterelt+rowglobal]   = (pastix_float_t)tempfloat1;
	  (*rhs)[iterelt+rowglobal+1] = (pastix_float_t)tempfloat2;
	  (*rhs)[iterelt+rowglobal+2] = (pastix_float_t)tempfloat3;
	  (*rhs)[iterelt+rowglobal+3] = (pastix_float_t)tempfloat4;
	  iterelt+=3;
	}

      switch (rowlocal-iterelt)
	{
	case 1:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf",&tempfloat1);
	  (*rhs)[iterelt+rowglobal] = (pastix_float_t)tempfloat1;
	  iterelt++;
	  break;
	case 2:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf",&tempfloat1,&tempfloat2);
	  (*rhs)[iterelt+rowglobal]   = (pastix_float_t)tempfloat1;
	  (*rhs)[iterelt+rowglobal+1] = (pastix_float_t)tempfloat2;
	  iterelt++;
	  break;
	case 3:
	  FGETS(line,BUFSIZ,infile);
	  sscanf(line,"%Lf %Lf %Lf",&tempfloat1,&tempfloat2,&tempfloat3);
	  (*rhs)[iterelt+rowglobal]   = (pastix_float_t)tempfloat1;
	  (*rhs)[iterelt+rowglobal+1] = (pastix_float_t)tempfloat2;
	  (*rhs)[iterelt+rowglobal+2] = (pastix_float_t)tempfloat3;
	  iterelt++;
	  break;
	}
      rowglobal += rowlocal;

      fclose(infile);
    }
}