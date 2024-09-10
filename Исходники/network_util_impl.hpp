typename std::enable_if<
    HasWeightsCheck<T, arma::mat&(T::*)()>::value, size_t>::type
LayerWeights(InitializationRuleType& initializeRule,
             T& layer,
             arma::mat& weights,
             size_t offset,
             arma::mat& /* output */)
{
  layer.Weights() = arma::mat(weights.memptr() + offset,
      layer.Weights().n_rows, layer.Weights().n_cols, false, false);

  initializeRule.Initialize(layer.Weights(), layer.Weights().n_rows,
      layer.Weights().n_cols);

  return layer.Weights().n_elem;
}