void Krylov<MatrixType>::initialize ()
{
  using Teuchos::ParameterList;
  using Teuchos::RCP;
  using Teuchos::rcp;
  typedef Tpetra::MultiVector<scalar_type, local_ordinal_type,
                              global_ordinal_type, node_type> TMV;
  typedef Tpetra::Operator<scalar_type, local_ordinal_type,
                           global_ordinal_type, node_type> TOP;

  TEUCHOS_TEST_FOR_EXCEPTION(
    A_.is_null (), std::runtime_error, "Ifpack2::Krylov::initialize: "
    "The input matrix A is null.  Please call setMatrix() with a nonnull "
    "input matrix before calling this method.");

  // clear any previous allocation
  IsInitialized_ = false;
  IsComputed_ = false;

  Teuchos::Time timer ("initialize");
  { // The body of code to time
    Teuchos::TimeMonitor timeMon (timer);

    // Belos parameter list
    RCP<ParameterList> belosList = rcp (new ParameterList ("GMRES"));
    belosList->set ("Maximum Iterations", numIters_);
    belosList->set ("Convergence Tolerance", resTol_);

    // FIXME (17 Jan 2014) This whole "preconditioner type" thing is
    // not how we want Krylov to initialize its inner preconditioner.
    // Krylov should be initialized like AdditiveSchwarz: the Factory
    // should create it, in order to avoid circular dependencies.

    if (PreconditionerType_ == 0) {
      // no preconditioner
    }
    else if (PreconditionerType_==1) {
      ifpack2_prec_=rcp (new Relaxation<row_matrix_type> (A_));
    }
    else if (PreconditionerType_==2) {
      ifpack2_prec_=rcp (new ILUT<row_matrix_type> (A_));
    }
    else if (PreconditionerType_==3) {
      ifpack2_prec_ = rcp (new RILUK<row_matrix_type> (A_));
    }
    else if (PreconditionerType_==4) {
      ifpack2_prec_ = rcp (new Chebyshev<row_matrix_type> (A_));
    }
    if (PreconditionerType_>0) {
      ifpack2_prec_->initialize();
      ifpack2_prec_->setParameters(precParams_);
    }
    belosProblem_ = rcp (new Belos::LinearProblem<belos_scalar_type,TMV,TOP> ());
    belosProblem_->setOperator (A_);

    if (iterationType_ == "GMRES") {
      belosSolver_ =
        rcp (new Belos::BlockGmresSolMgr<belos_scalar_type,TMV,TOP> (belosProblem_, belosList));
    }
    else {
      belosSolver_ =
        rcp (new Belos::BlockCGSolMgr<belos_scalar_type,TMV,TOP> (belosProblem_, belosList));
    }

  }
  IsInitialized_ = true;
  ++NumInitialize_;
  InitializeTime_ += timer.totalElapsedTime ();
}