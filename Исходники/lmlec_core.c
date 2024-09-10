/*
 * This function implements an elimination strategy for linearly constrained
 * optimization problems. The strategy relies on QR decomposition to transform
 * an optimization problem constrained by Ax=b to an equivalent, unconstrained
 * one. Also referred to as "null space" or "reduced Hessian" method.
 * See pp. 430-433 (chap. 15) of "Numerical Optimization" by Nocedal-Wright
 * for details.
 *
 * A is mxn with m<=n and rank(A)=m
 * Two matrices Y and Z of dimensions nxm and nx(n-m) are computed from A^T so that
 * their columns are orthonormal and every x can be written as x=Y*b + Z*x_z=
 * c + Z*x_z, where c=Y*b is a fixed vector of dimension n and x_z is an
 * arbitrary vector of dimension n-m. Then, the problem of minimizing f(x)
 * subject to Ax=b is equivalent to minimizing f(c + Z*x_z) with no constraints.
 * The computed Y and Z are such that any solution of Ax=b can be written as
 * x=Y*x_y + Z*x_z for some x_y, x_z. Furthermore, A*Y is nonsingular, A*Z=0
 * and Z spans the null space of A.
 *
 * The function accepts A, b and computes c, Y, Z. If b or c is NULL, c is not
 * computed. Also, Y can be NULL in which case it is not referenced.
 * The function returns 0 in case of error, A's computed rank if successfull
 *
 */
