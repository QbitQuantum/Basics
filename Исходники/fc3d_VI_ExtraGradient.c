void fc3d_VI_ExtraGradient(FrictionContactProblem* problem, double *reaction, double *velocity, int* info, SolverOptions* options)
{
  /* Number of contacts */
  int nc = problem->numberOfContacts;
  /* Dimension of the problem */
  int n = 3 * nc;


  VariationalInequality *vi = (VariationalInequality *)malloc(sizeof(VariationalInequality));

  //vi.self = &vi;
  vi->F = &Function_VI_FC3D;
  vi->ProjectionOnX = &Projection_VI_FC3D;

  int iter=0;
  double error=1e24;

  FrictionContactProblem_as_VI *fc3d_as_vi= (FrictionContactProblem_as_VI*)malloc(sizeof(FrictionContactProblem_as_VI));
  vi->env =fc3d_as_vi ;
  vi->size =  n;


  /*Set the norm of the VI to the norm of problem->q  */
  vi->normVI= cblas_dnrm2(n , problem->q , 1);
  vi->istheNormVIset=1;

  fc3d_as_vi->vi = vi;
  fc3d_as_vi->fc3d = problem;
  /* frictionContact_display(fc3d_as_vi->fc3d); */

  SolverOptions * visolver_options = (SolverOptions *) malloc(sizeof(SolverOptions));
  variationalInequality_setDefaultSolverOptions(visolver_options,
                                                SICONOS_VI_EG);

  int isize = options->iSize;
  int dsize = options->dSize;
  int vi_isize = visolver_options->iSize;
  int vi_dsize = visolver_options->dSize;

  if (isize != vi_isize )
  {
    printf("size prolem in fc3d_VI_ExtraGradient\n");
  }
  if (dsize != vi_dsize )
  {
    printf("size prolem in fc3d_VI_ExtraGradient\n");
  }
  /* int i; */
  /* for (i = 0; i < isize; i++) */
  /* { */
  /*   visolver_options->iparam[i] = options->iparam[i] ; */
  /* } */
  /* for (i = 0; i < dsize; i++) */
  /* { */
  /*   visolver_options->dparam[i] = options->dparam[i] ; */
  /* } */
  int i;
  for (i = 0; i < isize; i++)
  {
    if (options->iparam[i] != 0 )
      visolver_options->iparam[i] = options->iparam[i] ;
  }
  for (i = 0; i < dsize; i++)
  {
    if (fabs(options->dparam[i]) >= 1e-24 )
      visolver_options->dparam[i] = options->dparam[i] ;
  }

  variationalInequality_ExtraGradient(vi, reaction, velocity , info , visolver_options);



  /* **** Criterium convergence **** */
  fc3d_compute_error(problem, reaction , velocity, options->dparam[0], options, &error);

  /* for (i =0; i< n ; i++) */
  /* { */
  /*   printf("reaction[%i]=%f\t",i,reaction[i]);    printf("velocity[%i]=F[%i]=%f\n",i,i,velocity[i]); */
  /* } */

  error = visolver_options->dparam[1];
  iter = visolver_options->iparam[7];

  options->dparam[1] = error;
  options->iparam[7] = iter;


  if (verbose > 0)
  {
    printf("----------------------------------- FC3D - VI Extra Gradient (VI_EG) - #Iteration %i Final Residual = %14.7e\n", iter, error);
  }
  free(vi);

  deleteSolverOptions(visolver_options);
  free(visolver_options);
  visolver_options=NULL;
  free(fc3d_as_vi);



}