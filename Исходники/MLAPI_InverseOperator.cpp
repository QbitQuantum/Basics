void InverseOperator::Reshape(const Operator& Op, const string Type,
             Teuchos::ParameterList& List, Teuchos::ParameterList* pushlist)
{
  ResetTimer();
  StackPush();

  Op_ = Op;

  RCPRowMatrix_ = Op.GetRCPRowMatrix();

  // FIXME: to add overlap and level-of-fill
  int NumSweeps   = List.get("smoother: sweeps", 1);
  double Damping  = List.get("smoother: damping factor", 0.67); 
  int LOF_ilu     = List.get("smoother: ilu fill", 0);
  double LOF_ict  = List.get("smoother: ilut fill", 1.0);
  double LOF_ilut = List.get("smoother: ict fill", 1.0);
  string reorder  = List.get("schwarz: reordering type","rcm");

  Teuchos::ParameterList IFPACKList;

  // any parameters from the main list List are overwritten by the pushlist
  IFPACKList.set("relaxation: sweeps", NumSweeps);
  IFPACKList.set("relaxation: damping factor", Damping);
  IFPACKList.set("fact: level-of-fill", LOF_ilu);
  IFPACKList.set("fact: ict level-of-fill", LOF_ict);
  IFPACKList.set("fact: ilut level-of-fill", LOF_ilut);
  IFPACKList.set("relaxation: zero starting solution", false);
  IFPACKList.set("schwarz: reordering type",reorder);
  IFPACKList.set("fact: relative threshold",1.0);

  // if present, the pushlist is assumed to be a preconstructed ifpack list
  // that is copied straight to the ifpack list here
  // entries in pushlist overwrite previous list entries
  if (pushlist)
    IFPACKList.setParameters(*pushlist);


  bool verbose = false; //(GetMyPID() == 0 && GetPrintLevel() > 5);

  // the ML smoother
  RCPMLPrec_ = Teuchos::null;
  // The Ifpack smoother
  Ifpack_Preconditioner* Prec = NULL;

  if (Type == "Jacobi") {
    if (verbose) {
      cout << "Damping factor = " << Damping 
        << ", sweeps = " << NumSweeps << endl;
      cout << endl;
    }
    IFPACKList.set("relaxation: type", "Jacobi");
    Prec = new Ifpack_PointRelaxation(RowMatrix());
  }
  else if (Type == "Gauss-Seidel") {
    if (verbose) {
      cout << "Damping factor = " << Damping 
        << ", sweeps = " << NumSweeps << endl;
      cout << endl;
    }
    IFPACKList.set("relaxation: type", "Gauss-Seidel");
    Prec = new Ifpack_PointRelaxation(RowMatrix());
  }
  else if (Type == "symmetric Gauss-Seidel") {
    if (verbose) {
      cout << "Damping factor = " << Damping 
        << ", sweeps = " << NumSweeps << endl;
      cout << endl;
    }
    IFPACKList.set("relaxation: type", "symmetric Gauss-Seidel");

    Prec = new Ifpack_PointRelaxation(RowMatrix());
  }
  else if (Type == "ILU") {
    if (verbose) {
      cout << "ILU factorization, ov = 0, no reordering, LOF = "
        << LOF_ilu << endl;
      cout << endl;
    }
    
    // use the Additive Schwarz class because it does reordering
    Prec = new Ifpack_AdditiveSchwarz<Ifpack_ILU>(RowMatrix());
  }
  else if (Type == "ILUT") {
    if (verbose) {
      cout << "ILUT factorization, ov = 0, no reordering, LOF = "
        << LOF_ilu << endl;
      cout << endl;
    }
    Prec = new Ifpack_ILUT(RowMatrix());
  }
  else if (Type == "IC") {
    if (verbose) {
      cout << "IC factorization, ov = 0, no reordering, LOF = "
        << LOF_ilu << endl;
      cout << endl;
    }
    Prec = new Ifpack_IC(RowMatrix());
  }
  else if (Type == "ICT") {
    if (verbose) {
      cout << "ICT factorization, ov = 0, no reordering, LOF = "
        << LOF_ilu << endl;
      cout << endl;
    }
    Prec = new Ifpack_ICT(RowMatrix());
  }
  else if (Type == "LU") {
    if (verbose) {
      cout << "LU factorization, ov = 0, local solver = KLU" << endl;
      cout << endl;
    }
    Prec = new Ifpack_AdditiveSchwarz<Ifpack_Amesos>(RowMatrix());
  }
  else if (Type == "Amesos" || Type == "Amesos-KLU")  {
    if (verbose) {
      cout << "Amesos-KLU direct solver" << endl;
      cout << endl;
    }
    Prec = new Ifpack_Amesos(RowMatrix());
  }
  else if (Type == "MLS" || Type == "ML MLS" || 
           Type == "ML symmetric Gauss-Seidel" ||
           Type == "ML Gauss-Seidel") 
  {
    if (verbose) {
      cout << "ML's MLS smoother" << endl;
      cout << endl;
      }
    Teuchos::ParameterList mlparams;
    ML_Epetra::SetDefaults("SA",mlparams);
    int output = List.get("ML output",-47);
    if (output == -47) output = List.get("output",-1);
    if (output != -1) mlparams.set("ML output",output);
    mlparams.set("max levels",1);
    int sweeps = List.get("smoother: sweeps",1);
    mlparams.set("coarse: sweeps",sweeps);
    double damp = List.get("smoother: damping factor",0.67);
    mlparams.set("coarse: damping factor",damp);
    mlparams.set("zero starting solution", false);
    if (Type == "MLS" || Type == "ML MLS")
    {
      mlparams.set("coarse: type","MLS"); // MLS symmetric Gauss-Seidel Amesos-KLU
      int poly = List.get("smoother: MLS polynomial order",3);
      mlparams.set("coarse: MLS polynomial order",poly);
    }
    else if (Type == "ML symmetric Gauss-Seidel")
      mlparams.set("coarse: type","symmetric Gauss-Seidel"); // MLS symmetric Gauss-Seidel Amesos-KLU
    else if (Type == "ML Gauss-Seidel")
      mlparams.set("coarse: type","Gauss-Seidel");
    else if (Type == "ML Jacobi")
      mlparams.set("coarse: type","Jacobi");
    else
      ML_THROW("Requested type (" + Type + ") not recognized", -1);
    RCPMLPrec_ = Teuchos::rcp(new ML_Epetra::MultiLevelPreconditioner(*RowMatrix(),mlparams,true));
  }
  else
    ML_THROW("Requested type (" + Type + ") not recognized", -1);

  if (Prec)
  {
    RCPData_ = Teuchos::rcp(Prec);
    RCPData_->SetParameters(IFPACKList);
    RCPData_->Initialize();
    RCPData_->Compute();
    UpdateFlops(RCPData_->InitializeFlops());
    UpdateFlops(RCPData_->ComputeFlops());
  }
  else 
    RCPData_ = Teuchos::null;
    
  StackPop();
  UpdateTime();

}