void Stars(struct RUNPARAMS *param, struct CPUINFO *cpu, REAL dt, REAL aexp, int level, int is){
// ----------------------------------------------------------//
/// The stars creation function.\n
/// Scan if cell is allowed to form star\n
/// If true, compute how many star are needed\n
/// and add them to the linked list\n
// ----------------------------------------------------------//

#ifdef GSLRAND
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  param->stars->rpoiss=r;
#endif

  if(cpu->rank == RANK_DISP) printf("STARS\n");
  setStarsState(param, cpu, level);

  REAL mmax = 0;
  REAL percentvol =0;

  int n_unit_stars = 0;
  int n_part_stars = 0;
  int nstarsmax_in_one_cell=0;
  int nstarsmin_in_one_cell=1e3;

  initThresh(param, aexp);
  REAL mstars_level = setmStar(param,level);

  int iOct;
  for(iOct=0; iOct<cpu->locNoct[level-1]; iOct++){
    struct OCT *curoct=cpu->octList[level-1][iOct];

    int icell;
    for(icell=0;icell<8;icell++) {
      struct CELL *curcell = &curoct->cell[icell];

      if( testCond(curcell, param, aexp, level) ) {
  REAL dx = POW(2.0,-level);
	REAL xc=curoct->x+( icell    & 1)*dx+dx*0.5;
	REAL yc=curoct->y+((icell>>1)& 1)*dx+dx*0.5;
	REAL zc=curoct->z+( icell>>2    )*dx+dx*0.5;

  percentvol += POW(dx,3);

	int N = getNstars2create(curcell, param, dt, aexp, level,mstars_level);
	nstarsmax_in_one_cell = FMAX(nstarsmax_in_one_cell,N);
	nstarsmin_in_one_cell = FMIN(nstarsmin_in_one_cell,N);

	if(N>0.2*param->npartmax){
    printf("You are about to create more stars than 20 percent of npartmax N=%d nmax=%d on proc %d\n",(int)N,param->npartmax,cpu->rank);
    if(N>param->npartmax){
      printf("You are about to create more stars than npartmax N=%d nmax=%d on proc %d--> ABORT\n",(int)N,param->npartmax,cpu->rank);
      abort();
    }
  }

	//	if(N) printf("N_Rho_Temp_Seuil_z\t%d\t%e\t%e\t%e\t%e\n", N, curcell->field.d, curcell->rfield.temp, param->stars->thresh,1.0/aexp - 1.0  );


#ifdef MULTIPLESTARS
  struct Wtype init_state=curcell->field;
	int ipart;
	for (ipart=0;ipart< N; ipart++){
    addStar(curcell, &init_state, level, xc, yc, zc, cpu, dt, param, aexp, is,n_part_stars++, mstars_level);
    n_unit_stars++;
  }
#else
#ifdef CONTINUOUSSTARS

  REAL m = getMstars2create(curcell, param, dt, aexp, level);
  //if(m>mstars_level)
  {
    addStar(curcell, &curcell->field, level, xc, yc, zc, cpu, dt, param, aexp, is,n_part_stars++, m);
    n_unit_stars++;
  }
#else
  if(N){
    addStar(curcell, &curcell->field, level, xc, yc, zc, cpu, dt, param, aexp, is,n_part_stars++, N*mstars_level);
    n_unit_stars++;
  }
#endif // CONTINUOUSSTARS
#endif // MULTIPLESTARS

/*
if (N){
printWtype(&init_state);
printWtype(&curcell->field);
}
*/
      }
      mmax = FMAX(curcell->field.d, mmax);
    }
  }

#ifdef WMPI
  MPI_Allreduce(MPI_IN_PLACE,&n_unit_stars,1,MPI_INT,MPI_SUM,cpu->comm);
  MPI_Allreduce(MPI_IN_PLACE,&n_part_stars,1,MPI_INT,MPI_SUM,cpu->comm);
  MPI_Allreduce(MPI_IN_PLACE,&mmax,1,MPI_REEL,MPI_MAX,cpu->comm);
  MPI_Allreduce(MPI_IN_PLACE,&percentvol,1,MPI_REEL,MPI_SUM,cpu->comm);
  MPI_Allreduce(MPI_IN_PLACE,&nstarsmax_in_one_cell,1,MPI_INT,MPI_MAX,cpu->comm);
  MPI_Allreduce(MPI_IN_PLACE,&nstarsmin_in_one_cell,1,MPI_INT,MPI_MIN,cpu->comm);
#endif

  param->stars->n += n_part_stars;
  if(cpu->rank==RANK_DISP) {
    printf("Mmax=%e\tthresh=%e\tvol=%e\n", mmax, param->stars->thresh, percentvol );
    if (n_unit_stars){
      printf("%d stars added in %d particles on level %d --> min=%d max=%d \n", n_unit_stars, n_part_stars, level,nstarsmin_in_one_cell,nstarsmax_in_one_cell);
      printf("%d stars particles in total\n",param->stars->n);
    }
    if(cpu->trigstar==0 && param->stars->n>0) printf("FIRST_STARS at z=%e\n",1./aexp-1.);
    if(param->stars->n>0) cpu->trigstar=1;
  }

#ifdef GSLRAND
  gsl_rng_free (r);
#endif

}