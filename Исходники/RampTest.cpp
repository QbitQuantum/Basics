int main(int argc, char *argv[])
{

#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  choice::MpiArgs args( argc, argv );
#else
  choice::Args args( argc, argv );
#endif
  int rank = Teuchos::GlobalMPISession::getRank();
  int numProcs = Teuchos::GlobalMPISession::getNProc();

  int nCells = args.Input<int>("--nCells", "num cells",2);
  int numRefs = args.Input<int>("--numRefs","num adaptive refinements",0);
  int numPreRefs = args.Input<int>("--numPreRefs","num preemptive adaptive refinements",0);
  int order = args.Input<int>("--order","order of approximation",2);
  double eps = args.Input<double>("--epsilon","diffusion parameter",1e-2);
  double energyThreshold = args.Input<double>("-energyThreshold","energy thresh for adaptivity", .5);
  double rampHeight = args.Input<double>("--rampHeight","ramp height at x = 2", 0.0);
  bool useAnisotropy = args.Input<bool>("--useAnisotropy","aniso flag ", false);

  FunctionPtr zero = Function::constant(0.0);
  FunctionPtr one = Function::constant(1.0);
  FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );
  vector<double> e1,e2;
  e1.push_back(1.0);
  e1.push_back(0.0);
  e2.push_back(0.0);
  e2.push_back(1.0);

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

  // first order term with magnitude alpha
  double alpha = 0.0;
  confusionBF->addTerm(alpha * u, v);

  ////////////////////   DEFINE INNER PRODUCT(S)   ///////////////////////

  // robust test norm
  IPPtr robIP = Teuchos::rcp(new IP);
  FunctionPtr C_h = Teuchos::rcp( new EpsilonScaling(eps) );
  FunctionPtr invH = Teuchos::rcp(new InvHScaling);
  FunctionPtr invSqrtH = Teuchos::rcp(new InvSqrtHScaling);
  FunctionPtr sqrtH = Teuchos::rcp(new SqrtHScaling);
  robIP->addTerm(v*alpha);
  robIP->addTerm(invSqrtH*v);
  //  robIP->addTerm(v);
  robIP->addTerm(sqrt(eps) * v->grad() );
  robIP->addTerm(beta * v->grad() );
  robIP->addTerm(tau->div() );
  robIP->addTerm(C_h/sqrt(eps) * tau );

  LinearTermPtr vVecLT = Teuchos::rcp(new LinearTerm);
  LinearTermPtr tauVecLT = Teuchos::rcp(new LinearTerm);
  vVecLT->addTerm(sqrt(eps)*v->grad());
  tauVecLT->addTerm(C_h/sqrt(eps)*tau);

  LinearTermPtr restLT = Teuchos::rcp(new LinearTerm);
  restLT->addTerm(alpha*v);
  restLT->addTerm(invSqrtH*v);
  restLT = restLT + beta * v->grad();
  restLT = restLT + tau->div();

  ////////////////////   SPECIFY RHS   ///////////////////////

  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );
  FunctionPtr f = zero;
  //  f = one;
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );

  //  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowSquareBoundary );
  //  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new OutflowSquareBoundary);
  //  bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, zero);
  //  bc->addDirichlet(uhat, outflowBoundary, zero);

  SpatialFilterPtr rampInflow = Teuchos::rcp(new LeftInflow);
  SpatialFilterPtr rampBoundary = MeshUtilities::rampBoundary(rampHeight);
  SpatialFilterPtr freeStream = Teuchos::rcp(new FreeStreamBoundary);
  SpatialFilterPtr outflowBoundary = Teuchos::rcp(new OutflowBoundary);
  bc->addDirichlet(uhat, rampBoundary, one);
  //  bc->addDirichlet(uhat, outflowBoundary, one);
  bc->addDirichlet(beta_n_u_minus_sigma_n, rampInflow, zero);
  bc->addDirichlet(beta_n_u_minus_sigma_n, freeStream, zero);

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int H1Order = order+1;
  int pToAdd = 2;

  // create a pointer to a new mesh:
  //  Teuchos::RCP<Mesh> mesh = MeshUtilities::buildUnitQuadMesh(nCells,confusionBF, H1Order, H1Order+pToAdd);
  Teuchos::RCP<Mesh> mesh = MeshUtilities::buildRampMesh(rampHeight,confusionBF, H1Order, H1Order+pToAdd);
  mesh->setPartitionPolicy(Teuchos::rcp(new ZoltanMeshPartitionPolicy("HSFC")));

  ////////////////////   SOLVE & REFINE   ///////////////////////

  Teuchos::RCP<Solution> solution;
  solution = Teuchos::rcp( new Solution(mesh, bc, rhs, robIP) );
  //  solution->solve(false);
  solution->condensedSolve();

  LinearTermPtr residual = rhs->linearTermCopy();
  residual->addTerm(-confusionBF->testFunctional(solution));
  RieszRepPtr rieszResidual = Teuchos::rcp(new RieszRep(mesh, robIP, residual));
  rieszResidual->computeRieszRep();
  FunctionPtr e_v = Teuchos::rcp(new RepFunction(v,rieszResidual));
  FunctionPtr e_tau = Teuchos::rcp(new RepFunction(tau,rieszResidual));
  map<int,FunctionPtr> errRepMap;
  errRepMap[v->ID()] = e_v;
  errRepMap[tau->ID()] = e_tau;
  FunctionPtr errTau = tauVecLT->evaluate(errRepMap,false);
  FunctionPtr errV = vVecLT->evaluate(errRepMap,false);
  FunctionPtr errRest = restLT->evaluate(errRepMap,false);
  FunctionPtr xErr = (errTau->x())*(errTau->x()) + (errV->dx())*(errV->dx());
  FunctionPtr yErr = (errTau->y())*(errTau->y()) + (errV->dy())*(errV->dy());
  FunctionPtr restErr = errRest*errRest;

  RefinementStrategy refinementStrategy( solution, energyThreshold );

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                     PRE REFINEMENTS
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (rank==0)
  {
    cout << "Number of pre-refinements = " << numPreRefs << endl;
  }
  for (int i =0; i<=numPreRefs; i++)
  {
    vector<ElementPtr> elems = mesh->activeElements();
    vector<ElementPtr>::iterator elemIt;
    vector<int> wallCells;
    for (elemIt=elems.begin(); elemIt != elems.end(); elemIt++)
    {
      int cellID = (*elemIt)->cellID();
      int numSides = mesh->getElement(cellID)->numSides();
      FieldContainer<double> vertices(numSides,2); //for quads

      mesh->verticesForCell(vertices, cellID);
      bool cellIDset = false;
      for (int j = 0; j<numSides; j++)
      {
        if ((abs(vertices(j,0)-1.0)<1e-7) && (abs(vertices(j,1))<1e-7) && !cellIDset)  // if at singularity, i.e. if a vertex is (1,0)
        {
          wallCells.push_back(cellID);
          cellIDset = true;
        }
      }
    }
    if (i<numPreRefs)
    {
      refinementStrategy.refineCells(wallCells);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  VTKExporter exporter(solution, mesh, varFactory);

  for (int refIndex=0; refIndex<numRefs; refIndex++)
  {
    if (rank==0)
    {
      cout << "on ref index " << refIndex << endl;
    }
    rieszResidual->computeRieszRep(); // in preparation to get anisotropy

    vector<int> cellIDs;
    refinementStrategy.getCellsAboveErrorThreshhold(cellIDs);

    map<int,double> energyError = solution->energyError();

    map<int,double> xErrMap = xErr->cellIntegrals(cellIDs,mesh,5,true);
    map<int,double> yErrMap = yErr->cellIntegrals(cellIDs,mesh,5,true);
    map<int,double> restErrMap = restErr->cellIntegrals(cellIDs,mesh,5,true);
    for (vector<ElementPtr>::iterator elemIt = mesh->activeElements().begin(); elemIt!=mesh->activeElements().end(); elemIt++)
    {
      int cellID = (*elemIt)->cellID();
      double err = xErrMap[cellID]+ yErrMap[cellID] + restErrMap[cellID];
      if (rank==0)
        cout << "err thru LT = " << sqrt(err) << ", while energy err = " << energyError[cellID] << endl;
    }

    map<int,double> ratio,xErr,yErr;
    vector<ElementPtr> elems = mesh->activeElements();
    for (vector<ElementPtr>::iterator elemIt = elems.begin(); elemIt!=elems.end(); elemIt++)
    {
      int cellID = (*elemIt)->cellID();
      ratio[cellID] = 0.0;
      xErr[cellID] = 0.0;
      yErr[cellID] = 0.0;
      if (std::find(cellIDs.begin(),cellIDs.end(),cellID)!=cellIDs.end())  // if this cell is above energy thresh
      {
        ratio[cellID] = yErrMap[cellID]/xErrMap[cellID];
        xErr[cellID] = xErrMap[cellID];
        yErr[cellID] = yErrMap[cellID];
      }
    }
    FunctionPtr ratioFxn = Teuchos::rcp(new EnergyErrorFunction(ratio));
    FunctionPtr xErrFxn = Teuchos::rcp(new EnergyErrorFunction(xErr));
    FunctionPtr yErrFxn = Teuchos::rcp(new EnergyErrorFunction(yErr));
    std::ostringstream oss;
    oss << refIndex;
    exporter.exportFunction(ratioFxn, string("ratio")+oss.str());
    exporter.exportFunction(xErrFxn, string("xErr")+oss.str());
    exporter.exportFunction(yErrFxn, string("yErr")+oss.str());

    if (useAnisotropy)
    {
      refinementStrategy.refine(rank==0,xErrMap,yErrMap); //anisotropic refinements
    }
    else
    {
      refinementStrategy.refine(rank==0); // no anisotropy
    }

    solution->condensedSolve();
  }

  // final solve on final mesh
  solution->condensedSolve();

  ////////////////////   print to file   ///////////////////////

  FunctionPtr orderFxn = Teuchos::rcp(new MeshPolyOrderFunction(mesh));
  std::ostringstream oss;
  oss << nCells;
  if (rank==0)
  {
    exporter.exportSolution(string("robustIP")+oss.str());
    exporter.exportFunction(orderFxn, "meshOrder");
    cout << endl;
  }

  return 0;
}