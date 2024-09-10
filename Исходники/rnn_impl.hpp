RNN<LayerTypes, OutputLayerType, InitializationRuleType, PerformanceFunction
>::RNN(LayerType &&network,
       OutputType &&outputLayer,
       const arma::mat& predictors,
       const arma::mat& responses,
       InitializationRuleType initializeRule,
       PerformanceFunction performanceFunction) :
    network(std::forward<LayerType>(network)),
    outputLayer(std::forward<OutputType>(outputLayer)),
    performanceFunc(std::move(performanceFunction)),
    inputSize(0),
    outputSize(0)
{
  static_assert(std::is_same<typename std::decay<LayerType>::type,
                  LayerTypes>::value,
                  "The type of network must be LayerTypes.");

  static_assert(std::is_same<typename std::decay<OutputType>::type,
                OutputLayerType>::value,
                "The type of outputLayer must be OutputLayerType.");

  initializeRule.Initialize(parameter, NetworkSize(this->network), 1);
  NetworkWeights(parameter, this->network);

  Train(predictors, responses);
}