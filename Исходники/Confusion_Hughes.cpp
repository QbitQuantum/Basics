int main(int argc, char *argv[])
{
#ifdef HAVE_MPI
  Teuchos::GlobalMPISession mpiSession(&argc, &argv,0);
  int rank=mpiSession.getRank();
  int numProcs=mpiSession.getNProc();
#else
  int rank = 0;
  int numProcs = 1;
#endif
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

  vector<double> beta_const;
  double c = sqrt(1.25);
  beta_const.push_back(1.0/c);
  beta_const.push_back(.5/c);
//  FunctionPtr beta = Teuchos::rcp(new Beta());

  double eps = 1e-3;

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

  // quasi-optimal norm
  IPPtr qoptIP = Teuchos::rcp(new IP);
  qoptIP->addTerm( v );
  qoptIP->addTerm( tau / eps + v->grad() );
  qoptIP->addTerm( beta_const * v->grad() - tau->div() );

  // robust test norm
  IPPtr robIP = Teuchos::rcp(new IP);
  FunctionPtr ip_scaling = Teuchos::rcp( new EpsilonScaling(eps) );
  if (enforceLocalConservation)
  {
    robIP->addZeroMeanTerm( v );
  }
  else
  {
    robIP->addTerm( ip_scaling * v );
  }
  robIP->addTerm( sqrt(eps) * v->grad() );

  bool useNewBC = false;
  FunctionPtr weight = Teuchos::rcp( new SqrtWeight(eps) );
  if (useNewBC)
  {
    robIP->addTerm( beta_const * v->grad() );
    robIP->addTerm( tau->div() );
    robIP->addTerm( ip_scaling/sqrt(eps) * tau );
  }
  else
  {
    robIP->addTerm( weight * beta_const * v->grad() );
    robIP->addTerm( weight * tau->div() );
    robIP->addTerm( weight * ip_scaling/sqrt(eps) * tau );
  }


  ////////////////////   SPECIFY RHS   ///////////////////////
  FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
  Teuchos::RCP<RHSEasy> rhs = Teuchos::rcp( new RHSEasy );
  FunctionPtr f = zero;
  rhs->addTerm( f * v ); // obviously, with f = 0 adding this term is not necessary!

  ////////////////////   CREATE BCs   ///////////////////////
  Teuchos::RCP<BCEasy> bc = Teuchos::rcp( new BCEasy );
  SpatialFilterPtr inflowBoundary = Teuchos::rcp( new InflowSquareBoundary );
  SpatialFilterPtr outflowBoundary = Teuchos::rcp( new OutflowSquareBoundary );

  FunctionPtr u0 = Teuchos::rcp( new U0 );
  FunctionPtr n = Teuchos::rcp( new UnitNormalFunction );
  bc->addDirichlet(uhat, outflowBoundary, zero);
  if (useNewBC)
  {
    bc->addDirichlet(beta_n_u_minus_sigma_n, inflowBoundary, beta_const*n*u0);
  }
  else
  {
    SpatialFilterPtr inflowBot = Teuchos::rcp( new InflowSquareBot );
    SpatialFilterPtr inflowLeft = Teuchos::rcp( new InflowSquareLeft );

    bc->addDirichlet(beta_n_u_minus_sigma_n, inflowLeft, beta_const*n*u0);
    bc->addDirichlet(uhat, inflowBot, u0);
  }

  // Teuchos::RCP<PenaltyConstraints> pc = Teuchos::rcp(new PenaltyConstraints);
  // pc->addConstraint(uhat==u0,inflowBoundary);

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int H1Order = 2, pToAdd = 2;

  FieldContainer<double> quadPoints(4,2);

  quadPoints(0,0) = 0.0; // x1
  quadPoints(0,1) = 0.0; // y1
  quadPoints(1,0) = 1.0;
  quadPoints(1,1) = 0.0;
  quadPoints(2,0) = 1.0;
  quadPoints(2,1) = 1.0;
  quadPoints(3,0) = 0.0;
  quadPoints(3,1) = 1.0;

  int nCells = 2;
  int horizontalCells = nCells, verticalCells = nCells;

  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> mesh = Mesh::buildQuadMesh(quadPoints, horizontalCells, verticalCells,
                            confusionBF, H1Order, H1Order+pToAdd);


  ////////////////////   SOLVE & REFINE   ///////////////////////
  Teuchos::RCP<Solution> solution = Teuchos::rcp( new Solution(mesh, bc, rhs, robIP) );
  // solution->setFilter(pc);

  if (enforceLocalConservation)
  {
    FunctionPtr zero = Teuchos::rcp( new ConstantScalarFunction(0.0) );
    solution->lagrangeConstraints()->addConstraint(beta_n_u_minus_sigma_n == zero);
  }

  double energyThreshold = 0.2; // for mesh refinements
  RefinementStrategy refinementStrategy( solution, energyThreshold );

  int numRefs = 9;

  for (int refIndex=0; refIndex<numRefs; refIndex++)
  {
    solution->solve(false);
    refinementStrategy.refine(rank==0); // print to console on rank 0
  }
  // one more solve on the final refined mesh:
  solution->solve(false);

  if (rank==0)
  {
    solution->writeToVTK("Hughes.vtu",min(H1Order+1,4));
    solution->writeFluxesToFile(uhat->ID(), "uhat.dat");

    cout << "wrote files: u.m, uhat.dat\n";
  }

  return 0;
}