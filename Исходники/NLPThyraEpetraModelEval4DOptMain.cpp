int main( int argc, char* argv[] )
{
  using Teuchos::CommandLineProcessor;
  typedef AbstractLinAlgPack::value_type  Scalar;
  using MoochoPack::MoochoSolver;
  using MoochoPack::MoochoThyraSolver;

  bool dummySuccess = true;

  Teuchos::GlobalMPISession mpiSession(&argc,&argv);

  Teuchos::RCP<Teuchos::FancyOStream>
    out = Teuchos::VerboseObjectBase::getDefaultOStream();

  try {

    Stratimikos::DefaultLinearSolverBuilder lowsfCreator;
    MoochoThyraSolver                     solver;
  
    //
    // Get options from the command line
    //
    
    Scalar       xt0         = 1.0;
    Scalar       xt1         = 1.0;
    Scalar       pt0         = 2.0;
    Scalar       pt1         = 0.0;
    Scalar       d           = 10.0;
    Scalar       x00         = 1.0;
    Scalar       x01         = 1.0;
    Scalar       p00         = 2.0;
    Scalar       p01         = 0.0;
    Scalar       pL0         = -1e+50;
    Scalar       pL1         = -1e+50;
    Scalar       pU0         = +1e+50;
    Scalar       pU1         = +1e+50;

    Scalar       xL0         = -1e+50;
    Scalar       xL1         = -1e+50;
    Scalar       xU0         = +1e+50;
    Scalar       xU1         = +1e+50;

    bool supportDerivs = true;

    std::string extraXmlFile = "";

    CommandLineProcessor  clp(false); // Don't throw exceptions

    lowsfCreator.setupCLP(&clp);
    solver.setupCLP(&clp);

    clp.setOption( "xt0", &xt0 );
    clp.setOption( "xt1", &xt1 );
    clp.setOption( "pt0", &pt0 );
    clp.setOption( "pt1", &pt1 );
    clp.setOption( "d", &d );
    clp.setOption( "x00", &x00 );
    clp.setOption( "x01", &x01 );
    clp.setOption( "p00", &p00 );
    clp.setOption( "p01", &p01 );
    clp.setOption( "pL0", &pL0 );
    clp.setOption( "pL1", &pL1 );
    clp.setOption( "pU0", &pU0 );
    clp.setOption( "pU1", &pU1 );
    clp.setOption( "xL0", &xL0 );
    clp.setOption( "xL1", &xL1 );
    clp.setOption( "xU0", &xU0 );
    clp.setOption( "xU1", &xU1 );
    clp.setOption( "support-derivs", "no-support-derivs", &supportDerivs );
    clp.setOption("extra-xml-file",&extraXmlFile,"File with extra XML text that will modify the initial XML read in");
 
    std::string line("");
    if(extraXmlFile.length()) {
      std::ifstream myfile(extraXmlFile.c_str());
      if (myfile.is_open())
      {
        getline (myfile,line);
        solver.extraParamsXmlStringOption(line);
        std::cout << line << "\n";
        myfile.close();
      }
    }

    CommandLineProcessor::EParseCommandLineReturn
      parse_return = clp.parse(argc,argv,&std::cerr);

    if( parse_return != CommandLineProcessor::PARSE_SUCCESSFUL )
      return parse_return;

    lowsfCreator.readParameters(out.get());
    solver.readParameters(out.get());

    //
    // Create the NLP
    //
    
    // Create the EpetraExt::ModelEvaluator object

    Teuchos::RCP<EpetraModelEval4DOpt>
      epetraModel = Teuchos::rcp(new EpetraModelEval4DOpt(xt0,xt1,pt0,pt1,d,x00,x01,p00,p01));
    epetraModel->setSupportDerivs(supportDerivs);
    epetraModel->set_p_bounds(pL0,pL1,pU0,pU1);
    epetraModel->set_x_bounds(xL0,xL1,xU0,xU1);

    // Create the Thyra::EpetraModelEvaluator object

    Teuchos::RCP<Thyra::LinearOpWithSolveFactoryBase<double> >
      lowsFactory = lowsfCreator.createLinearSolveStrategy("");

    Teuchos::RCP<Thyra::EpetraModelEvaluator>
      epetraThyraModel = Teuchos::rcp(new Thyra::EpetraModelEvaluator());
    
    epetraThyraModel->initialize(epetraModel,lowsFactory);
    
    //
    // Solve the NLP
    //
    
    // Set the model
    solver.setModel(epetraThyraModel);

    // Read the initial guess if one exists
    solver.readInitialGuess(out.get());

    // Solve the NLP
    const MoochoSolver::ESolutionStatus	solution_status = solver.solve();

    // Write the final solution if requested
    solver.writeFinalSolution(out.get());

    // Write the parameters that where read
    lowsfCreator.writeParamsFile(*lowsFactory);
    solver.writeParamsFile();
    
    //
    // Return the solution status (0 if sucessfull)
    //

    return solution_status;

  }
  TEUCHOS_STANDARD_CATCH_STATEMENTS(true,*out,dummySuccess)

  return MoochoSolver::SOLVE_RETURN_EXCEPTION;

}