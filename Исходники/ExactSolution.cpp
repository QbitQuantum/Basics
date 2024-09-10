void ExactSolution::L2NormOfError(FieldContainer<double> &errorSquaredPerCell, Solution &solution, ElementTypePtr elemTypePtr, int trialID, int sideIndex, int cubDegree, double solutionLift) {
//  BasisCache(ElementTypePtr elemType, Teuchos::RCP<Mesh> mesh = Teuchos::rcp( (Mesh*) NULL ), bool testVsTest=false, int cubatureDegreeEnrichment = 0)

  DofOrdering dofOrdering = *(elemTypePtr->trialOrderPtr.get());
  BasisPtr basis = dofOrdering.getBasis(trialID,sideIndex);
  
  bool boundaryIntegral = solution.mesh()->bilinearForm()->isFluxOrTrace(trialID);
  
  BasisCachePtr basisCache;
  if (cubDegree <= 0) { // then take the default cub. degree
    basisCache = Teuchos::rcp( new BasisCache( elemTypePtr, solution.mesh() ) );
  } else {
    // we could eliminate the logic below if we just added BasisCache::setCubatureDegree()...
    // (the logic below is just to make the enriched cubature match the requested cubature degree...)
    int maxTrialDegree;
    if (!boundaryIntegral) {
      maxTrialDegree = elemTypePtr->trialOrderPtr->maxBasisDegreeForVolume();
    } else {
      maxTrialDegree = elemTypePtr->trialOrderPtr->maxBasisDegree(); // generally, this will be the trace degree
    }
    int maxTestDegree = elemTypePtr->testOrderPtr->maxBasisDegree();
    int cubDegreeEnrichment = max(cubDegree - (maxTrialDegree + maxTestDegree), 0);
    basisCache = Teuchos::rcp( new BasisCache( elemTypePtr, solution.mesh(), false, cubDegreeEnrichment) );
  }
  
  // much of this code is the same as what's in the volume integration in computeStiffness...
  FieldContainer<double> physicalCellNodes = solution.mesh()->physicalCellNodes(elemTypePtr);
  vector<GlobalIndexType> cellIDs = solution.mesh()->cellIDsOfType(elemTypePtr);
  basisCache->setPhysicalCellNodes(physicalCellNodes, cellIDs, true);
  
  if (boundaryIntegral) {
    basisCache = basisCache->getSideBasisCache(sideIndex);
  }
  
  FieldContainer<double> weightedMeasure = basisCache->getWeightedMeasures();
  FieldContainer<double> weightedErrorSquared;
  
  int numCells = basisCache->getPhysicalCubaturePoints().dimension(0);
  int numCubPoints = basisCache->getPhysicalCubaturePoints().dimension(1);
  int spaceDim = basisCache->getPhysicalCubaturePoints().dimension(2);
  
  Teuchos::Array<int> dimensions;
  dimensions.push_back(numCells);
  dimensions.push_back(numCubPoints);
  
  int basisRank = BasisFactory::basisFactory()->getBasisRank(basis);
  if (basisRank==1) {
    dimensions.push_back(spaceDim);
  }
  
  FieldContainer<double> computedValues(dimensions);
  FieldContainer<double> exactValues(dimensions);
  
  if (solutionLift != 0.0) {
    int size = computedValues.size();
    for (int i=0; i<size; i++) {
      computedValues[i] += solutionLift;
    }
  }
  
  solution.solutionValues(computedValues, trialID, basisCache);
  this->solutionValues(exactValues, trialID, basisCache);
  
//  cout << "ExactSolution: exact values:\n" << exactValues;
//  cout << "ExactSolution: computed values:\n" << computedValues;
  
  FieldContainer<double> errorSquared(numCells,numCubPoints);
  
  squaredDifference(errorSquared,computedValues,exactValues);
  
  weightedErrorSquared.resize(numCells,numCubPoints);
  for (int cellIndex=0; cellIndex<numCells; cellIndex++) {
    for (int ptIndex=0; ptIndex<numCubPoints; ptIndex++) {
      // following two lines for viewing in the debugger:
      double weight = weightedMeasure(cellIndex,ptIndex);
      double errorSquaredVal = errorSquared(cellIndex,ptIndex);
      weightedErrorSquared(cellIndex,ptIndex) = errorSquared(cellIndex,ptIndex) * weightedMeasure(cellIndex,ptIndex);
    }
  }
  
  // compute the integral
  errorSquaredPerCell.initialize(0.0);
  int numPoints = weightedErrorSquared.dimension(1);
  for (int cellIndex=0; cellIndex<numCells; cellIndex++) {
    for (int ptIndex=0; ptIndex<numPoints; ptIndex++) {
      errorSquaredPerCell(cellIndex) += weightedErrorSquared(cellIndex,ptIndex);
    }
  }
}