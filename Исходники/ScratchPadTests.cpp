bool ScratchPadTests::testResidualMemoryError()
{

  int rank = Teuchos::GlobalMPISession::getRank();

  double tol = 1e-11;
  bool success = true;

  int nCells = 2;
  double eps = 1e-2;

  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactoryPtr varFactory = VarFactory::varFactory();
  VarPtr tau = varFactory->testVar("\\tau", HDIV);
  VarPtr v = varFactory->testVar("v", HGRAD);

  // define trial variables
  VarPtr uhat = varFactory->traceVar("\\widehat{u}");
  VarPtr beta_n_u_minus_sigma_n = varFactory->fluxVar("\\widehat{\\beta \\cdot n u - \\sigma_{n}}");
  VarPtr u = varFactory->fieldVar("u");
  VarPtr sigma1 = varFactory->fieldVar("\\sigma_1");
  VarPtr sigma2 = varFactory->fieldVar("\\sigma_2");

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

  // robust test norm
  IPPtr robIP = Teuchos::rcp(new IP);
  robIP->addTerm(tau);
  robIP->addTerm(tau->div());
  robIP->addTerm(v->grad());
  robIP->addTerm(v);

  ////////////////////   SPECIFY RHS   ///////////////////////

  FunctionPtr zero = Function::constant(0.0);
  FunctionPtr one = Function::constant(1.0);
  RHSPtr rhs = RHS::rhs();
  FunctionPtr f = zero;
  //  FunctionPtr f = one;
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  BCPtr bc = BC::bc();
  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new LRInflowSquareBoundary );
  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new LROutflowSquareBoundary);

  FunctionPtr n = Function::normal();

  vector<double> e1,e2;
  e1.push_back(1.0);
  e1.push_back(0.0);
  e2.push_back(0.0);
  e2.push_back(1.0);

  bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, beta*n*one);
  bc->addDirichlet(uhat, outflowBoundary, zero);

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int order = 2;
  int H1Order = order+1;
  int pToAdd = 2;

  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = MeshUtilities::buildUnitQuadMesh(nCells,confusionBF, H1Order, H1Order+pToAdd);
  //  mesh->setPartitionPolicy(Teuchos::rcp(new ZoltanMeshPartitionPolicy("HSFC")));

  ////////////////////   SOLVE & REFINE   ///////////////////////

  Teuchos::RCP<Solution> solution;
  solution = Teuchos::rcp( new Solution(mesh, bc, rhs, robIP) );
  solution->solve(false);
  mesh->registerSolution(solution);
  double energyErr1 = solution->energyErrorTotal();

  LinearTermPtr residual = rhs->linearTermCopy();
  residual->addTerm(-confusionBF->testFunctional(solution));
  RieszRepPtr rieszResidual = Teuchos::rcp(new RieszRep(mesh, robIP, residual));
  rieszResidual->computeRieszRep();
  FunctionPtr e_v = RieszRep::repFunction(v,rieszResidual);
  FunctionPtr e_tau = RieszRep::repFunction(tau,rieszResidual);

  double energyThreshold = 0.2; // for mesh refinements
  RefinementStrategy refinementStrategy( solution, energyThreshold );

  refinementStrategy.refine();
  solution->solve(false);
  double energyErr2 = solution->energyErrorTotal();

  // if energy error rises
  if (energyErr1 < energyErr2)
  {
    if (rank==0)
      cout << "energy error increased from " << energyErr1 << " to " << energyErr2 << " after refinement.\n";
    success = false;
  }

  return success;
}