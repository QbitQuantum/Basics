void DofOrdering::copyLikeCoefficients( FieldContainer<double> &newValues, Teuchos::RCP<DofOrdering> oldDofOrdering,
                          const FieldContainer<double> &oldValues ) {
  // copy the coefficients for the bases that agree between the two DofOrderings
  // requires that "like" bases are actually pointers to the same memory location
  TEUCHOS_TEST_FOR_EXCEPTION( newValues.rank() != 1, std::invalid_argument, "newValues.rank() != 1");
  TEUCHOS_TEST_FOR_EXCEPTION( newValues.size() != totalDofs(), std::invalid_argument, "newValues.size() != totalDofs()");
  TEUCHOS_TEST_FOR_EXCEPTION( oldValues.rank() != 1, std::invalid_argument, "oldValues.rank() != 1");
  TEUCHOS_TEST_FOR_EXCEPTION( oldValues.size() != oldDofOrdering->totalDofs(), std::invalid_argument, "oldValues.size() != oldDofOrdering->totalDofs()");
  
  newValues.initialize(0.0);
  
  for (set<int>::iterator varIDIt = varIDs.begin(); varIDIt != varIDs.end(); varIDIt++) {
    int varID = *varIDIt;
    int numSides = getNumSidesForVarID(varID);
    if ( numSides == oldDofOrdering->getNumSidesForVarID(varID) ) {
      for (int sideIndex=0; sideIndex < numSides; sideIndex++) {
        BasisPtr basis = getBasis(varID,sideIndex);
        if (basis.get() == oldDofOrdering->getBasis(varID,sideIndex).get() ) {
          // bases alike: copy coefficients
          int cardinality = basis->getCardinality();
          for (int dofOrdinal=0; dofOrdinal < cardinality; dofOrdinal++) {
            int dofIndex = getDofIndex(varID,dofOrdinal,sideIndex);
            newValues(dofIndex) = oldValues( oldDofOrdering->getDofIndex(varID,dofOrdinal,sideIndex) );
          }
        }
      }
    }
  }
}