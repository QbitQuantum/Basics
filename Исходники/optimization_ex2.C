Number AssembleOptimization::objective (const NumericVector<Number> & soln,
                                        OptimizationSystem & /*sys*/)
{
  UniquePtr<NumericVector<Number> > AxU = soln.zero_clone();

  A_matrix->vector_mult(*AxU, soln);
  Number UTxAxU = AxU->dot(soln);

  Number UTxF = F_vector->dot(soln);

  return 0.5 * UTxAxU - UTxF;
}