MatrixWorkspace_sptr CalculateIqt::rebin(MatrixWorkspace_sptr workspace,
                                         const std::string &params) {
  IAlgorithm_sptr rebinAlgorithm = this->createChildAlgorithm("Rebin");
  rebinAlgorithm->initialize();
  rebinAlgorithm->setProperty("InputWorkspace", workspace);
  rebinAlgorithm->setProperty("OutputWorkspace", "_");
  rebinAlgorithm->setProperty("Params", params);
  rebinAlgorithm->execute();
  return rebinAlgorithm->getProperty("OutputWorkspace");
}