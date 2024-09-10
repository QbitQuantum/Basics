inline void ParametersVisitor::operator()(LayerType *layer) const
{
  LayerParameters(layer, layer->OutputParameter());
}