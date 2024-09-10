int main( int argc, char* argv[] )
{
  using Teuchos::rcp;
  using Teuchos::RCP;
  using Teuchos::OSTab;
  using MoochoPack::MoochoSolver;
  using MoochoPack::MoochoThyraSolver;
  using Teuchos::CommandLineProcessor;

  Teuchos::GlobalMPISession mpiSession(&argc,&argv);

  const int numProcs = mpiSession.getNProc();

  Teuchos::Time timer("");
  
  bool dummySuccess = true;

  Teuchos::RCP<Teuchos::FancyOStream>
    out = Teuchos::VerboseObjectBase::getDefaultOStream();

  try {
  
    // Create the solver object
    GLpApp::AdvDiffReactOptModelCreator     advDiffReacModelCreator;
    Stratimikos::DefaultLinearSolverBuilder   lowsfCreator;
    MoochoThyraSolver                       solver;

    //
    // Get options from the command line
    //

    std::string         matchingVecFile     = "";

    bool                showMoochoThyraParams = false;
    bool                showMoochoThyraParamsWithDoc = true;
    bool                showMoochoThyraParamsXML = false;

    CommandLineProcessor  clp;
    clp.throwExceptions(false);
    clp.addOutputSetupOptions(true);

    advDiffReacModelCreator.setupCLP(&clp);
    lowsfCreator.setupCLP(&clp);
    solver.setupCLP(&clp);

    clp.setOption(
      "q-vec-file", &matchingVecFile
      ,"Base file name to read the objective state matching "
      "vector q (i.e. ||x-q||_M in the objective)."
      );
    
    clp.setOption(
      "only-print-moocho-thyra-solver-params", "no-print-moocho-thyra-solver-params"
      ,&showMoochoThyraParams
      ,"Only print the parameters accepted by MoochoPack::MoochoThyraSolver and stop."
      );
    clp.setOption(
      "show-doc", "hide-doc", &showMoochoThyraParamsWithDoc
      ,"Show MoochoPack::MocohoThyraSolver parameters with documentation or not."
      );
    clp.setOption(
      "xml-format", "readable-format", &showMoochoThyraParamsXML
      ,"Show MoochoPack::MoochoThyraSolver parameters in XML or human-readable format."
      );

    CommandLineProcessor::EParseCommandLineReturn
      parse_return = clp.parse(argc,argv,&std::cerr);

    if( parse_return != CommandLineProcessor::PARSE_SUCCESSFUL )
      return parse_return;

    lowsfCreator.readParameters( !showMoochoThyraParams ? out.get() : NULL );
    solver.readParameters( !showMoochoThyraParams ? out.get() : NULL );

    if(showMoochoThyraParams) {
      typedef Teuchos::ParameterList::PrintOptions PLPrintOptions;
      if(showMoochoThyraParamsXML)
        Teuchos::writeParameterListToXmlOStream(
          *solver.getValidParameters()
          ,*out
          );
      else
        solver.getValidParameters()->print(
          *out,PLPrintOptions().indent(2).showTypes(true).showDoc(showMoochoThyraParamsWithDoc)
          );
      return 0;
    }

    //
    // Setup the output streams
    //
    
    Teuchos::RCP<Teuchos::FancyOStream>
      journalOut = Teuchos::rcp(
        new Teuchos::FancyOStream(
          solver.getSolver().generate_output_file("MoochoJournal")
          ,"  "
          )
        );
    journalOut->copyAllOutputOptions(*out);

    *out
      << "\n***"
      << "\n*** NLPThyraEpetraAdvDiffReactOptMain, Global numProcs = "<<numProcs
      << "\n***\n";

#ifdef HAVE_MPI
    MPI_Comm mpiComm = MPI_COMM_WORLD;
#endif

    Teuchos::RCP<Epetra_Comm> comm = Teuchos::null;
#ifdef HAVE_MPI
    comm = Teuchos::rcp(new Epetra_MpiComm(mpiComm));
#else
    comm = Teuchos::rcp(new Epetra_SerialComm());
#endif
    
    //
    // Create the Thyra::ModelEvaluator object
    //
    
    *out << "\nCreate the GLpApp::AdvDiffReactOptModel wrapper object ...\n";
    
    Teuchos::RCP<GLpApp::AdvDiffReactOptModel>
      epetraModel = advDiffReacModelCreator.createModel(comm);
    epetraModel->setOStream(journalOut);

    *out << "\nCreate the Thyra::LinearOpWithSolveFactory object ...\n";

    Teuchos::RCP<Thyra::LinearOpWithSolveFactoryBase<Scalar> >
      lowsFactory = lowsfCreator.createLinearSolveStrategy("");
    // ToDo: Set the output stream before calling above!
    ///lowsFactory = lowsfCreator.createLOWSF(OSTab(journalOut).get());
    
    *out << "\nCreate the Thyra::EpetraModelEvaluator wrapper object ...\n";
    
    Teuchos::RCP<Thyra::EpetraModelEvaluator>
      epetraThyraModel = rcp(new Thyra::EpetraModelEvaluator()); // Sets default options!
    epetraThyraModel->setOStream(journalOut);
    epetraThyraModel->initialize(epetraModel,lowsFactory);

    *out
      << "\nnx = " << epetraThyraModel->get_x_space()->dim()
      << "\nnp = " << epetraThyraModel->get_p_space(0)->dim() << "\n";

    if(matchingVecFile != "") {
      *out << "\nReading the matching vector \'q\' from the file(s) with base name \""<<matchingVecFile<<"\" ...\n";
      Thyra::DefaultSpmdMultiVectorFileIO<Scalar> fileIO;
      epetraModel->set_q(
        Thyra::get_Epetra_Vector(
          *epetraModel->get_x_map()
          ,readVectorFromFile(fileIO,matchingVecFile,*epetraThyraModel->get_x_space())
          )
        );
    }

    //
    // Solve the NLP
    //

    // Set the journal file
    solver.getSolver().set_journal_out(journalOut);
    
    // Set the model
    solver.setModel(epetraThyraModel);

    // Read the initial guess if one exists
    solver.readInitialGuess(out.get());

    // Solve the NLP
    const MoochoSolver::ESolutionStatus	solution_status = solver.solve();

    // Write the solution to file
    solver.writeFinalSolution(out.get());
    
    // Write the final parameters to file
    lowsfCreator.writeParamsFile(*lowsFactory);
    solver.writeParamsFile();
    
    //
    // Return the solution status (0 if successful)
    //

    if(solution_status == MoochoSolver::SOLVE_RETURN_SOLVED)
      *out << "\nEnd Result: TEST PASSED\n";
    else
      *out << "\nEnd Result: TEST FAILED\n";
    
    return solution_status;

  }
  TEUCHOS_STANDARD_CATCH_STATEMENTS(true, *out, dummySuccess)

  return MoochoSolver::SOLVE_RETURN_EXCEPTION;

}