int main(int argc, char *argv[])
{

  // initialize MPI and Epetra communicator
#ifdef HAVE_MPI
  MPI_Init(&argc,&argv);
  Epetra_MpiComm Comm( MPI_COMM_WORLD );
#else
  Epetra_SerialComm Comm;
#endif

  Teuchos::ParameterList GaleriList;

  // The problem is defined on a 2D grid, global size is nx * nx.
  int nx = 30; 
  GaleriList.set("nx", nx);
  GaleriList.set("ny", nx * Comm.NumProc());
  GaleriList.set("mx", 1);
  GaleriList.set("my", Comm.NumProc());
  Teuchos::RefCountPtr<Epetra_Map> Map = Teuchos::rcp( Galeri::CreateMap("Cartesian2D", Comm, GaleriList) );
  Teuchos::RefCountPtr<Epetra_RowMatrix> A = Teuchos::rcp( Galeri::CreateCrsMatrix("Laplace2D", &*Map, GaleriList) );

  // =============================================================== //
  // B E G I N N I N G   O F   I F P A C K   C O N S T R U C T I O N //
  // =============================================================== //

  Teuchos::ParameterList List;

  // allocates an IFPACK factory. No data is associated 
  // to this object (only method Create()).
  Ifpack Factory;

  // create the preconditioner. For valid PrecType values,
  // please check the documentation
  std::string PrecType = "Amesos";
  int OverlapLevel = 2; // must be >= 0. If Comm.NumProc() == 1,
                        // it is ignored.

  Teuchos::RefCountPtr<Ifpack_Preconditioner> Prec = Teuchos::rcp( Factory.Create(PrecType, &*A, OverlapLevel) );
  assert(Prec != Teuchos::null);

  // specify the Amesos solver to be used. 
  // If the selected solver is not available,
  // IFPACK will try to use Amesos' KLU (which is usually always
  // compiled). Amesos' serial solvers are:
  // "Amesos_Klu", "Amesos_Umfpack", "Amesos_Superlu"
  List.set("amesos: solver type", "Amesos_Klu");

  // sets the parameters
  IFPACK_CHK_ERR(Prec->SetParameters(List));

  // initialize the preconditioner. At this point the matrix must
  // have been FillComplete()'d, but actual values are ignored.
  // At this call, Amesos will perform the symbolic factorization.
  IFPACK_CHK_ERR(Prec->Initialize());

  // Builds the preconditioners, by looking for the values of 
  // the matrix. At this call, Amesos will perform the
  // numeric factorization.
  IFPACK_CHK_ERR(Prec->Compute());

  // =================================================== //
  // E N D   O F   I F P A C K   C O N S T R U C T I O N //
  // =================================================== //

  // At this point, we need some additional objects
  // to define and solve the linear system.

  // defines LHS and RHS
  Epetra_Vector LHS(A->OperatorDomainMap());
  Epetra_Vector RHS(A->OperatorDomainMap());

  // solution is constant
  LHS.PutScalar(1.0);
  // now build corresponding RHS
  A->Apply(LHS,RHS);

  // now randomize the solution
  RHS.Random();

  // need an Epetra_LinearProblem to define AztecOO solver
  Epetra_LinearProblem Problem(&*A,&LHS,&RHS);

  // now we can allocate the AztecOO solver
  AztecOO Solver(Problem);

  // specify solver
  Solver.SetAztecOption(AZ_solver,AZ_gmres);
  Solver.SetAztecOption(AZ_output,32);

  // HERE WE SET THE IFPACK PRECONDITIONER
  Solver.SetPrecOperator(&*Prec);

  // .. and here we solve
  // NOTE: with one process, the solver must converge in
  // one iteration.
  Solver.Iterate(1550,1e-8);

#ifdef HAVE_MPI
  MPI_Finalize() ; 
#endif

    return(EXIT_SUCCESS);
}