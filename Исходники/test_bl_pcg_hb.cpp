int main(int argc, char *argv[]) {
  //
#ifdef EPETRA_MPI	
  // Initialize MPI	
  MPI_Init(&argc,&argv); 	
  Belos::MPIFinalize mpiFinalize; // Will call finalize with *any* return
  (void)mpiFinalize;
#endif
  //
  using Teuchos::RCP;
  using Teuchos::rcp;
  //
  // Get test parameters from command-line processor
  //  
  bool verbose = false, proc_verbose = false;
  int frequency = -1; // how often residuals are printed by solver 
  int numrhs = 15;  // total number of right-hand sides to solve for
  int blocksize = 10;  // blocksize used by solver
  int maxiters = -1; // maximum number of iterations for the solver to use
  std::string filename("bcsstk14.hb");
  double tol = 1.0e-5;  // relative residual tolerance

  Teuchos::CommandLineProcessor cmdp(false,true);
  cmdp.setOption("verbose","quiet",&verbose,"Print messages and results.");
  cmdp.setOption("frequency",&frequency,"Solvers frequency for printing residuals (#iters).");
  cmdp.setOption("filename",&filename,"Filename for Harwell-Boeing test matrix.");
  cmdp.setOption("tol",&tol,"Relative residual tolerance used by CG solver.");
  cmdp.setOption("num-rhs",&numrhs,"Number of right-hand sides to be solved for.");
  cmdp.setOption("block-size",&blocksize,"Block size to be used by CG solver.");
  cmdp.setOption("max-iters",&maxiters,"Maximum number of iterations per linear system (-1 := adapted to problem/block size).");

  if (cmdp.parse(argc,argv) != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL) {
    return -1;
  }
  if (!verbose)
    frequency = -1;  // Reset frequency if verbosity is off
  //
  // Get the problem
  //
  int MyPID;
  RCP<Epetra_CrsMatrix> A;
  RCP<Epetra_MultiVector> X, B;
  int return_val =Belos::createEpetraProblem(filename,NULL,&A,&B,&X,&MyPID);
  if(return_val != 0) return return_val;
  proc_verbose = ( verbose && (MyPID==0) );
  //
  // Solve using Belos
  //
  typedef double                           ST;
  typedef Epetra_Operator                  OP;
  typedef Epetra_MultiVector               MV;
  typedef Belos::OperatorTraits<ST,MV,OP> OPT;
  typedef Belos::MultiVecTraits<ST,MV>    MVT;
  //
  // *****Construct initial guess and random right-hand-sides *****
  //
  if (numrhs != 1) {
    X = rcp( new Epetra_MultiVector( A->Map(), numrhs ) );
    MVT::MvRandom( *X );
    B = rcp( new Epetra_MultiVector( A->Map(), numrhs ) );
    OPT::Apply( *A, *X, *B );
    MVT::MvInit( *X, 0.0 );
  }
  //
  // ************Construct preconditioner*************
  //
  ParameterList ifpackList;

  // allocates an IFPACK factory. No data is associated
  // to this object (only method Create()).
  Ifpack Factory;

  // create the preconditioner. For valid PrecType values,
  // please check the documentation
  std::string PrecType = "ICT"; // incomplete Cholesky 
  int OverlapLevel = 0; // must be >= 0. If Comm.NumProc() == 1,
                        // it is ignored.

  RCP<Ifpack_Preconditioner> Prec = Teuchos::rcp( Factory.Create(PrecType, &*A, OverlapLevel) );
  assert(Prec != Teuchos::null);

  // specify parameters for ICT
  ifpackList.set("fact: drop tolerance", 1e-9);
  ifpackList.set("fact: ict level-of-fill", 1.0);
  // the combine mode is on the following:
  // "Add", "Zero", "Insert", "InsertAdd", "Average", "AbsMax"
  // Their meaning is as defined in file Epetra_CombineMode.h
  ifpackList.set("schwarz: combine mode", "Add");
  // sets the parameters
  IFPACK_CHK_ERR(Prec->SetParameters(ifpackList));

  // initialize the preconditioner. At this point the matrix must
  // have been FillComplete()'d, but actual values are ignored.
  IFPACK_CHK_ERR(Prec->Initialize());

  // Builds the preconditioners, by looking for the values of
  // the matrix.
  IFPACK_CHK_ERR(Prec->Compute());

  // Create the Belos preconditioned operator from the Ifpack preconditioner.
  // NOTE:  This is necessary because Belos expects an operator to apply the
  //        preconditioner with Apply() NOT ApplyInverse().
  RCP<Belos::EpetraPrecOp> belosPrec = rcp( new Belos::EpetraPrecOp( Prec ) );

   //
  // *****Create parameter list for the block CG solver manager*****
  //
  const int NumGlobalElements = B->GlobalLength();
  if (maxiters == -1)
    maxiters = NumGlobalElements/blocksize - 1; // maximum number of iterations to run
  //
  ParameterList belosList;
  belosList.set( "Block Size", blocksize );              // Blocksize to be used by iterative solver
  belosList.set( "Maximum Iterations", maxiters );       // Maximum number of iterations allowed
  belosList.set( "Convergence Tolerance", tol );         // Relative convergence tolerance requested
  if (verbose) {
    belosList.set( "Verbosity", Belos::Errors + Belos::Warnings + 
		   Belos::TimingDetails + Belos::FinalSummary + Belos::StatusTestDetails );
    if (frequency > 0)
      belosList.set( "Output Frequency", frequency );
  }
  else
    belosList.set( "Verbosity", Belos::Errors + Belos::Warnings );
  //
  // *******Construct a preconditioned linear problem********
  //
  RCP<Belos::LinearProblem<double,MV,OP> > problem
    = rcp( new Belos::LinearProblem<double,MV,OP>( A, X, B ) );
  problem->setLeftPrec( belosPrec );

  bool set = problem->setProblem();
  if (set == false) {
    if (proc_verbose)
      std::cout << std::endl << "ERROR:  Belos::LinearProblem failed to set up correctly!" << std::endl;
    return -1;
  }
  
  // Create an iterative solver manager.
  RCP< Belos::SolverManager<double,MV,OP> > solver
    = rcp( new Belos::BlockCGSolMgr<double,MV,OP>(problem, rcp(&belosList,false)) );
  
  //
  // *******************************************************************
  // *************Start the block CG iteration*************************
  // *******************************************************************
  if (proc_verbose) {
    std::cout << std::endl << std::endl;
    std::cout << "Dimension of matrix: " << NumGlobalElements << std::endl;
    std::cout << "Number of right-hand sides: " << numrhs << std::endl;
    std::cout << "Block size used by solver: " << blocksize << std::endl;
    std::cout << "Max number of CG iterations: " << maxiters << std::endl; 
    std::cout << "Relative residual tolerance: " << tol << std::endl;
    std::cout << std::endl;
  }
 //
  // Perform solve
  //
  Belos::ReturnType ret = solver->solve();
  //
  // Compute actual residuals.
  //
  bool badRes = false;
  std::vector<double> actual_resids( numrhs );
  std::vector<double> rhs_norm( numrhs );
  Epetra_MultiVector resid(A->Map(), numrhs);
  OPT::Apply( *A, *X, resid );
  MVT::MvAddMv( -1.0, resid, 1.0, *B, resid );
  MVT::MvNorm( resid, actual_resids );
  MVT::MvNorm( *B, rhs_norm );
  if (proc_verbose) {
    std::cout<< "---------- Actual Residuals (normalized) ----------"<<std::endl<<std::endl;
    for ( int i=0; i<numrhs; i++) {
      double actRes = actual_resids[i]/rhs_norm[i];
      std::cout<<"Problem "<<i<<" : \t"<< actRes <<std::endl;
      if (actRes > tol) badRes = true;
    }
  }

  if (ret!=Belos::Converged || badRes) {
    if (proc_verbose)
      std::cout << std::endl << "End Result: TEST FAILED" << std::endl;	
    return -1;
  }
  //
  // Default return value
  //
  if (proc_verbose)
    std::cout << std::endl << "End Result: TEST PASSED" << std::endl;
  return 0;

  //
} // end test_bl_pcg_hb.cpp