void Calculate_Droptol( sparse_matrix *A, real *droptol, real dtol )
{
  int i, j, k;
  real val;

  /* init droptol to 0 */
  for( i = 0; i < A->n; ++i )
    droptol[i] = 0;

  /* calculate sqaure of the norm of each row */
  for( i = 0; i < A->n; ++i ) {
    for( k = A->start[i]; k < A->start[i+1]-1; ++k ) {
      j = A->entries[k].j;
      val = A->entries[k].val;
      
      droptol[i] += val*val;
      droptol[j] += val*val;
    }
    
    val = A->entries[k].val; // diagonal entry
    droptol[i] += val*val;
  }

  /* calculate local droptol for each row */
  //fprintf( stderr, "droptol: " );
  for( i = 0; i < A->n; ++i ) {
    //fprintf( stderr, "%f-->", droptol[i] );
    droptol[i] = SQRT( droptol[i] ) * dtol;
    //fprintf( stderr, "%f  ", droptol[i] );
  }
  //fprintf( stderr, "\n" );
}