int main(int argc, char *argv[]) {
  // Process command line arguments
  if (argc > 1)
    numRefs = atof(argv[1]);
#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  int rank=mpiSession.getRank();
  int numProcs=mpiSession.getNProc();
#else
  int rank = 0;
  int numProcs = 1;
#endif

  FunctionPtr beta = Teuchos::rcp(new Beta());

  ////////////////////////////////////////////////////////////////////
  // DEFINE VARIABLES 
  ////////////////////////////////////////////////////////////////////
  // test variables
  VarFactory varFactory; 
  VarPtr tau = varFactory.testVar("\\tau", HDIV);
  VarPtr v = varFactory.testVar("v", HGRAD);

  // trial variables
  VarPtr uhat = varFactory.traceVar("\\widehat{u}");
  VarPtr beta_n_u_minus_sigma_n = varFactory.fluxVar("\\widehat{\\beta \\cdot n u - \\sigma_{n}}");
  VarPtr u = varFactory.fieldVar("u");
  VarPtr sigma1 = varFactory.fieldVar("\\sigma_1");
  VarPtr sigma2 = varFactory.fieldVar("\\sigma_2");

  ////////////////////////////////////////////////////////////////////
  // CREATE MESH 
  ////////////////////////////////////////////////////////////////////

  BFPtr confusionBF = Teuchos::rcp( new BF(varFactory) );

  FieldContainer<double> meshBoundary(4,2);

  meshBoundary(0,0) =  0.0; // x1
  meshBoundary(0,1) = -2.0; // y1
  meshBoundary(1,0) =  4.0;
  meshBoundary(1,1) = -2.0;
  meshBoundary(2,0) =  4.0;
  meshBoundary(2,1) =  2.0;
  meshBoundary(3,0) =  0.0;
  meshBoundary(3,1) =  2.0;

  int horizontalCells = 4, verticalCells = 4;

  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = Mesh::buildQuadMesh(meshBoundary, horizontalCells, verticalCells,
      confusionBF, H1Order, H1Order+pToAdd, false);

  ////////////////////////////////////////////////////////////////////
  // INITIALIZE BACKGROUND FLOW FUNCTIONS
  ////////////////////////////////////////////////////////////////////

  BCPtr nullBC = Teuchos::rcp((BC*)NULL);
  RHSPtr nullRHS = Teuchos::rcp((RHS*)NULL);
  IPPtr nullIP = Teuchos::rcp((IP*)NULL);
  SolutionPtr prevTimeFlow = Teuchos::rcp(new Solution(mesh, nullBC, nullRHS, nullIP) );  
  SolutionPtr flowResidual = Teuchos::rcp(new Solution(mesh, nullBC, nullRHS, nullIP) );  

  FunctionPtr u_prev_time = Teuchos::rcp( new PreviousSolutionFunction(prevTimeFlow, u) );

  // ==================== SET INITIAL GUESS ==========================
  double u_free = 0.0;
  double sigma1_free = 0.0;
  double sigma2_free = 0.0;
  map<int, Teuchos::RCP<Function> > functionMap;
  functionMap[u->ID()] = Teuchos::rcp( new ConstantScalarFunction(u_free) );
  functionMap[sigma1->ID()] = Teuchos::rcp( new ConstantScalarFunction(sigma1_free) );
  functionMap[sigma2->ID()] = Teuchos::rcp( new ConstantScalarFunction(sigma2_free) );

  prevTimeFlow->projectOntoMesh(functionMap);
  // ==================== END SET INITIAL GUESS ==========================

  ////////////////////////////////////////////////////////////////////
  // DEFINE BILINEAR FORM
  ////////////////////////////////////////////////////////////////////

  // tau terms:
  confusionBF->addTerm(sigma1 / epsilon, tau->x());
  confusionBF->addTerm(sigma2 / epsilon, tau->y());
  confusionBF->addTerm(u, tau->div());
  confusionBF->addTerm(-uhat, tau->dot_normal());

  // v terms:
  confusionBF->addTerm( sigma1, v->dx() );
  confusionBF->addTerm( sigma2, v->dy() );
  confusionBF->addTerm( beta * u, - v->grad() );
  confusionBF->addTerm( beta_n_u_minus_sigma_n, v);

  ////////////////////////////////////////////////////////////////////
  // TIMESTEPPING TERMS
  ////////////////////////////////////////////////////////////////////
  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );

  double dt = 0.25;
  FunctionPtr invDt = Teuchos::rcp(new ScalarParamFunction(1.0/dt));    
  if (rank==0){
    cout << "Timestep dt = " << dt << endl;
  }
  if (transient)
  {
    confusionBF->addTerm( u, invDt*v );
    rhs->addTerm( u_prev_time * invDt * v );
  }

  ////////////////////////////////////////////////////////////////////
  // DEFINE INNER PRODUCT
  ////////////////////////////////////////////////////////////////////

  // mathematician's norm
  IPPtr mathIP = Teuchos::rcp(new IP());
  mathIP->addTerm(tau);
  mathIP->addTerm(tau->div());

  mathIP->addTerm(v);
  mathIP->addTerm(v->grad());

  // quasi-optimal norm
  IPPtr qoptIP = Teuchos::rcp(new IP);
  qoptIP->addTerm( v );
  qoptIP->addTerm( tau / epsilon + v->grad() );
  qoptIP->addTerm( beta * v->grad() - tau->div() );

  // robust test norm
  IPPtr robIP = Teuchos::rcp(new IP);
  FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(epsilon) ); 
  if (!enforceLocalConservation)
  {
    robIP->addTerm( ip_scaling * v );
    if (transient)
      robIP->addTerm( invDt * v );
  }
  robIP->addTerm( sqrt(epsilon) * v->grad() );
  // Weight these two terms for inflow
  FunctionPtr ip_weight = Teuchos::rcp( new IPWeight() );
  robIP->addTerm( ip_weight * beta * v->grad() );
  robIP->addTerm( ip_weight * tau->div() );
  robIP->addTerm( ip_scaling/sqrt(epsilon) * tau );
  if (enforceLocalConservation)
    robIP->addZeroMeanTerm( v );

  ////////////////////////////////////////////////////////////////////
  // DEFINE RHS
  ////////////////////////////////////////////////////////////////////

  FunctionPtr f = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////////////////////////////////////////////////////
  // DEFINE BC
  ////////////////////////////////////////////////////////////////////

  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );
  // Teuchos::RCP<PenaltyConstraints> pc = Teuchos::rcp( new PenaltyConstraints );
  SpatialFilterPtr lBoundary = Teuchos::rcp( new LeftBoundary );
  SpatialFilterPtr tbBoundary = Teuchos::rcp( new TopBottomBoundary );
  SpatialFilterPtr rBoundary = Teuchos::rcp( new RightBoundary );
  FunctionPtr u0 = Teuchos::rcp( new ZeroBC );
  FunctionPtr u_inlet = Teuchos::rcp( new InletBC );
  // FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );
  bc->addDirichlet(beta_n_u_minus_sigma_n, lBoundary, u_inlet);
  bc->addDirichlet(beta_n_u_minus_sigma_n, tbBoundary, u0);
  bc->addDirichlet(uhat, rBoundary, u0);
  // pc->addConstraint(beta_n_u_minus_sigma_n - uhat == u0, rBoundary);

  ////////////////////////////////////////////////////////////////////
  // CREATE SOLUTION OBJECT
  ////////////////////////////////////////////////////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, robIP) );
  // solution->setFilter(pc);

  // ==================== Enforce Local Conservation ==================
  if (enforceLocalConservation) {
    if (transient)
    {
      FunctionPtr conserved_rhs = u_prev_time * invDt;
      LinearTermPtr conserved_quantity = invDt * u;
      LinearTermPtr flux_part = Teuchos::rcp(new LinearTerm(-1.0, beta_n_u_minus_sigma_n));
      conserved_quantity->addTerm(flux_part, true);
      // conserved_quantity = conserved_quantity - beta_n_u_minus_sigma_n;
      solution->lagrangeConstraints()->addConstraint(conserved_quantity == conserved_rhs);
    }
    else
    {
      FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
      solution->lagrangeConstraints()->addConstraint(beta_n_u_minus_sigma_n == zero);
    }
  }

  // ==================== Register Solutions ==========================
  mesh->registerSolution(solution);
  mesh->registerSolution(prevTimeFlow); // u_t(i-1)
  mesh->registerSolution(flowResidual); // u_t(i-1)

  double energyThreshold = 0.25; // for mesh refinements
  Teuchos::RCP<RefinementStrategy> refinementStrategy;
  refinementStrategy = Teuchos::rcp(new RefinementStrategy(solution,energyThreshold));

  ////////////////////////////////////////////////////////////////////
  // PSEUDO-TIME SOLVE STRATEGY 
  ////////////////////////////////////////////////////////////////////

  double time_tol = 1e-8;
  for (int refIndex=0; refIndex<=numRefs; refIndex++)
  {
    double L2_time_residual = 1e7;
    int timestepCount = 0;
    if (!transient)
      numTimeSteps = 1;
    while((L2_time_residual > time_tol) && (timestepCount < numTimeSteps))
    {
      solution->solve(false);
      // subtract solutions to get residual
      flowResidual->setSolution(solution); // reset previous time solution to current time sol
      flowResidual->addSolution(prevTimeFlow, -1.0);       
      double L2u = flowResidual->L2NormOfSolutionGlobal(u->ID());
      double L2sigma1 = flowResidual->L2NormOfSolutionGlobal(sigma1->ID());
      double L2sigma2 = flowResidual->L2NormOfSolutionGlobal(sigma2->ID());
      L2_time_residual = sqrt(L2u*L2u + L2sigma1*L2sigma1 + L2sigma2*L2sigma2);
      cout << endl << "Timestep: " << timestepCount << ", dt = " << dt << ", Time residual = " << L2_time_residual << endl;    	

      if (rank == 0)
      {
        stringstream outfile;
        if (transient)
          outfile << "TransientConfusion_" << refIndex << "_" << timestepCount;
        else
          outfile << "TransientConfusion_" << refIndex;
        solution->writeToVTK(outfile.str(), 5);
      }

      //////////////////////////////////////////////////////////////////////////
      // Check conservation by testing against one
      //////////////////////////////////////////////////////////////////////////
      VarPtr testOne = varFactory.testVar("1", CONSTANT_SCALAR);
      // Create a fake bilinear form for the testing
      BFPtr fakeBF = Teuchos::rcp( new BF(varFactory) );
      // Define our mass flux
      FunctionPtr flux_current_time = Teuchos::rcp( new PreviousSolutionFunction(solution, beta_n_u_minus_sigma_n) );
      FunctionPtr delta_u = Teuchos::rcp( new PreviousSolutionFunction(flowResidual, u) );
      LinearTermPtr surfaceFlux = -1.0 * flux_current_time * testOne;
      LinearTermPtr volumeChange = invDt * delta_u * testOne;
      LinearTermPtr massFluxTerm;
      if (transient)
      {
        massFluxTerm = volumeChange;
        // massFluxTerm->addTerm(surfaceFlux);
      }
      else
      {
        massFluxTerm = surfaceFlux;
      }
      // cout << "surface case = " << surfaceFlux->summands()[0].first->boundaryValueOnly() << " volume case = " << volumeChange->summands()[0].first->boundaryValueOnly() << endl;

      // FunctionPtr massFlux= Teuchos::rcp( new PreviousSolutionFunction(solution, beta_n_u_minus_sigma_n) );
      // LinearTermPtr massFluxTerm = massFlux * testOne;

      Teuchos::RCP<shards::CellTopology> quadTopoPtr = Teuchos::rcp(new shards::CellTopology(shards::getCellTopologyData<shards::Quadrilateral<4> >() ));
      DofOrderingFactory dofOrderingFactory(fakeBF);
      int fakeTestOrder = H1Order;
      DofOrderingPtr testOrdering = dofOrderingFactory.testOrdering(fakeTestOrder, *quadTopoPtr);

      int testOneIndex = testOrdering->getDofIndex(testOne->ID(),0);
      vector< ElementTypePtr > elemTypes = mesh->elementTypes(); // global element types
      map<int, double> massFluxIntegral; // cellID -> integral
      double maxMassFluxIntegral = 0.0;
      double totalMassFlux = 0.0;
      double totalAbsMassFlux = 0.0;
      for (vector< ElementTypePtr >::iterator elemTypeIt = elemTypes.begin(); elemTypeIt != elemTypes.end(); elemTypeIt++) 
      {
        ElementTypePtr elemType = *elemTypeIt;
        vector< ElementPtr > elems = mesh->elementsOfTypeGlobal(elemType);
        vector<int> cellIDs;
        for (int i=0; i<elems.size(); i++) {
          cellIDs.push_back(elems[i]->cellID());
        }
        FieldContainer<double> physicalCellNodes = mesh->physicalCellNodesGlobal(elemType);
        BasisCachePtr basisCache = Teuchos::rcp( new BasisCache(elemType,mesh) );
        basisCache->setPhysicalCellNodes(physicalCellNodes,cellIDs,true); // true: create side caches
        FieldContainer<double> cellMeasures = basisCache->getCellMeasures();
        FieldContainer<double> fakeRHSIntegrals(elems.size(),testOrdering->totalDofs());
        massFluxTerm->integrate(fakeRHSIntegrals,testOrdering,basisCache,true); // true: force side evaluation
        for (int i=0; i<elems.size(); i++) {
          int cellID = cellIDs[i];
          // pick out the ones for testOne:
          massFluxIntegral[cellID] = fakeRHSIntegrals(i,testOneIndex);
        }
        // find the largest:
        for (int i=0; i<elems.size(); i++) {
          int cellID = cellIDs[i];
          maxMassFluxIntegral = max(abs(massFluxIntegral[cellID]), maxMassFluxIntegral);
        }
        for (int i=0; i<elems.size(); i++) {
          int cellID = cellIDs[i];
          maxMassFluxIntegral = max(abs(massFluxIntegral[cellID]), maxMassFluxIntegral);
          totalMassFlux += massFluxIntegral[cellID];
          totalAbsMassFlux += abs( massFluxIntegral[cellID] );
        }
      }

      // Print results from processor with rank 0
      if (rank == 0)
      {
        cout << "largest mass flux: " << maxMassFluxIntegral << endl;
        cout << "total mass flux: " << totalMassFlux << endl;
        cout << "sum of mass flux absolute value: " << totalAbsMassFlux << endl;
      }

      prevTimeFlow->setSolution(solution); // reset previous time solution to current time sol
      timestepCount++;
    }

    if (refIndex < numRefs){
      if (rank==0){
        cout << "Performing refinement number " << refIndex << endl;
      }     
      refinementStrategy->refine(rank==0);    
      // RESET solution every refinement - make sure discretization error doesn't creep in
      // prevTimeFlow->projectOntoMesh(functionMap);
    }
  }

  return 0;
}