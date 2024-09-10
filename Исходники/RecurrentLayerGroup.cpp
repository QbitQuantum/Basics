void RecurrentLayerGroup::initSubNetwork(
    NeuralNetwork* rootNetwork,
    const ModelConfig& config,
    const std::vector<ParameterType>& parameterTypes,
    bool useGpu) {
  setNeedGradient(true);

  network_.reset(new RecurrentGradientMachine(config_.name(), rootNetwork));
  ParamInitCallback cb = [this, rootNetwork](int paramId, Parameter* para) {
    para->enableSharedType(
        PARAMETER_VALUE,
        rootNetwork->getParameters()[paramId]->getBuf(PARAMETER_VALUE),
        rootNetwork->getParameters()[paramId]->getMat(PARAMETER_VALUE));
    para->enableSharedType(
        PARAMETER_GRADIENT,
        rootNetwork->getParameters()[paramId]->getBuf(PARAMETER_GRADIENT),
        rootNetwork->getParameters()[paramId]->getMat(PARAMETER_GRADIENT));
  };
  network_->init(config, cb, parameterTypes, useGpu);

  for (auto paramId : network_->getParameterIds()) {
    ParameterPtr parameter = rootNetwork->getParameters()[paramId];
    parameter->incShared();
    CHECK_EQ(parameter->getDeviceId(), getDeviceId());
    parameters_.push_back(parameter);
  }
}