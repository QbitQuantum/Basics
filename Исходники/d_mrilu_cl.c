int mrilu_cl_field(     /* Return value is number of iterations taken */
    wilson_vector *src,	/* type wilson_vector (source vector - OVERWRITTEN!)*/
    wilson_vector *dest, /* type wilson_vector (answer and initial guess )*/
    quark_invert_control *qic,	/* parameters controlling inversion */
    void *dmp		/* parameters defining the Dirac matrix */
    )
{
  /* Unpack required members of the structures */
  int max_restarts = qic->nrestart;  /* Number of restarts */
  int nrestart = 0;
  int restart = qic->max;            /* Restart interval */
  int MaxCG = restart*qic->max;     /* maximum number of iterations */
  Real RsdCG = qic->resid;	/* desired residual -
                                 normalized as sqrt(r*r)/sqrt(src_e*src_e */
  Real RRsdCG = qic->relresid;       /* desired relative residual - */
  int flag = qic->start_flag;	/* 0: use a zero initial guess; 1: use dest */

  dirac_clover_param *dcp
    = (dirac_clover_param *)dmp;	/* Cast pass-through pointer */

  Real Kappa = dcp->Kappa;	/* hopping */
  Real Clov_c = dcp->Clov_c;	/* Perturbative clover coeff */
  Real U0 = dcp->U0;		/* Tadpole correction to Clov_c */
  /* End of unpacking required members of structures */

  wilson_vector *tmp=NULL,*mp=NULL,*r=NULL,*p=NULL;

  int N_iter;
  register int i;
  register site *s;
  Real size_src;
  double rsq, c;
  complex a, ctmp;
  double_complex d;
  register Real MKsq = -Kappa*Kappa;
  Real CKU0 = Kappa*Clov_c/(U0*U0*U0);
#ifdef CGTIME
  double dtime;
#endif
  msg_tag *tago[8],*tage[8];
  int is_startedo, is_startede;
  
  is_startedo = is_startede = 0;

  if(even_sites_on_node!=odd_sites_on_node){
    printf("Need same number of even and odd sites on each node\n");
    terminate(1);
  }
  
  /* Compute R_e and R_o and put in "clov" and "clov_diag" */
  compute_clov(gen_clov, CKU0);

  /* Invert R_o only, leaving R_e on even sites and 1/R_o on odd sites 
     in "clov" and "clov_diag" */
  compute_clovinv(gen_clov, ODD);

  /* now we can allocate temporary variables and copy them */
  /* PAD may be used to avoid cache trashing */
#define PAD 0
    
  tmp    = (wilson_vector *) malloc((sites_on_node+PAD)*sizeof(wilson_vector));
  mp     = (wilson_vector *) malloc((sites_on_node+PAD)*sizeof(wilson_vector));
  r      = (wilson_vector *) malloc((sites_on_node+PAD)*sizeof(wilson_vector));
  p      = r  + even_sites_on_node;

  if(tmp == NULL || mp == NULL || r == NULL ){
    printf("hopilu_cl_field(%d): No room for temporaries\n",this_node);
    terminate(1);
  }

  /* MR_ILU: */

#ifdef CGTIME
  dtime = -dclock();
#endif
  
  /* now we copy src to temporary */
  FORALLSITES(i,s) {
    r[i] = src[i];
  }

  /* Transform source - result is in r (even) - and dest (odd) */


  size_src = ilu_xfm_source(dest, r, mp, Kappa, &is_startede, tage);

#if 0
  /* src = L^(-1)*src */
  mult_this_ldu_field(gen_clov, r, mp, ODD);
  dslash_w_field_special(mp, mp, PLUS, EVEN, tage, is_startede);
  is_startede = 1;

  /* Normalisation  */
  rsq = 0.0;

  FOREVENSITESDOMAIN(i,s) {
    scalar_mult_add_wvec( &(r[i]), &(mp[i]), Kappa, &(r[i]) );
    rsq += (double)magsq_wvec( &(r[i]) );
    /* Save transformed source: Overwrite src on even sites */
    copy_wvec( &(r[i]), &(src[i]) );
  }