static int LMLEC_ELIM(LM_REAL *A, LM_REAL *b, LM_REAL *c, LM_REAL *Y, LM_REAL *Z, int m, int n)
{
static LM_REAL eps=CNST(-1.0);

LM_REAL *buf=NULL;
LM_REAL *a, *tau, *work, *r;
register LM_REAL tmp;
int a_sz, jpvt_sz, tau_sz, r_sz, Y_sz, worksz;
int info, rank, *jpvt, tot_sz, mintmn, tm, tn;
register int i, j, k;

  if(m>n){
    fprintf(stderr, RCAT("matrix of constraints cannot have more rows than columns in", LMLEC_ELIM) "()!\n");
    exit(1);
  }

  tm=n; tn=m; // transpose dimensions
  mintmn=m;

  /* calculate required memory size */
  a_sz=tm*tm; // tm*tn is enough for xgeqp3()
  jpvt_sz=tn;
  tau_sz=mintmn;
  r_sz=mintmn*mintmn; // actually smaller if a is not of full row rank
  worksz=2*tn+(tn+1)*32; // more than needed
  Y_sz=(Y)? 0 : tm*tn;

  tot_sz=jpvt_sz*sizeof(int) + (a_sz + tau_sz + r_sz + worksz + Y_sz)*sizeof(LM_REAL);
  buf=(LM_REAL *)malloc(tot_sz); /* allocate a "big" memory chunk at once */
  if(!buf){
    fprintf(stderr, RCAT("Memory allocation request failed in ", LMLEC_ELIM) "()\n");
    exit(1);
  }

  a=(LM_REAL *)buf;
  jpvt=(int *)(a+a_sz);
  tau=(LM_REAL *)(jpvt + jpvt_sz);
  r=tau+tau_sz;
  work=r+r_sz;
  if(!Y) Y=work+worksz;

  /* copy input array so that LAPACK won't destroy it. Note that copying is
   * done in row-major order, which equals A^T in column-major
   */
  for(i=0; i<tm*tn; ++i)
      a[i]=A[i];

  /* clear jpvt */
  for(i=0; i<jpvt_sz; ++i) jpvt[i]=0;

  /* rank revealing QR decomposition of A^T*/
  GEQP3((int *)&tm, (int *)&tn, a, (int *)&tm, jpvt, tau, work, (int *)&worksz, &info);
  //dgeqpf_((int *)&tm, (int *)&tn, a, (int *)&tm, jpvt, tau, work, &info);
  /* error checking */
  if(info!=0){
    if(info<0){
      fprintf(stderr, RCAT(RCAT("LAPACK error: illegal value for argument %d of ", GEQP3) " in ", LMLEC_ELIM) "()\n", -info);
      exit(1);
    }
    else if(info>0){
      fprintf(stderr, RCAT(RCAT("unknown LAPACK error (%d) for ", GEQP3) " in ", LMLEC_ELIM) "()\n", info);
      free(buf);
      return 0;
    }
  }
  /* the upper triangular part of a now contains the upper triangle of the unpermuted R */

  if(eps<0.0){
    LM_REAL aux;

    /* compute machine epsilon. DBL_EPSILON should do also */
    for(eps=CNST(1.0); aux=eps+CNST(1.0), aux-CNST(1.0)>0.0; eps*=CNST(0.5))
                              ;
    eps*=CNST(2.0);
  }

  tmp=tm*CNST(10.0)*eps*FABS(a[0]); // threshold. tm is max(tm, tn)
  tmp=(tmp>CNST(1E-12))? tmp : CNST(1E-12); // ensure that threshold is not too small
  /* compute A^T's numerical rank by counting the non-zeros in R's diagonal */
  for(i=rank=0; i<mintmn; ++i)
    if(a[i*(tm+1)]>tmp || a[i*(tm+1)]<-tmp) ++rank; /* loop across R's diagonal elements */
    else break; /* diagonal is arranged in absolute decreasing order */

  if(rank<tn){
    fprintf(stderr, RCAT("\nConstraints matrix in ",  LMLEC_ELIM) "() is not of full row rank (i.e. %d < %d)!\n"
            "Make sure that you do not specify redundant or inconsistent constraints.\n\n", rank, tn);
    exit(1);
  }

  /* compute the permuted inverse transpose of R */
  /* first, copy R from the upper triangular part of a to r. R is rank x rank */
  for(j=0; j<rank; ++j){
    for(i=0; i<=j; ++i)
      r[i+j*rank]=a[i+j*tm];
    for(i=j+1; i<rank; ++i)
      r[i+j*rank]=0.0; // lower part is zero
  }

  /* compute the inverse */
  TRTRI("U", "N", (int *)&rank, r, (int *)&rank, &info);
  /* error checking */
  if(info!=0){
    if(info<0){
      fprintf(stderr, RCAT(RCAT("LAPACK error: illegal value for argument %d of ", TRTRI) " in ", LMLEC_ELIM) "()\n", -info);
      exit(1);
    }
    else if(info>0){
      fprintf(stderr, RCAT(RCAT("A(%d, %d) is exactly zero for ", TRTRI) " (singular matrix) in ", LMLEC_ELIM) "()\n", info, info);
      free(buf);
      return 0;
    }
  }
  /* then, transpose r in place */
  for(i=0; i<rank; ++i)
    for(j=i+1; j<rank; ++j){
      tmp=r[i+j*rank];
      k=j+i*rank;
      r[i+j*rank]=r[k];
      r[k]=tmp;
  }

  /* finally, permute R^-T using Y as intermediate storage */
  for(j=0; j<rank; ++j)
    for(i=0, k=jpvt[j]-1; i<rank; ++i)
      Y[i+k*rank]=r[i+j*rank];

  for(i=0; i<rank*rank; ++i) // copy back to r
    r[i]=Y[i];

  /* resize a to be tm x tm, filling with zeroes */
  for(i=tm*tn; i<tm*tm; ++i)
    a[i]=0.0;

  /* compute Q in a as the product of elementary reflectors. Q is tm x tm */
  ORGQR((int *)&tm, (int *)&tm, (int *)&mintmn, a, (int *)&tm, tau, work, &worksz, &info);
  /* error checking */
  if(info!=0){
    if(info<0){
      fprintf(stderr, RCAT(RCAT("LAPACK error: illegal value for argument %d of ", ORGQR) " in ", LMLEC_ELIM) "()\n", -info);
      exit(1);
    }
    else if(info>0){
      fprintf(stderr, RCAT(RCAT("unknown LAPACK error (%d) for ", ORGQR) " in ", LMLEC_ELIM) "()\n", info);
      free(buf);
      return 0;
    }
  }

  /* compute Y=Q_1*R^-T*P^T. Y is tm x rank */
  for(i=0; i<tm; ++i)
    for(j=0; j<rank; ++j){
      for(k=0, tmp=0.0; k<rank; ++k)
        tmp+=a[i+k*tm]*r[k+j*rank];
      Y[i*rank+j]=tmp;
    }

  if(b && c){
    /* compute c=Y*b */
    for(i=0; i<tm; ++i){
      for(j=0, tmp=0.0; j<rank; ++j)
        tmp+=Y[i*rank+j]*b[j];

      c[i]=tmp;
    }
  }

  /* copy Q_2 into Z. Z is tm x (tm-rank) */
  for(j=0; j<tm-rank; ++j)
    for(i=0, k=j+rank; i<tm; ++i)
      Z[i*(tm-rank)+j]=a[i+k*tm];

  free(buf);

  return rank;
}