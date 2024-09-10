void SequenceConcatLayer::forward(PassType passType) {
  Layer::forward(passType);

  size_t dim = getSize();

  const Argument& input1 = getInput(0);
  size_t numSequences1 = input1.getNumSequences();
  auto startPositions1 = input1.sequenceStartPositions->getVector(false);

  const Argument& input2 = getInput(1);
  size_t numSequences2 = input2.getNumSequences();
  auto startPositions2 = input2.sequenceStartPositions->getVector(false);

  CHECK_EQ(dim, input1.value->getWidth());
  CHECK_EQ(startPositions1->getData()[numSequences1], input1.getBatchSize());
  CHECK_EQ(numSequences1, startPositions1->getSize() - 1);

  CHECK_EQ(dim, input2.value->getWidth());
  CHECK_EQ(startPositions2->getData()[numSequences2], input2.getBatchSize());
  CHECK_EQ(numSequences2, startPositions2->getSize() - 1);

  CHECK_EQ(numSequences1, numSequences2);

  MatrixPtr inputValue1 = getInputValue(0);
  MatrixPtr inputValue2 = getInputValue(1);

  // reset output
  reserveOutput(inputValue1->getHeight() + inputValue2->getHeight(), dim);

  MatrixPtr outputValue = getOutputValue();

  const int* starts1 = startPositions1->getData();
  const int* starts2 = startPositions2->getData();

  {
    AsyncGpuBlock asyncGpuBlock;
    REGISTER_TIMER_INFO("SequenceConcatLayerForward", getName().c_str());

    size_t offset = 0;
    size_t leftNumIns = 0;
    size_t rightNumIns = 0;
    for (size_t seqId = 0; seqId < numSequences1; ++seqId) {
      leftNumIns = starts1[seqId + 1] - starts1[seqId];
      outputValue->subMatrix(offset, leftNumIns)
          ->assign(*(inputValue1->subMatrix(starts1[seqId], leftNumIns)));
      offset += leftNumIns;

      rightNumIns = starts2[seqId + 1] - starts2[seqId];
      outputValue->subMatrix(offset, rightNumIns)
          ->assign(*(inputValue2->subMatrix(starts2[seqId], rightNumIns)));
      offset += rightNumIns;
    }

    // modify the sequenceStartPositions
    ICpuGpuVector::resizeOrCreate(
        output_.sequenceStartPositions, numSequences1 + 1, false);

    int* tgtBuf = output_.sequenceStartPositions->getMutableData(false);

    for (size_t seqId = 0; seqId < numSequences1 + 1; ++seqId) {
      tgtBuf[seqId] = starts1[seqId] + starts2[seqId];
    }
  }

  if (biases_.get() != NULL) {
    MatrixPtr outV = getOutputValue();
    outV->addBias(*(biases_->getW()), 1);
  }

  /* activation */
  forwardActivation();
}