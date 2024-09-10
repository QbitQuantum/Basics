void FunctionTests::setup()
{
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

  vector<double> beta_const;
  beta_const.push_back(2.0);
  beta_const.push_back(1.0);

  double eps = 1e-2;

  // standard confusion bilinear form
  _confusionBF = Teuchos::rcp( new BF(varFactory) );
  // tau terms:
  _confusionBF->addTerm(sigma1 / eps, tau->x());
  _confusionBF->addTerm(sigma2 / eps, tau->y());
  _confusionBF->addTerm(u, tau->div());
  _confusionBF->addTerm(-uhat, tau->dot_normal());

  // v terms:
  _confusionBF->addTerm( sigma1, v->dx() );
  _confusionBF->addTerm( sigma2, v->dy() );
  _confusionBF->addTerm( beta_const * u, - v->grad() );
  _confusionBF->addTerm( beta_n_u_minus_sigma_n, v);

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  FieldContainer<double> quadPoints(4,2);

  quadPoints(0,0) = -1.0; // x1
  quadPoints(0,1) = -1.0; // y1
  quadPoints(1,0) = 1.0;
  quadPoints(1,1) = -1.0;
  quadPoints(2,0) = 1.0;
  quadPoints(2,1) = 1.0;
  quadPoints(3,0) = -1.0;
  quadPoints(3,1) = 1.0;

  int H1Order = 1, pToAdd = 0;
  int horizontalCells = 1, verticalCells = 1;

  // create a pointer to a new mesh:
  _spectralConfusionMesh = MeshFactory::buildQuadMesh(quadPoints, horizontalCells, verticalCells,
                           _confusionBF, H1Order, H1Order+pToAdd);

  // some 2D test points:
  // setup test points:
  static const int NUM_POINTS_1D = 10;
  double x[NUM_POINTS_1D] = {-1.0,-0.8,-0.6,-.4,-.2,0,0.2,0.4,0.6,0.8};
  double y[NUM_POINTS_1D] = {-0.8,-0.6,-.4,-.2,0,0.2,0.4,0.6,0.8,1.0};

  _testPoints = FieldContainer<double>(NUM_POINTS_1D*NUM_POINTS_1D,2);
  for (int i=0; i<NUM_POINTS_1D; i++)
  {
    for (int j=0; j<NUM_POINTS_1D; j++)
    {
      _testPoints(i*NUM_POINTS_1D + j, 0) = x[i];
      _testPoints(i*NUM_POINTS_1D + j, 1) = y[j];
    }
  }

  _elemType = _spectralConfusionMesh->getElementType(0);
  vector<GlobalIndexType> cellIDs;
  GlobalIndexType cellID = 0;
  cellIDs.push_back(cellID);
  _basisCache = Teuchos::rcp( new BasisCache( _elemType, _spectralConfusionMesh ) );
  _basisCache->setRefCellPoints(_testPoints);

  _basisCache->setPhysicalCellNodes( _spectralConfusionMesh->physicalCellNodesForCell(cellID), cellIDs, true );
}