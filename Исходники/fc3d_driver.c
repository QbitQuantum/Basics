int fc3d_driver(FrictionContactProblem* problem,
                             double *reaction, double *velocity,
                             SolverOptions* options,
                             NumericsOptions* global_options)
{
  if (options == NULL)
    numericsError("fc3d_driver", "null input for solver and/or global options");

  int setnumericsoptions=0;

  /* Set global options */
  if (global_options)
  {
    setNumericsOptions(global_options);
    options->numericsOptions = (NumericsOptions*) malloc(sizeof(NumericsOptions));
    options->numericsOptions->verboseMode = global_options->verboseMode;
    setnumericsoptions=1;
  }

  int NoDefaultOptions = options->isSet; /* true(1) if the SolverOptions structure has been filled in else false(0) */

  if (!NoDefaultOptions)
    readSolverOptions(3, options);

  if (verbose > 0)
    printSolverOptions(options);

  /* Solver name */
  /*char * name = options->solverName;*/

  int info = -1 ;

  if (problem->dimension != 3)
    numericsError("fc3d_driver", "Dimension of the problem : problem-> dimension is not compatible or is not set");

  /* Check for trivial case */
  info = checkTrivialCase(problem, velocity, reaction, options);


  if (info == 0)
    goto exit;


  switch (options->solverId)
  {
    /* Non Smooth Gauss Seidel (NSGS) */
  case SICONOS_FRICTION_3D_NSGS:
  {
    snPrintf(1, options,
             " ========================== Call NSGS solver for Friction-Contact 3D problem ==========================\n");
    fc3d_nsgs(problem, reaction , velocity , &info , options);
    break;
  }
  case SICONOS_FRICTION_3D_NSGSV:
  {
    snPrintf(1, options,
             " ========================== Call NSGSV solver for Friction-Contact 3D problem ==========================\n");
    fc3d_nsgs_velocity(problem, reaction , velocity , &info , options);
    break;
  }
  /* Proximal point algorithm */
  case SICONOS_FRICTION_3D_PROX:
  {
    snPrintf(1, options,
             " ========================== Call PROX (Proximal Point) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_proximal(problem, reaction , velocity , &info , options);
    break;
  }
  /* Tresca Fixed point algorithm */
  case SICONOS_FRICTION_3D_TFP:
  {
    snPrintf(1, options,
             " ========================== Call TFP (Tresca Fixed Point) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_TrescaFixedPoint(problem, reaction , velocity , &info , options);
    break;
  }
  /* ACLM Fixed point algorithm */
  case SICONOS_FRICTION_3D_ACLMFP:
  {
    snPrintf(1, options,
             " ========================== Call ACLM (Acary Cadoux Lemarechal Malick Fixed Point) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_ACLMFixedPoint(problem, reaction , velocity , &info , options);
    break;
  }
  /* SOCLCP Fixed point algorithm */
  case SICONOS_FRICTION_3D_SOCLCP:
  {
    snPrintf(1, options,
             " ========================== Call SOCLCP solver for Friction-Contact 3D problem (Associated one) ==========================\n");
    fc3d_SOCLCP(problem, reaction , velocity , &info , options);
    break;
  }
  /* De Saxce Fixed point algorithm */
  case SICONOS_FRICTION_3D_DSFP:
  {
    snPrintf(1, options,
            " ========================== Call DeSaxce Fixed Point (DSFP) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_DeSaxceFixedPoint(problem, reaction , velocity , &info , options);
    break;
  }
  /* Fixed point projection algorithm */
  case SICONOS_FRICTION_3D_FPP:
  {
    snPrintf(1, options,
            " ========================== Call Fixed Point Projection (FPP) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_fixedPointProjection(problem, reaction , velocity , &info , options);
    break;
  }

  /* Extra Gradient algorithm */
  case SICONOS_FRICTION_3D_EG:
  {
    snPrintf(1, options,
            " ========================== Call ExtraGradient (EG) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_ExtraGradient(problem, reaction , velocity , &info , options);
    break;
  }
  /* VI Fixed Point Projection algorithm */
  case SICONOS_FRICTION_3D_VI_FPP:
  {
    snPrintf(1, options,
            " ========================== Call VI_FixedPointProjection (VI_FPP) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_VI_FixedPointProjection(problem, reaction , velocity , &info , options);
    break;
  }
  /* VI Extra Gradient algorithm */
  case SICONOS_FRICTION_3D_VI_EG:
  {
    snPrintf(1, options,
            " ========================== Call VI_ExtraGradient (VI_EG) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_VI_ExtraGradient(problem, reaction , velocity , &info , options);
    break;
  }
  /* Hyperplane Projection algorithm */
  case SICONOS_FRICTION_3D_HP:
  {
    snPrintf(1, options,
            " ========================== Call Hyperplane Projection (HP) solver for Friction-Contact 3D problem ==========================\n");
    fc3d_HyperplaneProjection(problem, reaction , velocity , &info , options);
    break;
  }
  /* Alart Curnier in local coordinates */
  case SICONOS_FRICTION_3D_NSN_AC:
  {
    snPrintf(1, options,
            " ========================== Call Alart Curnier solver for Friction-Contact 3D problem ==========================\n");
    if (problem->M->matrix0)
    {
      fc3d_nonsmooth_Newton_AlartCurnier(problem, reaction , velocity , &info , options);
    }
    else
    {
      fc3d_nonsmooth_Newton_AlartCurnier(problem, reaction , velocity , &info , options);
    }
    break;
  }
  /* Fischer Burmeister in local coordinates */
  case SICONOS_FRICTION_3D_NSN_FB:
  {
    snPrintf(1, options,
            " ========================== Call Fischer Burmeister solver for Friction-Contact 3D problem ==========================\n");
    fc3d_nonsmooth_Newton_FischerBurmeister(problem, reaction , velocity , &info , options);
    break;
  }
  case SICONOS_FRICTION_3D_NSN_NM:
  {
    snPrintf(1, options,
            " ========================== Call natural map solver for Friction-Contact 3D problem ==========================\n");
    fc3d_nonsmooth_Newton_NaturalMap(problem, reaction , velocity , &info , options);
    break;
  }
  case SICONOS_FRICTION_3D_ONECONTACT_QUARTIC_NU:
  case SICONOS_FRICTION_3D_ONECONTACT_QUARTIC:
  {
    snPrintf(1, options,
            " ========================== Call Quartic solver for Friction-Contact 3D problem ==========================\n");
    fc3d_unitary_enumerative(problem, reaction , velocity , &info , options);
    break;
  }
  case SICONOS_FRICTION_3D_ONECONTACT_NSN_AC:
  case SICONOS_FRICTION_3D_ONECONTACT_NSN_AC_GP:
  {
    snPrintf(1, options,
            " ========================== Call Newton-based solver for one contact Friction-Contact 3D problem ==========================\n");
    fc3d_onecontact_nonsmooth_Newton_solvers_initialize(problem, problem, options);
    info = fc3d_onecontact_nonsmooth_Newton_solvers_solve(problem, reaction , options);
    break;
  }
  case SICONOS_FRICTION_3D_ONECONTACT_ProjectionOnConeWithLocalIteration:
  {
    snPrintf(1, options,
            " ========================== Call Projection on cone solver for one contact Friction-Contact 3D problem ==========================\n");
    fc3d_projectionOnConeWithLocalIteration_initialize(problem, problem, options);
    info = fc3d_projectionOnConeWithLocalIteration_solve(problem, reaction , options);
    fc3d_projectionOnConeWithLocalIteration_free(problem, problem, options);

    break;
  }
  case SICONOS_FRICTION_3D_GAMS_PATH:
  {
    snPrintf(1, options,
            " ========================== Call PATH solver via GAMS for an AVI Friction-Contact 3D problem ==========================\n");
    fc3d_AVI_gams_path(problem, reaction , velocity, &info, options);
    break;
  }
  case SICONOS_FRICTION_3D_GAMS_PATHVI:
  {
    snPrintf(1, options,
            " ========================== Call PATHVI solver via GAMS for an AVI Friction-Contact 3D problem ==========================\n");
    fc3d_AVI_gams_pathvi(problem, reaction , velocity, &info, options);
    break;
  }
  case SICONOS_FRICTION_3D_GAMS_LCP_PATH:
  {
    snPrintf(1, options,
            " ========================== Call PATH solver via GAMS for an LCP-based reformulation of the AVI Friction-Contact 3D problem ==========================\n");
    fc3d_lcp_gams_path(problem, reaction , velocity, &info, options);
    break;
  }
  case SICONOS_FRICTION_3D_GAMS_LCP_PATHVI:
  {
    snPrintf(1, options,
            " ========================== Call PATHVI solver via GAMS for an LCP-based reformulation of the AVI Friction-Contact 3D problem ==========================\n");
    fc3d_lcp_gams_pathvi(problem, reaction , velocity, &info, options);
    break;
  }
  default:
  {
    fprintf(stderr, "Numerics, fc3d_driver failed. Unknown solver.\n");
    exit(EXIT_FAILURE);

  }
  }

exit:

  if (setnumericsoptions)
  {
      free(options->numericsOptions);
      options->numericsOptions = NULL;
  }

  return info;

}