// tests Riesz inversion by integration by parts
bool LinearTermTests::testRieszInversion()
{
  bool success = true;

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
  double eps = .01;

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

  ////////////////////   BUILD MESH   ///////////////////////
  // define nodes for mesh
  int H1Order = 1;
  int pToAdd = 1;

  FieldContainer<double> quadPoints(4,2);

  quadPoints(0,0) = 0.0; // x1
  quadPoints(0,1) = 0.0; // y1
  quadPoints(1,0) = 1.0;
  quadPoints(1,1) = 0.0;
  quadPoints(2,0) = 1.0;
  quadPoints(2,1) = 1.0;
  quadPoints(3,0) = 0.0;
  quadPoints(3,1) = 1.0;

  int nCells = 1;
  int horizontalCells = nCells, verticalCells = nCells;
  // create a pointer to a new mesh:
  Teuchos::RCP<Mesh> myMesh = MeshFactory::buildQuadMesh(quadPoints, horizontalCells, verticalCells,
                              confusionBF, H1Order, H1Order+pToAdd);

  ElementTypePtr elemType = myMesh->getElement(0)->elementType();
  BasisCachePtr basisCache = Teuchos::rcp(new BasisCache(elemType, myMesh));

  vector<GlobalIndexType> cellIDs;
  vector<ElementPtr> elems = myMesh->activeElements();
  vector<ElementPtr>::iterator elemIt;
  for (elemIt=elems.begin(); elemIt!=elems.end(); elemIt++)
  {
    int cellID = (*elemIt)->cellID();
    cellIDs.push_back(cellID);
  }
  bool createSideCacheToo = true;

  basisCache->setPhysicalCellNodes(myMesh->physicalCellNodesGlobal(elemType), cellIDs, createSideCacheToo);

  LinearTermPtr integrand = Teuchos::rcp(new LinearTerm);// residual
  LinearTermPtr integrandIBP = Teuchos::rcp(new LinearTerm);// residual

  vector<double> e1(2); // (1,0)
  vector<double> e2(2); // (0,1)
  e1[0] = 1;
  e2[1] = 1;
  FunctionPtr n = Function::normal();
  FunctionPtr X = Function::xn(1);
  FunctionPtr Y = Function::yn(1);
  FunctionPtr testFxn1 = X;
  FunctionPtr testFxn2 = Y;
  FunctionPtr divTestFxn = testFxn1->dx() + testFxn2->dy();
  FunctionPtr vectorTest = testFxn1*e1 + testFxn2*e2;

  integrand->addTerm(divTestFxn*v);
  integrandIBP->addTerm(vectorTest*n*v - vectorTest*v->grad()); // boundary term

  IPPtr sobolevIP = Teuchos::rcp(new IP);
  sobolevIP->addTerm(v);
  sobolevIP->addTerm(tau);

  Teuchos::RCP<RieszRep> riesz = Teuchos::rcp(new RieszRep(myMesh, sobolevIP, integrand));
  //  riesz->setPrintOption(true);
  riesz->computeRieszRep();
  Teuchos::RCP<RieszRep> rieszIBP = Teuchos::rcp(new RieszRep(myMesh, sobolevIP, integrandIBP));
  riesz->setFunctional(integrandIBP);
  //  rieszIBP->setPrintOption(true);
  rieszIBP->computeRieszRep();

  FunctionPtr rieszOrigFxn = RieszRep::repFunction(v,riesz);
  FunctionPtr rieszIBPFxn = RieszRep::repFunction(v,rieszIBP);
  int numCells = basisCache->getPhysicalCubaturePoints().dimension(0);
  int numPts = basisCache->getPhysicalCubaturePoints().dimension(1);

  FieldContainer<double> valOriginal( numCells, numPts);
  FieldContainer<double> valIBP( numCells, numPts);
  rieszOrigFxn->values(valOriginal,basisCache);
  rieszIBPFxn->values(valIBP,basisCache);

  double maxDiff;
  double tol = 1e-14;
  success = TestSuite::fcsAgree(valOriginal,valIBP,tol,maxDiff);

  if (success==false)
  {
    cout << "Failed TestRieszInversion with maxDiff = " << maxDiff << endl;
  }
  return success;
}