int main(int argc, char *argv[])
{

#ifdef HAVE_MPI
  MPI_Init(&argc,&argv);
#endif

  Init();

  try {

    int NX = 10;         // number of nodes on the X-axis
    int NY = 10;         // number of nodes on the Y-axis
    double conv = 1.0;   // convection coefficient
    double diff = 1e-5;  // diffusion coefficient

    Operator A = GetRecirc2D(NX, NY, conv, diff);

    Teuchos::ParameterList List;
    List.set("smoother: type", "symmetric Gauss-Seidel");
    List.set("smoother: sweeps", 1);
    List.set("aggregation: damping factor", 0.0);
    List.set("coarse: max size", 32);

    MultiLevelNonSymmetricSA Prec(A, List);

    MultiVector LHS(A.GetRangeSpace());
    MultiVector RHS(A.GetDomainSpace());

    LHS.Random();
    RHS = 0.0;

    List.set("krylov: type", "gmres");
    Krylov(A, LHS, RHS, Prec, List);

    Finalize(); 

  }
  catch (const int e) {
    cerr << "Caught integer exception, code = " << e << endl;
  }
  catch (...) {
    cerr << "Caught exception..." << endl;
  }

#ifdef HAVE_MPI
  MPI_Finalize() ;
#endif

  return(0);

}