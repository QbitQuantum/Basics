int main(int argc, char *argv[]) {
#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  int rank=mpiSession.getRank();
  int numProcs=mpiSession.getNProc();
#else
  int rank = 0;
  int numProcs = 1;
#endif
  bool useCompliantGraphNorm = false;
  bool enforceOneIrregularity = true;
  bool writeStiffnessMatrices = false;
  bool writeWorstCaseGramMatrices = false;
  int numRefs = 10;
  
  // problem parameters:
  double eps = 1e-8;
  vector<double> beta_const;
  beta_const.push_back(2.0);
  beta_const.push_back(1.0);
  
  int k = 2, delta_k = 2;
  
  Teuchos::CommandLineProcessor cmdp(false,true); // false: don't throw exceptions; true: do return errors for unrecognized options
  
  cmdp.setOption("polyOrder",&k,"polynomial order for field variable u");
  cmdp.setOption("delta_k", &delta_k, "test space polynomial order enrichment");
  cmdp.setOption("numRefs",&numRefs,"number of refinements");
  cmdp.setOption("eps", &eps, "epsilon");
  
  if (cmdp.parse(argc,argv) != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL) {
#ifdef HAVE_MPI
    MPI_Finalize();
#endif
    return -1;
  }
  
  int H1Order = k + 1;
  
  if (rank==0) {
    string normChoice = useCompliantGraphNorm ? "unit-compliant graph norm" : "standard graph norm";
    cout << "Using " << normChoice << "." << endl;
    cout << "eps = " << eps << endl;
    cout << "numRefs = " << numRefs << endl;
    cout << "p = " << k << endl;
  }
  
  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactory varFactory; 
  VarPtr tau = varFactory.testVar("\\tau", HDIV);
  VarPtr v = varFactory.testVar("v", HGRAD);
  
  // define trial variables
  VarPtr uhat = varFactory.traceVar("\\widehat{u}");
  VarPtr beta_n_u_minus_sigma_n = varFactory.fluxVar("\\widehat{\\beta \\cdot n u - \\sigma_{n}}");
  VarPtr u;
  if (useCompliantGraphNorm) {
    u = varFactory.fieldVar("u",HGRAD);
  } else {
    u = varFactory.fieldVar("u");
  }
  
  VarPtr sigma1 = varFactory.fieldVar("\\sigma_1");
  VarPtr sigma2 = varFactory.fieldVar("\\sigma_2");
  
  ////////////////////   DEFINE BILINEAR FORM   ///////////////////////
  BFPtr confusionBF = Teuchos::rcp( new BF(varFactory) );
  // tau terms:
  confusionBF->addTerm(sigma1 / eps, tau->x());
  confusionBF->addTerm(sigma2 / eps, tau->y());
  confusionBF->addTerm(u, tau->div());
  confusionBF->addTerm(-uhat, tau->dot_normal());
  
  // v terms:
  confusionBF->addTerm( sigma1, v->dx() );
  confusionBF->addTerm( sigma2, v->dy() );
  confusionBF->addTerm( beta_const * u, - v->grad() );
  confusionBF->addTerm( beta_n_u_minus_sigma_n, v);
  
  ////////////////////   DEFINE INNER PRODUCT(S)   ///////////////////////
  // mathematician's norm
  IPPtr mathIP = Teuchos::rcp(new IP());
  mathIP->addTerm(tau);
  mathIP->addTerm(tau->div());

  mathIP->addTerm(v);
  mathIP->addTerm(v->grad());

  // quasi-optimal norm
  IPPtr qoptIP = Teuchos::rcp(new IP);
  
  if (!useCompliantGraphNorm) {
    qoptIP->addTerm( tau / eps + v->grad() );
    qoptIP->addTerm( beta_const * v->grad() - tau->div() );
    
    qoptIP->addTerm( v );
  } else {
    FunctionPtr h = Teuchos::rcp( new hFunction );
    
    // here, we're aiming at optimality in 1/h^2 |u|^2 + 1/eps^2 |sigma|^2
    
    qoptIP->addTerm( tau + eps * v->grad() );
    qoptIP->addTerm( h * beta_const * v->grad() - tau->div() );
    qoptIP->addTerm(v);
    qoptIP->addTerm(tau);
  }
  
  ////////////////////   SPECIFY RHS   ///////////////////////
  RHSPtr rhs = RHS::rhs();
  FunctionPtr f = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  BCPtr bc = BC::bc();
  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowSquareBoundary );
  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new OutflowSquareBoundary );
  FunctionPtr u0 = Teuchos::rcp( new U0 );
  bc->addDirichlet(uhat, outflowBoundary, u0);

  bc->addDirichlet(uhat, inflowBoundary, u0);
  
