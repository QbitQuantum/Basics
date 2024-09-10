std::vector<std::complex<double> >
PolyBase::calcRoots(const double epsilon)
  /**
    Calculate all the roots of the polynominal.
    Uses the GSL which uses a Hessian reduction of the 
    characteristic compainion matrix.
    \f[ A= \left( -a_{m-1}/a_m -a_{m-2}/a_m ... -a_0/a_m \right) \f]
    where the matrix component below A is the Indenty.
    However, GSL requires that the input coefficient is a_m == 1,
    hence the call to this->compress().
    @param epsilon :: tolerance factor (-ve to use default) 
    @return roots (not sorted/uniqued)
  */
{
  compress(epsilon);
  std::vector<std::complex<double> > Out(iDegree);
  // Zero State:
  if (iDegree==0)
    return Out;
  
  // x+a_0 =0 
  if (iDegree==1)
    {
      Out[0]=std::complex<double>(-afCoeff[0]);
      return Out;
    }
  // x^2+a_1 x+c = 0
  if (iDegree==2)
    {
      solveQuadratic(Out[0],Out[1]);
      return Out;
    }

  // x^3+a_2 x^2+ a_1 x+c=0
  if (iDegree==2)
    {
      solveCubic(Out[0],Out[1],Out[2]);
      return Out;
    }
  // THERE IS A QUARTIC / QUINTIC Solution availiable but...
  // WS contains the the hessian matrix if required (eigenvalues/vectors)
  //
  gsl_poly_complex_workspace* WS
    (gsl_poly_complex_workspace_alloc(iDegree+1));
  double* RZ=new double[2*(iDegree+1)];
  gsl_poly_complex_solve(&afCoeff.front(),iDegree+1, WS, RZ);
  for(int i=0;i<iDegree;i++)
    Out[i]=std::complex<double>(RZ[2*i],RZ[2*i+1]);
  gsl_poly_complex_workspace_free (WS);
  delete [] RZ;
  return Out;
}