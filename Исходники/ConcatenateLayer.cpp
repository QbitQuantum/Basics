void ConcatenateLayer2::forward(PassType passType) {
  Layer::forward(passType);

  int batchSize = getInput(0).getBatchSize();
  int size = getSize();
  resetOutput(batchSize, size);

  for (size_t i = 0; i < projections_.size(); i++) {
    size_t startCol = projCol_[i].first;
    size_t endCol = projCol_[i].second;
    projOutput_[i].value = output_.value->subColMatrix(startCol, endCol);
    if (output_.grad) {
      projOutput_[i].grad = output_.grad->subColMatrix(startCol, endCol);
    }
  }

  {
    AsyncGpuBlock block;
    for (size_t i = 0; i != inputLayers_.size(); ++i) {
      projections_[i]->forward(&getInput(i), &projOutput_[i], passType);
    }
  }

  /* add the bias-vector */
  if (biases_) {
    REGISTER_TIMER_INFO("FwBiasTimer", getName().c_str());
    output_.value->addBias(*(biases_->getW()), 1, sharedBias_);
  }

  /* activation */ {
    REGISTER_TIMER_INFO("FwAtvTimer", getName().c_str());
    forwardActivation();
  }
}