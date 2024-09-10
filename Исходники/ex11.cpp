int main(int argc, char *argv[])
{
  
#ifdef HAVE_MPI
  MPI_Init(&argc, &argv);
  Epetra_MpiComm Comm(MPI_COMM_WORLD);
#else
  Epetra_SerialComm Comm;
#endif

  // Total number of elements in vectors, can be any positive number
  int NumRows = 5;

  Epetra_SerialDenseVector x, b;
  x.Size( NumRows );
  b.Size( NumRows );

  // set the elements of the vector
  for( int i=0 ; i<NumRows ; ++i ) b[i] = 1.0, x[i]=0.0;
  
  Epetra_SerialDenseMatrix A, A2;
  A.Shape( NumRows, NumRows );
  A2.Shape( NumRows, NumRows ); // A2 is a copy of A

  // Hilbert matrix (ill-conditioned)
  for( int i=0 ; i<NumRows ; ++i )
    for( int j=0 ; j<NumRows ; ++j ) 
      A(i,j) = 1.0/(i+j+2);

  cout<< A;

  // set up the solver
  Epetra_SerialDenseSolver Problem;
  Problem.SetMatrix( A );
  Problem.SetVectors( x, b );

  A2 = A; 
  // we make a copy of A because Problem.Solve() will
  // overwrite A with its LU decomposition. Try with
  // cout << A after the following invocation

  b.Multiply('N','N',1.0, A2, x, 0.0);

  cout << "A * x = \n" << b;

  double rcond;
  Problem.ReciprocalConditionEstimate(rcond);
  cout << "The (estimated) condition number of A is " << 1/rcond << endl;

  Problem.SetMatrix( A2 );
  Problem.Invert();
  cout << "The inverse of A is\n";
  cout << A2;

#ifdef HAVE_MPI
  MPI_Finalize();
#endif

} /* main */