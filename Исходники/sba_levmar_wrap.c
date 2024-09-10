/* Given a parameter vector p made up of the 3D coordinates of n points, compute in
 * jac the jacobian of the predicted measurements, i.e. the jacobian of the projections of 3D points in the m images.
 * The jacobian is approximated with the aid of finite differences and is returned in the order
 * (B_11, ..., B_1m, ..., B_n1, ..., B_nm), where B_ij=dx_ij/db_i (see HZ).
 * Notice that depending on idxij, some of the B_ij might be missing
 *
 * Problem-specific information is assumed to be stored in a structure pointed to by "dat".
 *
 * NOTE: This function is provided mainly for illustration purposes; in case that execution time is a concern,
 * the jacobian should be computed analytically
 */
static void sba_str_Qs_fdjac(
    double *p,                /* I: current parameter estimate, (n*pnp)x1 */
    struct sba_crsm *idxij,   /* I: sparse matrix containing the location of x_ij in hx */
    int    *rcidxs,           /* work array for the indexes of nonzero elements of a single sparse matrix row/column */
    int    *rcsubs,           /* work array for the subscripts of nonzero elements in a single sparse matrix row/column */
    double *jac,              /* O: array for storing the approximated jacobian */
    void   *dat)              /* I: points to a "wrap_str_data_" structure */
{
  register int i, j, ii, jj;
  double *pbi;
  register double *pB;
  //int m;
  int n, nnz, Bsz;

  double tmp;
  register double d, d1;

  struct wrap_str_data_ *fdjd;
  void (*proj)(int j, int i, double *bi, double *xij, void *adata);
  double *hxij, *hxxij;
  int pnp, mnp;
  void *adata;

  /* retrieve problem-specific information passed in *dat */
  fdjd=(struct wrap_str_data_ *)dat;
  proj=fdjd->proj;
  pnp=fdjd->pnp; mnp=fdjd->mnp;
  adata=fdjd->adata;

  n=idxij->nr;
  //m=idxij->nc;
  Bsz=mnp*pnp;

  /* allocate memory for hxij, hxxij */
  if((hxij=malloc(2*mnp*sizeof(double)))==NULL){
    fprintf(stderr, "memory allocation request failed in sba_str_Qs_fdjac()!\n");
    exit(1);
  }
  hxxij=hxij+mnp;

  /* compute B_ij */
  for(i=0; i<n; ++i){
    pbi=p+i*pnp; // i-th point parameters

    nnz=sba_crsm_row_elmidxs(idxij, i, rcidxs, rcsubs); /* find nonzero B_ij, j=0...m-1 */
    for(jj=0; jj<pnp; ++jj){
      /* determine d=max(SBA_DELTA_SCALE*|pbi[jj]|, SBA_MIN_DELTA), see HZ */
      d=(double)(SBA_DELTA_SCALE)*pbi[jj]; // force evaluation
      d=FABS(d);
      if(d<SBA_MIN_DELTA) d=SBA_MIN_DELTA;
      d1=1.0/d; /* invert so that divisions can be carried out faster as multiplications */

      for(j=0; j<nnz; ++j){
        (*proj)(rcsubs[j], i, pbi, hxij, adata); // evaluate supplied function on current solution

        tmp=pbi[jj];
        pbi[jj]+=d;
        (*proj)(rcsubs[j], i, pbi, hxxij, adata);
        pbi[jj]=tmp; /* restore */

        pB=jac + idxij->val[rcidxs[j]]*Bsz; // set pB to point to B_ij
        for(ii=0; ii<mnp; ++ii)
          pB[ii*pnp+jj]=(hxxij[ii]-hxij[ii])*d1;
      }
    }
  }

  free(hxij);
}