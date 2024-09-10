int main(int argc, char *argv[])
{
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
  bool zeroL2 = args.Input("--zeroL2", "take L2 term on v in robust norm to zero", false);
  args.Process();

  ////////////////////   DECLARE VARIABLES   ///////////////////////
  // define test variables
  VarFactory varFactory;
  VarPtr tau = varFactory.testVar("\\tau", HDIV);
  VarPtr v = varFactory.testVar("v", HGRAD);

  // define trial variables
  VarPtr uhat = varFactory.traceVar("\\widehat{u}");
  VarPtr beta_n_u_minus_sigma_n = varFactory.fluxVar("\\widehat{\\beta \\cdot n u - \\sigma_{n}}");
  VarPtr u = varFactory.fieldVar("u");
  VarPtr sigma = varFactory.fieldVar("sigma", VECTOR_L2);

  vector<double> beta;
  beta.push_back(1.0);
  beta.push_back(0.0);

  ////////////////////   DEFINE BILINEAR FORM   ///////////////////////
  BFPtr bf = Teuchos::rcp( new BF(varFactory) );
  // tau terms:
  bf->addTerm(sigma / epsilon, tau);
  bf->addTerm(u, tau->div());
  bf->addTerm(-uhat, tau->dot_normal());

  // v terms:
  bf->addTerm( sigma, v->grad() );
  bf->addTerm( beta * u, - v->grad() );
  bf->addTerm( beta_n_u_minus_sigma_n, v);

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

  // // robust test norm
  // IPPtr robIP = Teuchos::rcp(new IP);
  // FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(epsilon) );
  // if (!enforceLocalConservation)
  //   robIP->addTerm( ip_scaling * v );
  // robIP->addTerm( sqrt(epsilon) * v->grad() );
  // // Weight these two terms for inflow
  // FunctionPtr ip_weight = Teuchos::rcp( new IPWeight() );
  // robIP->addTerm( ip_weight * beta * v->grad() );
  // robIP->addTerm( ip_weight * tau->div() );
  // robIP->addTerm( ip_scaling/sqrt(epsilon) * tau );
  // if (enforceLocalConservation)
  //   robIP->addZeroMeanTerm( v );

  ////////////////////   SPECIFY RHS   ///////////////////////
  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );
  FunctionPtr f = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );
  Teuchos::RCP<PenaltyConstraints> pc = Teuchos::rcp( new PenaltyConstraints );

  FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  FunctionPtr one = Teuchos::rcp( new ConstantScalarFunction(1.0) );
  FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );

  SpatialFilterPtr lBoundary = Teuchos::rcp( new LeftBoundary );
  SpatialFilterPtr tbBoundary = Teuchos::rcp( new TopBottomBoundary );
  SpatialFilterPtr rBoundary = Teuchos::rcp( new RightBoundary );
  // SpatialFilterPtr leftCircleBoundary = Teuchos::rcp( new LeftCircleBoundary );
  // SpatialFilterPtr rightCircleBoundary = Teuchos::rcp( new RightCircleBoundary );
  SpatialFilterPtr circleBoundary = Teuchos::rcp( new CircleBoundary );

  bc->addDirichlet(beta_n_u_minus_sigma_n, lBoundary, zero);
  bc->addDirichlet(beta_n_u_minus_sigma_n, tbBoundary, zero);
  pc->addConstraint(beta*uhat->times_normal() - beta_n_u_minus_sigma_n == zero, rBoundary);
  // bc->addDirichlet(uhat, leftCircleBoundary, one);
  // bc->addDirichlet(beta_n_u_minus_sigma_n, rightCircleBoundary, beta*n*one);
  bc->addDirichlet(uhat, circleBoundary, one);


  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int H1Order = 3, pToAdd = 2;
  Teuchos::RCP<Mesh> mesh;
  mesh = MeshFactory::shiftedHemkerMesh(-3, 9, 6, 1, bf, H1Order, pToAdd);
  // mesh = BuildHemkerMesh(bf, nseg, circleMesh, triangulateMesh, H1Order, pToAdd);

  ////////////////////   SOLVE & REFINE   ///////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, ip) );
  solution->setFilter(pc);

  if (enforceLocalConservation)
  {
    FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
    solution->lagrangeConstraints()->addConstraint(beta_n_u_minus_sigma_n == zero);
  }

  double energyThreshold = 0.25; // for mesh refinements
  RefinementStrategy refinementStrategy( solution, energyThreshold );
  Teuchos::RCP<RefinementHistory> refHistory = Teuchos::rcp( new RefinementHistory );
  mesh->registerObserver(refHistory);
#ifdef saveVTK
  VTKExporter exporter(solution, mesh, varFactory);
#endif
  ofstream errOut;
  if (commRank == 0)
    errOut.open("hemker_err.txt");

  for (int refIndex=0; refIndex<=numRefs; refIndex++)
  {
    solution->solve(false);

    double energy_error = solution->energyErrorTotal();
    if (commRank==0)
    {
      stringstream outfile;
      outfile << "hemker_" << refIndex;
#ifdef saveVTK
      exporter.exportSolution(outfile.str());
#endif

      // Check local conservation
      FunctionPtr flux = Teuchos::rcp( new PreviousSolutionFunction(solution, beta_n_u_minus_sigma_n) );
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