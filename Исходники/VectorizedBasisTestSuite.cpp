bool VectorizedBasisTestSuite::testPoisson()
{
  bool success = true;

  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactoryPtr varFactory = VarFactory::varFactory();
  VarPtr tau = varFactory->testVar("\\tau", HDIV);
  VarPtr v = varFactory->testVar("v", HGRAD);

  // define trial variables
  VarPtr uhat = varFactory->traceVar("\\widehat{u}");
  VarPtr sigma_n = varFactory->fluxVar("\\widehat{\\sigma_{n}}");
  VarPtr u = varFactory->fieldVar("u");
  VarPtr sigma = varFactory->fieldVar("\\sigma", VECTOR_L2);

  ////////////////////   DEFINE BILINEAR FORM   ///////////////////////
  BFPtr bf = Teuchos::rcp( new BF(varFactory) );
  // tau terms:
  bf->addTerm(sigma, tau);
  bf->addTerm(u, tau->div());
  bf->addTerm(-uhat, tau->dot_normal());

  // v terms:
  bf->addTerm( sigma, v->grad() );
  bf->addTerm( -sigma_n, v);

  ////////////////////   DEFINE INNER PRODUCT(S)   ///////////////////////
  IPPtr ip = bf->graphNorm();

  ////////////////////   SPECIFY RHS   ///////////////////////
  RHSPtr rhs = RHS::rhs();
  FunctionPtr f = Function::constant(1.0);
  rhs->addTerm( f * v );

  ////////////////////   CREATE BCs   ///////////////////////
  BCPtr bc = BC::bc();
  SpatialFilterPtr boundary = SpatialFilter::allSpace();
  FunctionPtr zero = Function::zero();
  bc->addDirichlet(uhat, boundary, zero);

  ////////////////////   BUILD MESH   ///////////////////////
  int H1Order = 3, pToAdd = 2;
  // define nodes for mesh
  FieldContainer<double> meshBoundary(4,2);

  meshBoundary(0,0) = 0.0; // x1
  meshBoundary(0,1) = 0.0; // y1
  meshBoundary(1,0) = 1.0;
  meshBoundary(1,1) = 0.0;
  meshBoundary(2,0) = 1.0;
  meshBoundary(2,1) = 1.0;
  meshBoundary(3,0) = 0.0;
  meshBoundary(3,1) = 1.0;

  int horizontalCells = 1, verticalCells = 1;

  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = MeshFactory::buildQuadMesh(meshBoundary, horizontalCells, verticalCells,
                            bf, H1Order, H1Order+pToAdd, false);

  ////////////////////   SOLVE & REFINE   ///////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, ip) );
  double energyThreshold = 0.2; // for mesh refinements
  RefinementStrategy refinementStrategy( solution, energyThreshold );
#ifdef USE_VTK
  VTKExporter exporter(solution, mesh, varFactory);
#endif

  for (int refIndex=0; refIndex<=4; refIndex++)
  {
    solution->solve(false);
#ifdef USE_VTK
    // output commented out because it's not properly part of the test.
//    stringstream outfile;
//    outfile << "test_" << refIndex;
//    exporter.exportSolution(outfile.str());
#endif

    if (refIndex < 4)
      refinementStrategy.refine(false); // don't print to console
  }
  return success;
}