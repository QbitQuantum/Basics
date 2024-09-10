void BilinearFormUtility::computeStiffnessMatrix(FieldContainer<double> &stiffness, 
                                                 FieldContainer<double> &innerProductMatrix,
                                                 FieldContainer<double> &optimalTestWeights) {
  // stiffness has dimensions (numCells, numTrialDofs, numTrialDofs)
  // innerProductMatrix has dim. (numCells, numTestDofs, numTestDofs)
  // optimalTestWeights has dim. (numCells, numTrialDofs, numTestDofs)
  // all this does is computes stiffness = weights^T * innerProductMatrix * weights
  int numCells = stiffness.dimension(0);
  int numTrialDofs = stiffness.dimension(1);
  int numTestDofs = innerProductMatrix.dimension(1);
  
  // check that all the dimensions are compatible:
  TEUCHOS_TEST_FOR_EXCEPTION( ( optimalTestWeights.dimension(0) != numCells ),
                     std::invalid_argument,
                     "stiffness.dimension(0) and optimalTestWeights.dimension(0) (numCells) do not match.");
  TEUCHOS_TEST_FOR_EXCEPTION( ( optimalTestWeights.dimension(1) != numTrialDofs ),
                     std::invalid_argument,
                     "numTrialDofs and optimalTestWeights.dimension(1) do not match.");
  TEUCHOS_TEST_FOR_EXCEPTION( ( optimalTestWeights.dimension(2) != numTestDofs ),
                     std::invalid_argument,
                     "numTestDofs and optimalTestWeights.dimension(2) do not match.");
  TEUCHOS_TEST_FOR_EXCEPTION( ( innerProductMatrix.dimension(2) != innerProductMatrix.dimension(1) ),
                     std::invalid_argument,
                     "innerProductMatrix.dimension(1) and innerProductMatrix.dimension(2) do not match.");
  
  TEUCHOS_TEST_FOR_EXCEPTION( ( stiffness.dimension(1) != stiffness.dimension(2) ),
                     std::invalid_argument,
                     "stiffness.dimension(1) and stiffness.dimension(2) do not match.");
  
  stiffness.initialize(0);
  
  for (int cellIndex=0; cellIndex < numCells; cellIndex++) {
    Epetra_SerialDenseMatrix weightsT(Copy,
                                     &optimalTestWeights(cellIndex,0,0),
                                     optimalTestWeights.dimension(2), // stride
                                     optimalTestWeights.dimension(2),optimalTestWeights.dimension(1));
    
    Epetra_SerialDenseMatrix ipMatrixT(Copy,
                                      &innerProductMatrix(cellIndex,0,0),
                                      innerProductMatrix.dimension(2), // stride
                                      innerProductMatrix.dimension(2),innerProductMatrix.dimension(1));
    
    Epetra_SerialDenseMatrix   stiffT (View,
                                      &stiffness(cellIndex,0,0),
                                      stiffness.dimension(2), // stride
                                      stiffness.dimension(2),stiffness.dimension(1));
    
    Epetra_SerialDenseMatrix intermediate( numTrialDofs, numTestDofs );
    
    // account for the fact that SDM is column-major and FC is row-major: 
    //   (weightsT) * (ipMatrixT)^T * (weightsT)^T
    int success = intermediate.Multiply('T','T',1.0,weightsT,ipMatrixT,0.0);
    
    if (success != 0) {
      cout << "computeStiffnessMatrix: intermediate.Multiply() failed with error code " << success << endl;
    }
    
    success = stiffT.Multiply('N','N',1.0,intermediate,weightsT,0.0);
    // stiffT is technically the transpose of stiffness, but the construction A^T * B * A is symmetric even in general...
    
    if (success != 0) {
      cout << "computeStiffnessMatrix: stiffT.Multiply() failed with error code " << success << endl;
    }
  }
  
  if ( ! checkForZeroRowsAndColumns("stiffness",stiffness) ) {
    //cout << "stiffness: " << stiffness;
  }
  
  bool enforceNumericalSymmetry = false;
  if (enforceNumericalSymmetry) {
    for (unsigned int c=0; c < numCells; c++)
      for (unsigned int i=0; i < numTrialDofs; i++)
        for (unsigned int j=i+1; j < numTrialDofs; j++)
        {
          stiffness(c,i,j) = (stiffness(c,i,j) + stiffness(c,j,i)) / 2.0;
          stiffness(c,j,i) = stiffness(c,i,j);
        }
  }
}