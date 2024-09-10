/**
  * Gaussian fit to determine peak position if no user position given.
  *
  * @return :: detector position of the peak: Gaussian fit and position
  * of the maximum (serves as start value for the optimization)
  */
double LoadILLReflectometry::reflectometryPeak() {
  if (!isDefault("BeamCentre")) {
    return getProperty("BeamCentre");
  }
  size_t startIndex;
  size_t endIndex;
  std::tie(startIndex, endIndex) =
      fitIntegrationWSIndexRange(*m_localWorkspace);
  IAlgorithm_sptr integration = createChildAlgorithm("Integration");
  integration->initialize();
  integration->setProperty("InputWorkspace", m_localWorkspace);
  integration->setProperty("OutputWorkspace", "__unused_for_child");
  integration->setProperty("StartWorkspaceIndex", static_cast<int>(startIndex));
  integration->setProperty("EndWorkspaceIndex", static_cast<int>(endIndex));
  integration->execute();
  MatrixWorkspace_sptr integralWS = integration->getProperty("OutputWorkspace");
  IAlgorithm_sptr transpose = createChildAlgorithm("Transpose");
  transpose->initialize();
  transpose->setProperty("InputWorkspace", integralWS);
  transpose->setProperty("OutputWorkspace", "__unused_for_child");
  transpose->execute();
  integralWS = transpose->getProperty("OutputWorkspace");
  rebinIntegralWorkspace(*integralWS);
  // determine initial height: maximum value
  const auto maxValueIt =
      std::max_element(integralWS->y(0).cbegin(), integralWS->y(0).cend());
  const double height = *maxValueIt;
  // determine initial centre: index of the maximum value
  const size_t maxIndex = std::distance(integralWS->y(0).cbegin(), maxValueIt);
  const double centreByMax = static_cast<double>(maxIndex);
  g_log.debug() << "Peak maximum position: " << centreByMax << '\n';
  // determine sigma
  const auto &ys = integralWS->y(0);
  auto lessThanHalfMax = [height](const double x) { return x < 0.5 * height; };
  using IterType = HistogramData::HistogramY::const_iterator;
  std::reverse_iterator<IterType> revMaxValueIt{maxValueIt};
  auto revMinFwhmIt = std::find_if(revMaxValueIt, ys.crend(), lessThanHalfMax);
  auto maxFwhmIt = std::find_if(maxValueIt, ys.cend(), lessThanHalfMax);
  std::reverse_iterator<IterType> revMaxFwhmIt{maxFwhmIt};
  if (revMinFwhmIt == ys.crend() || maxFwhmIt == ys.cend()) {
    g_log.warning() << "Couldn't determine fwhm of beam, using position of max "
                       "value as beam center.\n";
    return centreByMax;
  }
  const double fwhm =
      static_cast<double>(std::distance(revMaxFwhmIt, revMinFwhmIt) + 1);
  g_log.debug() << "Initial fwhm (full width at half maximum): " << fwhm
                << '\n';
  // generate Gaussian
  auto func =
      API::FunctionFactory::Instance().createFunction("CompositeFunction");
  auto sum = boost::dynamic_pointer_cast<API::CompositeFunction>(func);
  func = API::FunctionFactory::Instance().createFunction("Gaussian");
  auto gaussian = boost::dynamic_pointer_cast<API::IPeakFunction>(func);
  gaussian->setHeight(height);
  gaussian->setCentre(centreByMax);
  gaussian->setFwhm(fwhm);
  sum->addFunction(gaussian);
  func = API::FunctionFactory::Instance().createFunction("LinearBackground");
  func->setParameter("A0", 0.);
  func->setParameter("A1", 0.);
  sum->addFunction(func);
  // call Fit child algorithm
  API::IAlgorithm_sptr fit = createChildAlgorithm("Fit");
  fit->initialize();
  fit->setProperty("Function",
                   boost::dynamic_pointer_cast<API::IFunction>(sum));
  fit->setProperty("InputWorkspace", integralWS);
  fit->setProperty("StartX", centreByMax - 3 * fwhm);
  fit->setProperty("EndX", centreByMax + 3 * fwhm);
  fit->execute();
  const std::string fitStatus = fit->getProperty("OutputStatus");
  if (fitStatus != "success") {
    g_log.warning("Fit not successful, using position of max value.\n");
    return centreByMax;
  }
  const auto centre = gaussian->centre();
  g_log.debug() << "Sigma: " << gaussian->fwhm() << '\n';
  g_log.debug() << "Estimated peak position: " << centre << '\n';
  return centre;
}