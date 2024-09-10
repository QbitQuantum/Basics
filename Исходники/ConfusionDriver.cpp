int main(int argc, char *argv[]) {
#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  choice::MpiArgs args( argc, argv );
#else
  choice::Args args( argc, argv );
#endif
  int commRank = Teuchos::GlobalMPISession::getRank();
  int numProcs = Teuchos::GlobalMPISession::getNProc();

  // Required arguments
  double epsilon = args.Input<double>("--epsilon", "diffusion parameter");
  int numRefs = args.Input<int>("--numRefs", "number of refinement steps");
  bool enforceLocalConservation = args.Input<bool>("--conserve", "enforce local conservation");
  int norm = args.Input<int>("--norm", "0 = graph\n    1 = robust\n    2 = modified robust");

  // Optional arguments (have defaults)
  bool zeroL2 = args.Input("--zeroL2", "take L2 term on v in robust norm to zero", true);
  args.Process();

  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactory varFactory;
  VarPtr tau = varFactory.testVar("tau", HDIV);
  VarPtr v = varFactory.testVar("v", HGRAD);

  // define trial variables
  VarPtr uhat = varFactory.traceVar("uhat");
  VarPtr fhat = varFactory.fluxVar("fhat");
  VarPtr u = varFactory.fieldVar("u");
  VarPtr sigma = varFactory.fieldVar("sigma", VECTOR_L2);

  ////////////////////   BUILD MESH   ///////////////////////
  BFPtr bf = Teuchos::rcp( new BF(varFactory) );
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

  int horizontalCells = 4, verticalCells = 4;

  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = Mesh::buildQuadMesh(meshBoundary, horizontalCells, verticalCells,
      bf, H1Order, H1Order+pToAdd, false);

  vector<double> beta;
  beta.push_back(2.0);
  beta.push_back(1.0);

  ////////////////////   DEFINE BILINEAR FORM   ///////////////////////
  // tau terms:
  bf->addTerm(sigma / epsilon, tau);
  bf->addTerm(u, tau->div());
  bf->addTerm(-uhat, tau->dot_normal());

  // v terms:
  bf->addTerm( sigma, v->grad() );
  bf->addTerm( beta * u, - v->grad() );
  bf->addTerm( fhat, v);

  ////////////////////   DEFINE INNER PRODUCT(S)   ///////////////////////
  IPPtr ip = Teuchos::rcp(new IP);
  if (norm == 0)
  {
    ip = bf->graphNorm();
    FunctionPtr h2_scaling = Teuchos::rcp( new ZeroMeanScaling );
    ip->addZeroMeanTerm( h2_scaling*v );
  }
  // Robust norm
  else if (norm == 1)
  {
    // robust test norm
    FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(epsilon) );
    FunctionPtr h2_scaling = Teuchos::rcp( new ZeroMeanScaling );
    if (!zeroL2)
      ip->addTerm( v );
    ip->addTerm( sqrt(epsilon) * v->grad() );
    // Weight these two terms for inflow
    ip->addTerm( beta * v->grad() );
    ip->addTerm( tau->div() );
    ip->addTerm( ip_scaling/sqrt(epsilon) * tau );
    if (zeroL2)
      ip->addZeroMeanTerm( h2_scaling*v );
  }
  // Modified robust norm
  else if (norm == 2)
  {
    // robust test norm
    FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(epsilon) );
    FunctionPtr h2_scaling = Teuchos::rcp( new ZeroMeanScaling );
    // FunctionPtr ip_weight = Teuchos::rcp( new IPWeight() );
    if (!zeroL2)
      ip->addTerm( v );
    ip->addTerm( sqrt(epsilon) * v->grad() );
    ip->addTerm( beta * v->grad() );
    ip->addTerm( tau->div() - beta*v->grad() );
    ip->addTerm( ip_scaling/sqrt(epsilon) * tau );
    if (zeroL2)
      ip->addZeroMeanTerm( h2_scaling*v );
  }

  ////////////////////   SPECIFY RHS   ///////////////////////
  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );
  FunctionPtr f = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );
  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowBoundary );
  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new OutflowBoundary );
  FunctionPtr u0 = Teuchos::rcp( new U0 );
  bc->addDirichlet(uhat, outflowBoundary, u0);

  FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );
  bc->addDirichlet(fhat, inflowBoundary, beta*n*u0);

  // Teuchos::RCP<PenaltyConstraints> pc = Teuchos::rcp(new PenaltyConstraints);
  // pc->addConstraint(uhat==u0,inflowBoundary);

  ////////////////////   SOLVE & REFINE   ///////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, ip) );
  // solution->setFilter(pc);

  if (enforceLocalConservation) {
    FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
    solution->lagrangeConstraints()->addConstraint(fhat == zero);
  }

  double energyThreshold = 0.2; // for mesh refinements
  RefinementStrategy refinementStrategy( solution, energyThreshold );
  VTKExporter exporter(solution, mesh, varFactory);
  ofstream errOut;
  if (commRank == 0)
    errOut.open("confusion_err.txt");

  for (int refIndex=0; refIndex<=numRefs; refIndex++){
    solution->solve(false);

    double energy_error = solution->energyErrorTotal();
    if (commRank==0){
      stringstream outfile;
      outfile << "confusion_" << refIndex;
      exporter.exportSolution(outfile.str());
      // solution->writeToVTK(outfile.str());

      // Check local conservation
      FunctionPtr flux = Function::solution(fhat, solution);
      FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
      Teuchos::Tuple<double, 3> fluxImbalances = checkConservation(flux, zero, varFactory, mesh);
      cout << "Mass flux: Largest Local = " << fluxImbalances[0]
        << ", Global = " << fluxImbalances[1] << ", Sum Abs = " << fluxImbalances[2] << endl;

      errOut << mesh->numGlobalDofs() << " " << energy_error << " "
        << fluxImbalances[0] << " " << fluxImbalances[1] << " " << fluxImbalances[2] << endl;
    }

    if (refIndex < numRefs)
      refinementStrategy.refine(commRank==0); // print to console on commRank 0
  }
  if (commRank == 0)
    errOut.close();

  return 0;
}