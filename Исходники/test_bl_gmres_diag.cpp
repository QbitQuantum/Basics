void Iterative_Inverse_Operator::operator () (const Epetra_MultiVector &b, Epetra_MultiVector &x)
{
  // Initialize the solution to zero
  x.PutScalar( 0.0 );

  // Reset the solver, problem, and status test for next solve (HKT)
  pProb->setProblem( Teuchos::rcp(&x, false), Teuchos::rcp(&b, false) );

  timer.start();
  Belos::ReturnType ret = pBelos->solve();
  timer.stop();

  int pid = pComm->MyPID();

  if (pid == 0 && print) {
    if (ret == Belos::Converged)
    {
      std::cout << std::endl << "pid[" << pid << "] Block GMRES converged" << std::endl;
      std::cout << "Solution time: " << timer.totalElapsedTime() << std::endl;

    }
    else
      std::cout << std::endl << "pid[" << pid << "] Block GMRES did not converge" << std::endl;
  }
}