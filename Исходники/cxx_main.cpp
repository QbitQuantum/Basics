int check(Epetra_SerialDenseSolver &solver, double * A1, int LDA1,
	  int N1, int NRHS1, double OneNorm1,
	  double * B1, int LDB1,
	  double * X1, int LDX1,
	  bool Transpose, bool verbose) {

  int i;
  bool OK;
  // Test query functions

  int M= solver.M();
  if (verbose) cout << "\n\nNumber of Rows = " << M << endl<< endl;
  assert(M==N1);

  int N= solver.N();
  if (verbose) cout << "\n\nNumber of Equations = " << N << endl<< endl;
  assert(N==N1);

  int LDA = solver.LDA();
  if (verbose) cout << "\n\nLDA = " << LDA << endl<< endl;
  assert(LDA==LDA1);

  int LDB = solver.LDB();
  if (verbose) cout << "\n\nLDB = " << LDB << endl<< endl;
  assert(LDB==LDB1);

  int LDX = solver.LDX();
  if (verbose) cout << "\n\nLDX = " << LDX << endl<< endl;
  assert(LDX==LDX1);

  int NRHS = solver.NRHS();
  if (verbose) cout << "\n\nNRHS = " << NRHS << endl<< endl;
  assert(NRHS==NRHS1);

  assert(solver.ANORM()==-1.0);
  assert(solver.RCOND()==-1.0);
  if (!solver.A_Equilibrated() && !solver.B_Equilibrated()) {
    assert(solver.ROWCND()==-1.0);
    assert(solver.COLCND()==-1.0);
    assert(solver.AMAX()==-1.0);
  }


  // Other binary tests

  assert(!solver.Factored());
  assert(solver.Transpose()==Transpose);
  assert(!solver.SolutionErrorsEstimated());
  assert(!solver.Inverted());
  assert(!solver.ReciprocalConditionEstimated());
  assert(!solver.Solved());

  assert(!solver.SolutionRefined());


  int ierr = solver.Factor();
  assert(ierr>-1);
  if (ierr!=0) return(ierr); // Factorization failed due to poor conditioning.
  double rcond;
  ierr = solver.ReciprocalConditionEstimate(rcond);
  assert(ierr==0);
  if (verbose) {

    double rcond1 = 1.0/exp(3.5*((double)N));
    if (N==1) rcond1 = 1.0;
    cout << "\n\nRCOND = "<< rcond << " should be approx = "
		    << rcond1 << endl << endl;
  }

  ierr = solver.Solve();
  assert(ierr>-1);
  if (ierr!=0 && verbose) cout << "LAPACK rules suggest system should be equilibrated." << endl;

  assert(solver.Factored());
  assert(solver.Transpose()==Transpose);
  assert(solver.ReciprocalConditionEstimated());
  assert(solver.Solved());

  if (solver.SolutionErrorsEstimated()) {
    if (verbose) {
      cout << "\n\nFERR[0] = "<< solver.FERR()[0] << endl;
      cout << "\n\nBERR[0] = "<< solver.BERR()[0] << endl<< endl;
    }
  }

  double * resid = new double[NRHS];
  OK = Residual(N, NRHS, A1, LDA1, solver.Transpose(), solver.X(), solver.LDX(), B1, LDB1, resid);
  if (verbose) {
    if (!OK) cout << "************* Residual do not meet tolerance *************" << endl;
 /*
    if (solver.A_Equilibrated()) {
      double * R = solver.R();
      double * C = solver.C();
      for (i=0; i<solver.M(); i++)
      cout << "R[" << i <<"] = "<< R[i] << endl;
      for (i=0; i<solver.N(); i++)
      cout << "C[" << i <<"] = "<< C[i] << endl;
    }
 */
    cout << "\n\nResiduals using factorization to solve" << endl;
    for (i=0; i<NRHS; i++)
      cout << "Residual[" << i <<"] = "<< resid[i] << endl;
    cout  << endl;
  }


  ierr = solver.Invert();
  assert(ierr>-1);

  assert(solver.Inverted());
  assert(!solver.Factored());
  assert(solver.Transpose()==Transpose);


  Epetra_SerialDenseMatrix RHS1(Copy, B1, LDB1, N, NRHS);
  Epetra_SerialDenseMatrix LHS1(Copy, X1, LDX1, N, NRHS);
  assert(solver.SetVectors(LHS1, RHS1)==0);
  assert(!solver.Solved());

  assert(solver.Solve()>-1);
	


  OK = Residual(N, NRHS, A1, LDA1, solver.Transpose(), solver.X(), solver.LDX(), B1, LDB1, resid);

  if (verbose) {
    if (!OK) cout << "************* Residual do not meet tolerance *************" << endl;
    cout << "Residuals using inverse to solve" << endl;
    for (i=0; i<NRHS; i++)
      cout << "Residual[" << i <<"] = "<< resid[i] << endl;
    cout  << endl;
  }
  delete [] resid;


  return(0);
}