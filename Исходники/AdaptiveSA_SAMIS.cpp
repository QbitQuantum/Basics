int main(int argc, char *argv[])
{

#ifdef HAVE_MPI
  MPI_Init(&argc,&argv);
#endif

  if (argc != 2) {
    fprintf(stderr, "Usage: `%s InputFile'\n", argv[0]);
    fprintf(stderr, "An example of input file is reported\n");
    fprintf(stderr, "in the source of this example\n");
    exit(EXIT_SUCCESS);
  }

  string InputFile = argv[1];

  // Initialize the workspace and set the output level
  Init();

  try {

    int         NumPDEEqns;
    Operator    A;

    ReadSAMISMatrix("mtx.dat", A, NumPDEEqns);

    Teuchos::ParameterList List = ReadParameterList(InputFile.c_str());
    int  MaxLevels            = List.get("max levels", 10);
    int  AdditionalCandidates = List.get("additional candidates", 2);
    int  limKer               = List.get("limit kernel", -1);

    if (AdditionalCandidates == 0 && limKer == 0)
      limKer = -1;

    // create multilevel preconditioner, do not compute hierarchy
    MultiLevelAdaptiveSA Prec(A, List, NumPDEEqns);

    if (limKer) {
      MultiVector NS;
      ReadSAMISKernel("ker.dat", NS, limKer);
      Prec.SetNullSpace(NS);
      Prec.AdaptCompute(true, AdditionalCandidates);
    }
    else {
      Prec.AdaptCompute(false, AdditionalCandidates);
    }

    MultiVector LHS(A.GetDomainSpace());
    MultiVector RHS(A.GetRangeSpace());

    LHS.Random();
    RHS = 0.0;

    // Set krylov: type unless specified in the config. file
    if (List.isParameter("krylov: type") == 0)
        List.set("krylov: type","cg_condnum");

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