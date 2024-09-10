/** Rebins the distributions and sets error values.
 */
MatrixWorkspace_sptr
VesuvioL1ThetaResolution::processDistribution(MatrixWorkspace_sptr ws,
                                              const double binWidth) {
  const size_t numHist = ws->getNumberHistograms();

  double xMin(DBL_MAX);
  double xMax(DBL_MIN);
  for (size_t i = 0; i < numHist; i++) {
    auto &x = ws->x(i);
    xMin = std::min(xMin, x.front());
    xMax = std::max(xMax, x.back());
  }

  std::stringstream binParams;
  binParams << xMin << "," << binWidth << "," << xMax;

  IAlgorithm_sptr rebin = AlgorithmManager::Instance().create("Rebin");
  rebin->initialize();
  rebin->setChild(true);
  rebin->setLogging(false);
  rebin->setProperty("InputWorkspace", ws);
  rebin->setProperty("OutputWorkspace", "__rebin");
  rebin->setProperty("Params", binParams.str());
  rebin->execute();
  ws = rebin->getProperty("OutputWorkspace");

  for (size_t i = 0; i < numHist; i++) {
    auto &y = ws->y(i);
    auto &e = ws->mutableE(i);
    std::transform(y.begin(), y.end(), e.begin(),
                   [](double x) { return sqrt(x); });
  }

  return ws;
}