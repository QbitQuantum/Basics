/*
 * This function returns the solution of Ax = b
 *
 * The function employs LU decomposition followed by forward/back substitution (see 
 * also the LAPACK-based LU solver above)
 *
 * A is mxm, b is mx1
 *
 * The function returns 0 in case of error, 1 if successful
 *
 * This function is often called repetitively to solve problems of identical
 * dimensions. To avoid repetitive malloc's and free's, allocated memory is
 * retained between calls and free'd-malloc'ed when not of the appropriate size.
 * A call with NULL as the first argument forces this memory to be released.
 */
int AX_EQ_B_LU(LM_REAL *A, LM_REAL *B, LM_REAL *x, int m)
{
__STATIC__ void *buf=NULL;
__STATIC__ int buf_sz=0;

register int i, j, k;
int *idx, maxi=-1, idx_sz, a_sz, work_sz, tot_sz;
LM_REAL *a, *work, max, sum, tmp;

    if(!A)
#ifdef LINSOLVERS_RETAIN_MEMORY
    {
      if(buf) free(buf);
      buf=NULL;
      buf_sz=0;

      return 1;
    }
#else
    return 1; /* NOP */
#endif /* LINSOLVERS_RETAIN_MEMORY */
   
  /* calculate required memory size */
  idx_sz=m;
  a_sz=m*m;
  work_sz=m;
  tot_sz=(a_sz+work_sz)*sizeof(LM_REAL) + idx_sz*sizeof(int); /* should be arranged in that order for proper doubles alignment */

  // Check inputs for validity
  for(i=0; i<a_sz; i++)
     if (!LM_FINITE(A[i]))
        return 0;


#ifdef LINSOLVERS_RETAIN_MEMORY
  if(tot_sz>buf_sz){ /* insufficient memory, allocate a "big" memory chunk at once */
    if(buf) free(buf); /* free previously allocated memory */

    buf_sz=tot_sz;
    buf=(void *)malloc(tot_sz);
    if(!buf){
      fprintf(stderr, RCAT("memory allocation in ", AX_EQ_B_LU) "() failed!\n");
      exit(1);
    }
  }
#else
    buf_sz=tot_sz;
    buf=(void *)malloc(tot_sz);
    if(!buf){
      fprintf(stderr, RCAT("memory allocation in ", AX_EQ_B_LU) "() failed!\n");
      exit(1);
    }
#endif /* LINSOLVERS_RETAIN_MEMORY */

  a=(LM_REAL*)buf;
  work=a+a_sz;
  idx=(int *)(work+work_sz);

  /* avoid destroying A, B by copying them to a, x resp. */
  memcpy(a, A, a_sz*sizeof(LM_REAL));
  memcpy(x, B, m*sizeof(LM_REAL));

  /* compute the LU decomposition of a row permutation of matrix a; the permutation itself is saved in idx[] */
	for(i=0; i<m; ++i){
		max=0.0;
		for(j=0; j<m; ++j)
			if((tmp=FABS(a[i*m+j]))>max)
        max=tmp;
		  if(max==0.0){
        fprintf(stderr, RCAT("Singular matrix A in ", AX_EQ_B_LU) "()!\n");
#ifndef LINSOLVERS_RETAIN_MEMORY
        free(buf);
#endif

        return 0;
      }
		  work[i]=LM_CNST(1.0)/max;
	}

	for(j=0; j<m; ++j){
		for(i=0; i<j; ++i){
			sum=a[i*m+j];
			for(k=0; k<i; ++k)
        sum-=a[i*m+k]*a[k*m+j];
			a[i*m+j]=sum;
		}
		max=0.0;
		for(i=j; i<m; ++i){
			sum=a[i*m+j];
			for(k=0; k<j; ++k)
        sum-=a[i*m+k]*a[k*m+j];
			a[i*m+j]=sum;
			if((tmp=work[i]*FABS(sum))>=max){
				max=tmp;
				maxi=i;
			}
		}
		if(j!=maxi){
			for(k=0; k<m; ++k){
				tmp=a[maxi*m+k];
				a[maxi*m+k]=a[j*m+k];
				a[j*m+k]=tmp;
			}
			work[maxi]=work[j];
		}
		idx[j]=maxi;
		if(a[j*m+j]==0.0)
      a[j*m+j]=LM_REAL_EPSILON;
		if(j!=m-1){
			tmp=LM_CNST(1.0)/(a[j*m+j]);
			for(i=j+1; i<m; ++i)
        a[i*m+j]*=tmp;
		}
	}

  /* The decomposition has now replaced a. Solve the linear system using
   * forward and back substitution
   */
	for(i=k=0; i<m; ++i){
		j=idx[i];
		sum=x[j];
		x[j]=x[i];
		if(k!=0)
			for(j=k-1; j<i; ++j)
        sum-=a[i*m+j]*x[j];
		else
      if(sum!=0.0)
			  k=i+1;
		x[i]=sum;
	}

	for(i=m-1; i>=0; --i){
		sum=x[i];
		for(j=i+1; j<m; ++j)
      sum-=a[i*m+j]*x[j];
		x[i]=sum/a[i*m+i];
	}

#ifndef LINSOLVERS_RETAIN_MEMORY
  free(buf);
#endif

  return 1;
}