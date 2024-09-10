unsigned int CLTreeTrainer<ImgType, nChannels, FeatType, FeatDim, nClasses>::_initHistogram(
  const TreeTrainerParameters<FeatType, FeatDim> &params)
{
  unsigned int frontierSize = m_frontierIdxMap.size();

  size_t perNodeHistogramSize = params.nFeatures*params.nThresholds*nClasses;
  unsigned int nSlices = ceill((double)frontierSize/m_histogramSize);

  return nSlices;
}