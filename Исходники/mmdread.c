/*
 *  Function: DistributedMatrixMarketRead
 *
 *  Reads a matrix in distributed matrix market format
 *
 *  For more information about matrix market format see mmio.c/mmio.h
 *
 * Parameters:
 *   dirname - Path to the directory containing matrix
 *   Ncol    - Number of columns
 *   Nrow    - Number of rows
 *   Nnzero  - Number of non zeros
 *   col     - Index of first element of each column in *row* and *val*
 *   row     - Row of eah element
 *   val     - Value of each element
 *   Type    - Type of the matrix
 *   RhsType - Type of the right-hand-side.
 *
 */
void DistributedMatrixMarketRead(char const      *filename,
                                 pastix_int_t    *Ncol,
                                 pastix_int_t    *Nrow,
                                 pastix_int_t    *Nnzero,
                                 pastix_int_t   **col,
                                 pastix_int_t   **row,
                                 pastix_float_t **val,
                                 pastix_int_t   **l2g,
                                 char           **Type,
                                 char           **RhsType)
{

  FILE * file;
  pastix_int_t * tempcol, *g2l, *templ2g;
  pastix_int_t iter, iter2, baseval, mincol, maxcol;
  pastix_int_t * temprow;
  pastix_float_t * tempval;
  pastix_int_t total;
  pastix_int_t tmp;
  pastix_int_t pos;
  pastix_int_t limit;
  MM_typecode matcode;
  int tmpncol,tmpnrow,tmpnnzero;
  int rank, size;
  int tmpint;
  pastix_int_t i, global_n_col;
  char line[BUFSIZ], my_filename_s[BUFSIZ];
  char * my_filename;
  pastix_int_t column;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  file = fopen (filename,"r");
  if (file==NULL)
  {
    fprintf(stderr,"cannot load %s\n", filename);
    EXIT(MOD_SI,FILE_ERR);
  }

  FGETS(line, BUFSIZ, file);
  sscanf(line, "%d", &tmpint); /* Read number of filename */
  fprintf(stdout, "%d files\n", tmpint);

  if (size != tmpint)
    {
      /* pour l'instant rien. au choix : recreer un nouveau comm mpi, refusionner la csc et la redecouper */
      if (rank == 0)
        fprintf(stderr, "Please rerun with %d processors\n", tmpint);
      exit(EXIT_FAILURE);
    }

  for (i = 0; i < rank+1; i++)
    {
      FGETS(line, BUFSIZ, file);
      sscanf(line, "%s", my_filename_s);
    }
  my_filename = (char*)malloc(sizeof(char)*(strlen(filename)+BUFSIZ));
  strcpy(my_filename, filename);
  sprintf(my_filename,"%s/%s", dirname(my_filename), my_filename_s);
  fclose(file);

  *Type = (char *) malloc(4*sizeof(char));
  *RhsType = (char *) malloc(1*sizeof(char));
  (*RhsType)[0] = '\0';

  file = fopen (my_filename,"r");
  if (file==NULL)
  {
    fprintf(stderr,"cannot load %s\n", my_filename);
    EXIT(MOD_SI,FILE_ERR);
  }

  if (mm_read_banner(file, &matcode) != 0)
  {
    fprintf(stderr,"Could not process Matrix Market banner.\n");
    exit(1);
  }

#ifdef    TYPE_COMPLEX
  (*Type)[0] = 'C';
  if (!mm_is_complex(matcode))
  {
    fprintf(stderr, "\nWARNING : Matrix should be complex. Imaginary part will be 0.\n\n");
  }
#else  /* TYPE_COMPLEX */
  (*Type)[0] = 'R';
  if (mm_is_complex(matcode))
  {
    fprintf(stderr, "\nWARNING : Matrix should not be complex. Only real part will be taken.\n\n");
  }
#endif /* TYPE_COMPLEX */

  (*Type)[1] = 'U';
  if (mm_is_symmetric(matcode))
  {
    (*Type)[1] = 'S';
  }
  else {
    if (mm_is_hermitian(matcode))
    {
      (*Type)[1] = 'H';
    }
  }
  (*Type)[2] = 'A';
  (*Type)[3] = '\0';
  /* find out size of sparse matrix .... */

  if (mm_read_mtx_crd_size(file, &tmpnrow, &tmpncol, &tmpnnzero) !=0)
    exit(1);

  *Ncol = 0;
  *Nrow = 0;
  *Nnzero = tmpnnzero;
  
  /* Allocation memoire */
  tempcol = (pastix_int_t *) malloc((*Nnzero)*sizeof(pastix_int_t));
  templ2g = (pastix_int_t *) malloc((*Nnzero)*sizeof(pastix_int_t));
  temprow = (pastix_int_t *) malloc((*Nnzero)*sizeof(pastix_int_t));
  tempval = (pastix_float_t *) malloc((*Nnzero)*sizeof(pastix_float_t));

  if ((tempcol==NULL) || (temprow == NULL) || (tempval == NULL))
  {
    fprintf(stderr, "MatrixMarketRead : Not enough memory (Nnzero %ld)\n",(long)*Nnzero);
    EXIT(MOD_SI,OUTOFMEMORY_ERR);
  }

  /* Remplissage */
  {
    long temp1,temp2;
    double re,im;
    im = 0.0;

    if (mm_is_complex(matcode))
    {
      for (iter=0; iter<(*Nnzero); iter++)
      {
        if (4 != fscanf(file,"%ld %ld %lg %lg\n", &temp1, &temp2, &re, &im))
        {
          fprintf(stderr, "ERROR: reading matrix (line %ld)\n",
                  (long int)iter);
          exit(1);
        }

        iter2 = 0;
        column = temp2;
        while ( iter2 < *Ncol &&
                templ2g[iter2] < column)
          iter2++;
        if ( !(iter2 < *Ncol && (templ2g)[iter2] == column) )
          {
            while ( iter2 < *Ncol )
              {
                tmp = column;
                column = (templ2g)[iter2];
                (templ2g)[iter2] = tmp;
                iter2++;
              }
            (templ2g)[iter2] = column;
            (*Ncol)++;
          }

        temprow[iter]=(pastix_int_t)temp1;
        tempcol[iter]=(pastix_int_t)temp2;
#ifdef    TYPE_COMPLEX
        tempval[iter]=(pastix_float_t)(re+im*I);
#else  /* TYPE_COMPLEX */
        tempval[iter]=(pastix_float_t)(re);
#endif /* TYPE_COMPLEX */
      }
    }
    else
    {
      for (iter=0; iter<(*Nnzero); iter++)
      {
        if (3 != fscanf(file,"%ld %ld %lg\n", &temp1, &temp2, &re))
        {
          fprintf(stderr, "ERROR: reading matrix (line %ld)\n",
                  (long int)iter);
          exit(1);
        }

        iter2 = 0;
        column = temp2;
        while ( iter2 < *Ncol &&
                (templ2g)[iter2] < column)
          iter2++;
        if ( iter2 == *Ncol || (templ2g)[iter2] != column )
          {
            while ( iter2 < *Ncol )
              {
                tmp = (templ2g)[iter2];
                (templ2g)[iter2] = column;
                column = tmp;
                iter2++;
              }
            (templ2g)[iter2] = column;
            (*Ncol)++;
          }

        temprow[iter]=(pastix_int_t)temp1;
        tempcol[iter]=(pastix_int_t)temp2;
#ifdef    TYPE_COMPLEX
        tempval[iter]=(pastix_float_t)(re+im*I);
#else  /* TYPE_COMPLEX */
        tempval[iter]=(pastix_float_t)(re);
#endif /* TYPE_COMPLEX */
      }
    }
  }

  *Nrow = *Ncol;
  (*l2g) = (pastix_int_t *) malloc((*Ncol)*sizeof(pastix_int_t));
  memcpy(*l2g, templ2g, *Ncol*sizeof(pastix_int_t));
  free(templ2g);
  (*col) = (pastix_int_t *) malloc((*Ncol+1)*sizeof(pastix_int_t));
  memset(*col,0,(*Ncol+1)*sizeof(pastix_int_t));
  (*row) = (pastix_int_t *) malloc((*Nnzero)*sizeof(pastix_int_t));
  memset(*row,0,(*Nnzero)*sizeof(pastix_int_t));
  (*val) = (pastix_float_t *) malloc((*Nnzero)*sizeof(pastix_float_t));

  if (((*col)==NULL) || ((*row) == NULL) || ((*val) == NULL))
    {
      fprintf(stderr, "MatrixMarketRead : Not enough memory (Nnzero %ld)\n",
              (long)*Nnzero);
      EXIT(MOD_SI,OUTOFMEMORY_ERR);
    }

  /* Detection de la base */
  mincol = (*l2g)[0];
  maxcol = (*l2g)[*Ncol-1];
  if (sizeof(int) == sizeof(pastix_int_t))
    {
      MPI_Allreduce(&mincol, &baseval, 1,      MPI_INT, MPI_MIN, MPI_COMM_WORLD);
      MPI_Allreduce(&maxcol, &global_n_col, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    }
  else
    {
      MPI_Allreduce(&mincol, &baseval, 1,      MPI_LONG, MPI_MIN, MPI_COMM_WORLD);
      MPI_Allreduce(&maxcol, &global_n_col, 1, MPI_LONG, MPI_MAX, MPI_COMM_WORLD);
    }
  *Nrow = global_n_col;
  if (baseval == 0)
    {
      for(iter=0; iter<(*Nnzero); iter++)
        {
          tempcol[iter]++;
          temprow[iter]++;
        }
      for (iter = 0; iter < *Ncol; iter++)
        {
          (*l2g)[iter]++;
        }
    }

  if (baseval > 1 || baseval < 0)
    {
      fprintf(stderr, "Baseval > 1 || baseval < 0\n");
      exit(1);
    }
  baseval = 1;
  {
    /* Build loc2gloab */
    int inserted_column = 0;
    int iter2;
    int column;
    for (iter = 0; iter < (*Nnzero); iter ++)
      {
        iter2 = 0;
        column = tempcol[iter];
        while ( iter2 < inserted_column &&
                (*l2g)[iter2] < column)
          iter2++;
        if (iter2 < inserted_column && (*l2g)[iter2] == column)
          continue;

        while ( iter2 < inserted_column )
          {
            tmp = column;
            column = (*l2g)[iter2];
            (*l2g)[iter2] = tmp;
            iter2++;
          }
        (*l2g)[iter2] = column;
        inserted_column++;
        if (inserted_column == *Ncol)
          break;
      }
    assert(inserted_column == *Ncol);
  }

  {
    /* Build loc2glob */
    g2l = malloc(global_n_col*sizeof(pastix_int_t));
    for (iter = 0; iter < global_n_col; iter++)
      g2l[iter] = -1;
    for (iter = 0; iter < (*Ncol); iter ++)
      g2l[(*l2g)[iter]-1] = iter+1;
  }

  for (iter = 0; iter < (*Nnzero); iter ++)
    {
      (*col)[g2l[tempcol[iter]-1]-1]++;
    }

  total = baseval;
  for (iter = 0; iter < (*Ncol)+1; iter ++)
    {
      tmp = (*col)[iter];
      (*col)[iter]=total;
      total+=tmp;
    }

  for (iter = 0; iter < (*Nnzero); iter ++)
    {

      pos = (*col)[g2l[tempcol[iter]-1]-1]-1;
      limit = (*col)[g2l[tempcol[iter]-1]]-1;
      while((*row)[pos] != 0 && pos < limit)
        {
          pos++;
        }
      if (pos == limit)
        fprintf(stderr, "Erreur de lecture %ld %ld %ld\n",
                (long int)(*col)[g2l[tempcol[iter]-1]-1]-1,
                (long int)pos, (long int)limit);

      (*row)[pos] = temprow[iter];
      (*val)[pos] = tempval[iter];
    }

  memFree_null(tempval);
  memFree_null(temprow);
  memFree_null(tempcol);

  free(my_filename);
}