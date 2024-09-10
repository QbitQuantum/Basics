int main(int argc, char *argv[]) {
#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  choice::MpiArgs args( argc, argv );
  int rank=mpiSession.getRank();
  int numProcs=mpiSession.getNProc();
#else
  choice::Args args( argc, argv );
  int rank = 0;
  int numProcs = 1;
#endif

  int nCells = args.Input<int>("--nCells", "num cells",2);  
  int numRefs = args.Input<int>("--numRefs","num adaptive refinements",0); 
  double eps = args.Input<double>("--epsilon","diffusion parameter",1e-2);
  double energyThreshold = args.Input<double>("--energyThreshold","adaptivity thresh",.5);
  if (rank==0){
    cout << "nCells = " << nCells << ", numRefs = " << numRefs << ", eps = " << eps << endl;
  }
  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactory varFactory; 
  VarPtr tau = varFactory.testVar("\\tau", HDIV);
  VarPtr v = varFactory.testVar("v", HGRAD);
  
  // define trial variables
  VarPtr uhat = varFactory.traceVar("\\widehat{u}");
  VarPtr beta_n_u_minus_sigma_n = varFactory.fluxVar("\\widehat{\\beta \\cdot n u - \\sigma_{n}}");
  VarPtr u = varFactory.fieldVar("u");
  VarPtr sigma1 = varFactory.fieldVar("\\sigma_1");
  VarPtr sigma2 = varFactory.fieldVar("\\sigma_2");

  vector<double> beta;
  beta.push_back(1.0);
  beta.push_back(0.0);
  
  ////////////////////   DEFINE BILINEAR FORM   ///////////////////////

  BFPtr confusionBF = Teuchos::rcp( new BF(varFactory) );
  // tau terms:
  confusionBF->addTerm(sigma1 / eps, tau->x());
  confusionBF->addTerm(sigma2 / eps, tau->y());
  confusionBF->addTerm(u, tau->div());
  confusionBF->addTerm(uhat, -tau->dot_normal());
  
  // v terms:
  confusionBF->addTerm( sigma1, v->dx() );
  confusionBF->addTerm( sigma2, v->dy() );
  confusionBF->addTerm( -u, beta * v->grad() );
  confusionBF->addTerm( beta_n_u_minus_sigma_n, v);
  
  ////////////////////   DEFINE INNER PRODUCT(S)   ///////////////////////

  // quasi-optimal norm
  IPPtr qoptIP = Teuchos::rcp(new IP);  
  qoptIP->addTerm( v );
  qoptIP->addTerm( tau / eps + v->grad() );
  qoptIP->addTerm( beta * v->grad() - tau->div() );

  // robust test norm
  IPPtr robIP = Teuchos::rcp(new IP);
  FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(eps) ); 
  FunctionPtr invSqrtH = Teuchos::rcp(new InvSqrtHScaling);

  
  robIP->addTerm( ip_scaling * v);
  robIP->addTerm( ip_scaling/sqrt(eps) * tau );
  robIP->addTerm( sqrt(eps) * v->grad() );
  robIP->addTerm( beta * v->grad() );
  robIP->addTerm( tau->div() );  
  /*
  robIP->addTerm(v);
  robIP->addTerm(v->grad());
  robIP->addTerm(tau->div());
  robIP->addTerm(invSqrtH*tau);  
  */
  FunctionPtr h2_scaling = Teuchos::rcp( new ZeroMeanScaling ); // see what effect this has
  //  robIP->addZeroMeanTerm( h2_scaling*v );
  
  ////////////////////   SPECIFY RHS   ///////////////////////
  FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );
  //  FunctionPtr f = zero;
  //  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );
  //  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowSquareBoundary(beta) );
  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowSquareBoundary );
  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new OutflowSquareBoundary);

  FunctionPtr u_exact = Teuchos::rcp( new Uex(eps,0) );
  FunctionPtr sig1_exact = Teuchos::rcp( new Uex(eps,1) );
  FunctionPtr sig2_exact = Teuchos::rcp( new Uex(eps,2) );
  FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );

  vector<double> e1(2); // (1,0)
  vector<double> e2(2); // (0,1)
  e1[0] = 1;
  e2[1] = 1;
  FunctionPtr sigma = sig1_exact*e1 + sig2_exact*e2;

  bc->addDirichlet(uhat, outflowBoundary, zero);
  bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, beta*n*u_exact-sigma*n);  
  //  bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, beta*n*u_exact);   // ignoring sigma
  FunctionPtr u_disc = Teuchos::rcp( new Udisc );
  //  bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, beta*n*u_disc);  

  //  bc->addDirichlet(uhat, inflowBoundary, u_exact);  

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int H1Order = 2, pToAdd = 3;
  
  int horizontalCells = nCells, verticalCells = nCells;
  
  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = MeshUtilities::buildUnitQuadMesh(nCells,confusionBF, H1Order, H1Order+pToAdd);
    
  ////////////////////   SOLVE & REFINE   ///////////////////////

  Teuchos::RCP<Solution> solution;
  solution = Teuchos::rcp( new Solution(mesh, bc, rhs, robIP) );
  //  solution = Teuchos::rcp( new Solution(mesh, bc, rhs, qoptIP) );

  if (enforceLocalConservation) {
    FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
    solution->lagrangeConstraints()->addConstraint(beta_n_u_minus_sigma_n == zero);
  }
  
  RefinementStrategy refinementStrategy( solution, energyThreshold );
   
  ofstream convOut;
  stringstream convOutFile;
  convOutFile << "erickson_conv_" << round(-log(eps)/log(10.0)) <<".txt";
  convOut.open(convOutFile.str().c_str());
  for (int refIndex=0; refIndex < numRefs; refIndex++){    
    solution->condensedSolve(false);
    //    solution->solve(false);

    double quadTol = 1e-7;
    int cubEnrich = 25;
    FunctionPtr u_soln = Teuchos::rcp( new PreviousSolutionFunction(solution, u) );
    FunctionPtr sigma1_soln = Teuchos::rcp( new PreviousSolutionFunction(solution, sigma1) );
    FunctionPtr sigma2_soln = Teuchos::rcp( new PreviousSolutionFunction(solution, sigma2) );
    FunctionPtr u_diff = (u_soln - u_exact)*(u_soln - u_exact);
    FunctionPtr sig1_diff = (sigma1_soln - sig1_exact)*(sigma1_soln - sig1_exact);
    FunctionPtr sig2_diff = (sigma2_soln - sig2_exact)*(sigma2_soln - sig2_exact);
    double u_L2_error = u_diff->integrate(mesh,cubEnrich);
    double sigma_L2_error = sig1_diff->integrate(mesh,cubEnrich) + sig2_diff->integrate(mesh,cubEnrich);
    double L2_error = sqrt(u_L2_error + sigma_L2_error);
    double energy_error = solution->energyErrorTotal();
    u_soln->writeValuesToMATLABFile(mesh, "u_soln.m");
    u_diff->writeValuesToMATLABFile(mesh, "u_diff.m");
    u_exact->writeValuesToMATLABFile(mesh, "u_exact.m");
    sig1_exact->writeValuesToMATLABFile(mesh, "s1_exact.m");
    sig2_exact->writeValuesToMATLABFile(mesh, "s2_exact.m");

    convOut << mesh->numGlobalDofs() << " " << L2_error << " " << energy_error << endl;
    if (rank==0){
      cout << "L2 error = " << L2_error << ", energy error = " << energy_error << ", ratio = " << L2_error/energy_error << endl;
      cout << "u squared L2 error = " << u_L2_error << ", sigma squared l2 error = " << sigma_L2_error << ", num dofs = " << mesh->numGlobalDofs() << endl;
    }

    refinementStrategy.refine(rank==0); // print to console on rank 0
  }
  convOut.close();  

  // one more solve on the final refined mesh:
  solution->condensedSolve(false);

  VTKExporter exporter(solution, mesh, varFactory);
  if (rank==0){
    exporter.exportSolution("robustIP");
    cout << endl;
  }

  return 0; 
  /*
  // determine trialIDs
  vector< int > trialIDs = mesh->bilinearForm()->trialIDs();
  vector< int > fieldIDs;
  vector< int > fluxIDs;
  vector< int >::iterator idIt;

  for (idIt = trialIDs.begin();idIt!=trialIDs.end();idIt++){
    int trialID = *(idIt);
    if (!mesh->bilinearForm()->isFluxOrTrace(trialID)){ // if field
      fieldIDs.push_back(trialID);
    } else {
      fluxIDs.push_back(trialID);
    }
  } 
  int numFieldInds = 0;
  map<int,vector<int> > globalFluxInds;   // from cellID to localDofInd vector
  map<int,vector<int> > globalFieldInds;   // from cellID to localDofInd vector
  map<int,vector<int> > localFieldInds;   // from cellID to localDofInd vector
  map<int,vector<int> > localFluxInds;   // from cellID to localDofInd vector
  set<int>              allFluxInds;    // unique set of all flux inds

  mesh->getDofIndices(allFluxInds,globalFluxInds,globalFieldInds,localFluxInds,localFieldInds);

  if (rank==0){

    vector< ElementPtr > activeElems = mesh->activeElements();
    vector< ElementPtr >::iterator elemIt;

    cout << "num flux dofs = " << allFluxInds.size() << endl;
    cout << "num field dofs = " << mesh->numFieldDofs() << endl;
    cout << "num flux dofs = " << mesh->numFluxDofs() << endl;
    elemIt = activeElems.begin();
    int cellID = (*elemIt)->cellID();
    cout << "num LOCAL field dofs = " << localFieldInds[cellID].size() << endl;
  
    ofstream fieldInds; 
    fieldInds.open("fieldInds.dat");
    for (elemIt = activeElems.begin();elemIt!=activeElems.end();elemIt++){
      int cellID = (*elemIt)->cellID();
      vector<int> inds = globalFieldInds[cellID];
      vector<int> locFieldInds = localFieldInds[cellID];
      cout << "local field inds for cell ID " << cellID << endl;
      for (int i = 0;i<inds.size();++i){
	fieldInds << inds[i]+1 << endl;
	cout << locFieldInds[i] << endl;
      }
      vector<int> finds = globalFluxInds[cellID];
      vector<int> locFluxInds = localFluxInds[cellID];
      cout << "local flux inds for cell ID " << cellID << endl;
      for (int i = 0;i<finds.size();++i){
	cout << locFluxInds[i] << endl;
      }
      cout << "global flux inds for cell ID " << cellID << endl;
      for (int i = 0;i<finds.size();++i){
	cout << globalFluxInds[cellID][i] << endl;
      }
    }
    fieldInds.close();

    ofstream fluxInds;
    fluxInds.open("fluxInds.dat");
    set<int>::iterator fluxIt;
    for (fluxIt = allFluxInds.begin();fluxIt!=allFluxInds.end();fluxIt++){
      fluxInds << (*fluxIt)+1 << endl; // offset by 1 for matlab
    }
    fluxInds.close();
  }
  
  return 0;
  */
}