//  Teuchos::RCP<PenaltyConstraints> pc = Teuchos::rcp(new PenaltyConstraints);
//  pc->addConstraint(uhat==u0,inflowBoundary);

  ////////////////////   BUILD MESH   ///////////////////////
  // create a new mesh on a single-cell, unit square domain
  Teuchos::RCP<Mesh> mesh = MeshFactory::quadMeshMinRule(confusionBF, H1Order, delta_k);
  
  ////////////////////   SOLVE & REFINE   ///////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, qoptIP) );
//  solution->setFilter(pc);
  
  double energyThreshold = 0.2; // for mesh refinements
  
  bool useRieszRepBasedRefStrategy = true;
  
  if (rank==0) {
    if (useRieszRepBasedRefStrategy) {
      cout << "using RieszRep-based refinement strategy.\n";
    } else {
      cout << "using solution-based refinement strategy.\n";
    }
  }
  Teuchos::RCP<RefinementStrategy> refinementStrategy;
  if (!useRieszRepBasedRefStrategy) {
    refinementStrategy = Teuchos::rcp( new RefinementStrategy( solution, energyThreshold ) );
  } else {
    LinearTermPtr residual = confusionBF->testFunctional(solution) - rhs->linearTerm();
    refinementStrategy = Teuchos::rcp( new RefinementStrategy( mesh, residual, qoptIP, energyThreshold ) );
  }
  
  refinementStrategy->setReportPerCellErrors(true);
  refinementStrategy->setEnforceOneIrregularity(enforceOneIrregularity);
  
  for (int refIndex=0; refIndex<numRefs; refIndex++){
    if (writeStiffnessMatrices) {
      string stiffnessFile = fileNameForRefinement("confusion_stiffness", refIndex);
      solution->setWriteMatrixToFile(true, stiffnessFile);
    }
    solution->solve();
    if (writeWorstCaseGramMatrices) {
      string gramFile = fileNameForRefinement("confusion_gram", refIndex);
      bool jacobiScaling = true;
      double condNum = MeshUtilities::computeMaxLocalConditionNumber(qoptIP, mesh, jacobiScaling, gramFile);
      if (rank==0) {
        cout << "estimated worst-case Gram matrix condition number: " << condNum << endl;
        cout << "putative worst-case Gram matrix written to file " << gramFile << endl;
      }
    }
    if (refIndex == numRefs-1) { // write out second-to-last mesh
      if (rank==0)
        GnuPlotUtil::writeComputationalMeshSkeleton("confusionMesh", mesh, true);
    }
    refinementStrategy->refine(rank==0); // print to console on rank 0
  }
  if (writeStiffnessMatrices) {
    string stiffnessFile = fileNameForRefinement("confusion_stiffness", numRefs);
    solution->setWriteMatrixToFile(true, stiffnessFile);
  }
  if (writeWorstCaseGramMatrices) {
    string gramFile = fileNameForRefinement("confusion_gram", numRefs);
    bool jacobiScaling = true;
    double condNum = MeshUtilities::computeMaxLocalConditionNumber(qoptIP, mesh, jacobiScaling, gramFile);
    if (rank==0) {
      cout << "estimated worst-case Gram matrix condition number: " << condNum << endl;
      cout << "putative worst-case Gram matrix written to file " << gramFile << endl;
    }
  }
  // one more solve on the final refined mesh:
  solution->solve();
  
#ifdef HAVE_EPETRAEXT_HDF5
  ostringstream dir_name;
  dir_name << "confusion_eps" << eps;
  HDF5Exporter exporter(mesh,dir_name.str());
  exporter.exportSolution(solution, varFactory, 0);
  if (rank==0) cout << "wrote solution to " << dir_name.str() << endl;
#endif

  
  return 0;
}