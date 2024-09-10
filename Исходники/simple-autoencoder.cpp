  /** Constructs a nueral network with a given number of layers and a
      given number of neurons for each particular layer */
  NeuralNetwork(int numLayers, int * unitCounts) {
    // initialize the activations and biases
    for (int layer=0; layer < numLayers; layer++) {
      //MatrixXd layerActivations = MatrixXd(unitCounts[layer], 1);
      //layerActivations.setZero();
      _activations.push_back(MatrixXd(unitCounts[layer], 1));//layerActivations);
      _activationFnInputs.push_back(MatrixXd(unitCounts[layer], 1));
      _activationAverages.push_back(MatrixXd(unitCounts[layer], 1).setZero());

    }
    // initialize the weights/biases
    for (int i=1; i < numLayers; i++) {
      // biases -> 0
      MatrixXd layerBias = MatrixXd(unitCounts[i], 1);
      layerBias.setZero();
      _biases.push_back(layerBias);

      // weights -> 1 / (sqrt(fanout)) where fanout = incoming degree of node
      int rows = unitCounts[i];
      int cols = unitCounts[i - 1];
      
      MatrixXd layerWeightMatrix = MatrixXd(rows, cols);

      for (int row=0; row < rows; row++) {
	double fanout = static_cast<double>(unitCounts[i - 1]);
	for (int col=0; col < cols; col++) {
	  layerWeightMatrix(row, col) = randDouble(1.0 / (sqrt(fanout) + .0000000001));
	}
      }
      
      _W.push_back(layerWeightMatrix);
    }
  }