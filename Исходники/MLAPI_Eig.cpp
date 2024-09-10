// ====================================================================== 
// FIXME: Add List
void Eigs(const Operator& A, int NumEigenvalues, 
          MultiVector& ER, MultiVector& EI)
{

  if (A.GetDomainSpace() != A.GetRangeSpace())
    ML_THROW("Input Operator is not square", -1);

  double time;

  time = GetClock();

  int length = NumEigenvalues;
  double tol = 1e-3;
  int restarts = 1;
  int output = 10;
  bool PrintStatus = true;

  // 1.- set parameters for Anasazi
  Teuchos::ParameterList AnasaziList;
  // MatVec should be either "A" or "ML^{-1}A"
  AnasaziList.set("eigen-analysis: matrix operation", "A");
  AnasaziList.set("eigen-analysis: use diagonal scaling", false);
  AnasaziList.set("eigen-analysis: symmetric problem", false);
  AnasaziList.set("eigen-analysis: length", length);
  AnasaziList.set("eigen-analysis: block-size",1);
  AnasaziList.set("eigen-analysis: tolerance", tol);
  AnasaziList.set("eigen-analysis: restart", restarts);
  AnasaziList.set("eigen-analysis: output", output);
  AnasaziList.get("eigen-analysis: print current status",PrintStatus);

  // data to hold real and imag for eigenvalues and eigenvectors
  Space ESpace(-1, NumEigenvalues);
  ER.Reshape(ESpace);
  EI.Reshape(ESpace);

  // this is the starting value -- random
  Epetra_MultiVector EigenVectors(A.GetRowMatrix()->OperatorDomainMap(),
                                  NumEigenvalues);
  EigenVectors.Random();
#ifdef HAVE_ML_ANASAxI
  //int NumRealEigenvectors, NumImagEigenvectors;
#endif

  AnasaziList.set("eigen-analysis: action", "LM");

#ifdef HAVE_ML_ANASAxI
  ML_THROW("fixme...", -1);
  /* FIXME
  ML_Anasazi::Interface(A.GetRowMatrix(),EigenVectors,ER.GetValues(),
			EI.GetValues(), AnasaziList, 0, 0,
			&NumRealEigenvectors, &NumImagEigenvectors, 0);
                        */
#else
  ML_THROW("Anasazi is no longer supported", -1);
#endif

  return;
}