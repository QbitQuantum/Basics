/**
 * Fit peak without background i.e, with background removed
 *  inspired from FitPowderDiffPeaks.cpp
 *  copied from PoldiPeakDetection2.cpp
 *
 @param workspaceindex :: indice of the row to use
 @param center :: gaussian parameter - center
 @param sigma :: gaussian parameter - width
 @param height :: gaussian parameter - height
 @param startX :: fit range - start X value
 @param endX :: fit range - end X value
 @returns A boolean status flag, true for fit success, false else
 */
bool ConvertEmptyToTof::doFitGaussianPeak(int workspaceindex, double &center,
                                          double &sigma, double &height,
                                          double startX, double endX) {

  g_log.debug("Calling doFitGaussianPeak...");

  // 1. Estimate
  sigma = sigma * 0.5;

  // 2. Use factory to generate Gaussian
  auto temppeak = API::FunctionFactory::Instance().createFunction("Gaussian");
  auto gaussianpeak = boost::dynamic_pointer_cast<API::IPeakFunction>(temppeak);
  gaussianpeak->setHeight(height);
  gaussianpeak->setCentre(center);
  gaussianpeak->setFwhm(sigma);

  // 3. Constraint
  double centerleftend = center - sigma * 0.5;
  double centerrightend = center + sigma * 0.5;
  std::ostringstream os;
  os << centerleftend << " < PeakCentre < " << centerrightend;
  auto *centerbound = API::ConstraintFactory::Instance().createInitialized(
      gaussianpeak.get(), os.str(), false);
  gaussianpeak->addConstraint(centerbound);

  g_log.debug("Calling createChildAlgorithm : Fit...");
  // 4. Fit
  API::IAlgorithm_sptr fitalg = createChildAlgorithm("Fit", -1, -1, true);
  fitalg->initialize();

  fitalg->setProperty(
      "Function", boost::dynamic_pointer_cast<API::IFunction>(gaussianpeak));
  fitalg->setProperty("InputWorkspace", m_inputWS);
  fitalg->setProperty("WorkspaceIndex", workspaceindex);
  fitalg->setProperty("Minimizer", "Levenberg-MarquardtMD");
  fitalg->setProperty("CostFunction", "Least squares");
  fitalg->setProperty("MaxIterations", 1000);
  fitalg->setProperty("Output", "FitGaussianPeak");
  fitalg->setProperty("StartX", startX);
  fitalg->setProperty("EndX", endX);

  // 5.  Result
  bool successfulfit = fitalg->execute();
  if (!fitalg->isExecuted() || !successfulfit) {
    // Early return due to bad fit
    g_log.warning() << "Fitting Gaussian peak for peak around "
                    << gaussianpeak->centre() << '\n';
    return false;
  }

  // 6. Get result
  center = gaussianpeak->centre();
  height = gaussianpeak->height();
  double fwhm = gaussianpeak->fwhm();

  return fwhm > 0.0;
}