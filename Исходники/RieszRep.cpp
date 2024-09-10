// computes riesz representation over a single element - map is from int (testID) to FieldContainer of values (sized cellIndex, numPoints)
void RieszRep::computeRepresentationValues(FieldContainer<double> &values, int testID, IntrepidExtendedTypes::EOperatorExtended op, BasisCachePtr basisCache){

  if (_repsNotComputed){
    cout << "Computing riesz rep dofs" << endl;
    computeRieszRep();
  }

  int spaceDim = _mesh->getTopology()->getSpaceDim();
  int numCells = values.dimension(0);
  int numPoints = values.dimension(1);
  vector<GlobalIndexType> cellIDs = basisCache->cellIDs();

  // all elems coming in should be of same type
  ElementPtr elem = _mesh->getElement(cellIDs[0]);
  ElementTypePtr elemTypePtr = elem->elementType();   
  DofOrderingPtr testOrderingPtr = elemTypePtr->testOrderPtr;
  CellTopoPtrLegacy cellTopoPtr = elemTypePtr->cellTopoPtr;
  int numTestDofsForVarID = testOrderingPtr->getBasisCardinality(testID, 0);
  BasisPtr testBasis = testOrderingPtr->getBasis(testID);
  
  bool testBasisIsVolumeBasis = (spaceDim == testBasis->domainTopology()->getDimension());  
  bool useCubPointsSideRefCell = testBasisIsVolumeBasis && basisCache->isSideCache();
  
  Teuchos::RCP< const FieldContainer<double> > transformedBasisValues = basisCache->getTransformedValues(testBasis,op,useCubPointsSideRefCell);
  
  int rank = values.rank() - 2; // if values are shaped as (C,P), scalar...
  if (rank > 1) {
    cout << "ranks greater than 1 not presently supported...\n";
    TEUCHOS_TEST_FOR_EXCEPTION(true, std::invalid_argument, "ranks greater than 1 not presently supported...");
  }
  
//  Camellia::print("cellIDs",cellIDs);
  
  values.initialize(0.0);
  for (int cellIndex = 0;cellIndex<numCells;cellIndex++){
    int cellID = cellIDs[cellIndex];
    for (int j = 0;j<numTestDofsForVarID;j++) {
      int dofIndex = testOrderingPtr->getDofIndex(testID, j);
      for (int i = 0;i<numPoints;i++) {
        if (rank==0) {
          double basisValue = (*transformedBasisValues)(cellIndex,j,i);
          values(cellIndex,i) += basisValue*_rieszRepDofsGlobal[cellID](dofIndex);
        } else {
          for (int d = 0; d<spaceDim; d++) {
            double basisValue = (*transformedBasisValues)(cellIndex,j,i,d);
            values(cellIndex,i,d) += basisValue*_rieszRepDofsGlobal[cellID](dofIndex);
          }
        }
      }
    }
  }
//  TestSuite::serializeOutput("rep values", values);
}