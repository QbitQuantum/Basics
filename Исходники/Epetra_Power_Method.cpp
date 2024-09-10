int
powerMethod (double & lambda, 
             Epetra_CrsMatrix& A, 
             const int niters, 
             const double tolerance,
             const bool verbose)
{
  // In the power iteration, z = A*q.  Thus, q must be in the domain
  // of A, and z must be in the range of A.  The residual vector is of
  // course in the range of A.
  Epetra_Vector q (A.OperatorDomainMap ());
  Epetra_Vector z (A.OperatorRangeMap ());
  Epetra_Vector resid (A.OperatorRangeMap ());

  Epetra_Flops* counter = A.GetFlopCounter();
  if (counter != 0) {
    q.SetFlopCounter(A);
    z.SetFlopCounter(A);
    resid.SetFlopCounter(A);
  }

  // Initialize the starting vector z with random data.
  z.Random();

  double normz, residual;
  int ierr = 1;
  for (int iter = 0; iter < niters; ++iter)
    {
      z.Norm2 (&normz);        // normz  := ||z||_2
      q.Scale (1.0/normz, z);  // q      := z / normz
      A.Multiply(false, q, z); // z      := A * q
      q.Dot(z, &lambda);       // lambda := dot (q, z)

      // Compute the residual vector and display status output every
      // 100 iterations, or if we have reached the maximum number of
      // iterations.
      if (iter % 100 == 0 || iter + 1 == niters)
        {
          resid.Update (1.0, z, -lambda, q, 0.0); // resid := A*q - lambda*q
          resid.Norm2 (&residual);                // residual := ||resid||_2
          if (verbose) 
            cout << "Iter = " << iter << "  Lambda = " << lambda 
                 << "  Residual of A*q - lambda*q = " << residual << endl;
        } 
      if (residual < tolerance) { // We've converged!
        ierr = 0;
        break;
      }
    }
  return ierr;
}