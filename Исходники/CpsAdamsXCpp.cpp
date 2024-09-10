static void PrintFinalStats(CPodes& cpode)
{
  int nst, nfe, nni, ncfn, netf;
  Real h0u;
  int flag;
  
  flag = cpode.getActualInitStep(&h0u);
  flag = cpode.getNumSteps(&nst);
  flag = cpode.getNumFctEvals(&nfe);
  flag = cpode.getNumErrTestFails(&netf);
  flag = cpode.getNumNonlinSolvIters(&nni);
  flag = cpode.getNumNonlinSolvConvFails(&ncfn);

  printf("\n Final statistics:\n\n");
  printf(" Number of steps                          = %4d \n", nst);
  printf(" Number of f-s                            = %4d \n", nfe);
  printf(" Number of nonlinear iterations           = %4d \n", nni);
  printf(" Number of nonlinear convergence failures = %4d \n", ncfn);
  printf(" Number of error test failures            = %4d \n", netf);
  printf(" Initial step size                        = %g \n\n", h0u);

}