int soclcp_driver(SecondOrderConeLinearComplementarityProblem* problem,
                  double *r, double *v,
                  SolverOptions* options,
                  NumericsOptions* global_options)
{
  if(options == NULL)
    numericsError("soclcp_driver", "null input for solver and/or global options");

  int setnumericsoptions=0;

  /* Set global options */
  if(global_options)
  {
    setNumericsOptions(global_options);
    options->numericsOptions = (NumericsOptions*) malloc(sizeof(NumericsOptions));
    options->numericsOptions->verboseMode = global_options->verboseMode;
    setnumericsoptions=1;
  }

  int NoDefaultOptions = options->isSet; /* true(1) if the SolverOptions structure has been filled in else false(0) */

  if(!NoDefaultOptions)
    readSolverOptions(3, options);

  if(verbose > 0)
    printSolverOptions(options);

  /* Solver name */
  /*char * name = options->solverName;*/

  int info = -1 ;

  /* Check for trivial case */
  info = soclcp_checkTrivialCase(problem, v, r, options);


  if(info == 0)
    return info;


  switch(options->solverId)
  {
  /* Non Smooth Gauss Seidel (NSGS) */
  case SICONOS_SOCLCP_NSGS:
  {
    snPrintf(1, options,
             " ========================== Call NSGS solver for Second Order Cone LCP problem ==========================\n");
    soclcp_nsgs(problem, r , v , &info , options);
    break;
  }
  /* case SICONOS_SOCLCP_NSGSV: */
  /* { */
  /*   snPrintf(1, options, */
  /*            " ========================== Call NSGSV solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_nsgs_v(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  /* /\* Proximal point algorithm *\/ */
  /* case SICONOS_SOCLCP_PROX: */
  /* { */
  /*   snPrintf(1, options, */
  /*            " ========================== Call PROX (Proximal Point) solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_proximal(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  /* /\* Tresca Fixed point algorithm *\/ */
  /* case SICONOS_SOCLCP_TFP: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call TFP (Tresca Fixed Point) solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_TrescaFixedPoint(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  case SICONOS_SOCLCP_VI_FPP:
  {
    snPrintf(1, options,
             " ========================== Call VI_FixedPointProjection (VI_FPP) solver for Second Order Cone LCP problem ==========================\n");
    soclcp_VI_FixedPointProjection(problem, r , v , &info , options);
    break;
  }
  /* VI Extra Gradient algorithm */
  case SICONOS_SOCLCP_VI_EG:
  {
    snPrintf(1, options,
             " ========================== Call VI_ExtraGradient (VI_EG) solver for Second Order Cone LCP problem ==========================\n");
    soclcp_VI_ExtraGradient(problem, r , v , &info , options);
    break;
  }
  /* /\* Hyperplane Projection algorithm *\/ */
  /* case SICONOS_SOCLCP_HP: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call Hyperplane Projection (HP) solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_HyperplaneProjection(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  /* /\* Alart Curnier in local coordinates *\/ */
  /* case SICONOS_SOCLCP_LOCALAC: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call Alart Curnier solver for Second Order Cone LCP problem ==========================\n"); */
  /*   if (problem->M->matrix0) */
  /*   { */
  /*     soclcp_localAlartCurnier(problem, r , v , &info , options); */
  /*   } */
  /*   else */
  /*   { */
  /*     soclcp_localAlartCurnier(problem, r , v , &info , options); */
  /*   } */
  /*   break; */
  /* } */
  /* /\* Fischer Burmeister in local coordinates *\/ */
  /* case SICONOS_SOCLCP_LOCALFB: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call Fischer Burmeister solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_localFischerBurmeister(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  /* case SICONOS_SOCLCP_QUARTIC_NU: */
  /* case SICONOS_SOCLCP_QUARTIC: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call Quartic solver for Second Order Cone LCP problem ==========================\n"); */
  /*   soclcp_unitary_enumerative(problem, r , v , &info , options); */
  /*   break; */
  /* } */
  /* case SICONOS_SOCLCP_AlartCurnierNewton: */
  /* case SICONOS_SOCLCP_DampedAlartCurnierNewton: */
  /* { */
  /*   snPrintf(1, options,  */
  /*            " ========================== Call Quartic solver for Second Order Cone LCP problem ==========================\n"); */
  /*   info =soclcp_Newton_solve(problem, r , options); */
  /*   break; */
  /* } */
  default:
  {
    fprintf(stderr, "Numerics, SecondOrderConeLinearComplementarity_driver failed. Unknown solver.\n");
    exit(EXIT_FAILURE);

  }
  }

  if(setnumericsoptions)
  {
    free(options->numericsOptions);
    options->numericsOptions = NULL;
  }

  return info;

}