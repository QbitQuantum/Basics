/** Process WorkspaceGroup inputs.
 *
 * Overriden from Algorithm base class.
 *
 * This should be called after checkGroups(), which sets up required members.
 * It goes through each member of the group(s), creates and sets an algorithm
 * for each and executes them one by one.
 *
 * If there are several group input workspaces, then the member of each group
 * is executed pair-wise.
 *
 * @param sourceAlg : Source algorithm
 * @param vecMultiPeriodGroups : Vector of pre-identified multiperiod groups.
 * @return true - if all the workspace members are executed.
 */
bool MultiPeriodGroupWorker::processGroups(
    Algorithm *const sourceAlg,
    const VecWSGroupType &vecMultiPeriodGroups) const {
  // If we are not processing multiperiod groups, use the base behaviour.
  if (vecMultiPeriodGroups.empty()) {
    return false; // Indicates that this is not a multiperiod group workspace.
  }
  Property *outputWorkspaceProperty = sourceAlg->getProperty("OutputWorkspace");
  const std::string outName = outputWorkspaceProperty->value();

  const size_t nPeriods = vecMultiPeriodGroups[0]->size();
  WorkspaceGroup_sptr outputWS = boost::make_shared<WorkspaceGroup>();
  AnalysisDataService::Instance().addOrReplace(outName, outputWS);

  double progress_proportion = 1.0 / static_cast<double>(nPeriods);
  // Loop through all the periods. Create spawned algorithms of the same type as
  // this to process pairs from the input groups.
  for (size_t i = 0; i < nPeriods; ++i) {
    const int periodNumber = static_cast<int>(i + 1);
    // use create Child Algorithm that look like this one
    Algorithm_sptr alg = sourceAlg->createChildAlgorithm(
        sourceAlg->name(), progress_proportion * periodNumber,
        progress_proportion * (1 + periodNumber), sourceAlg->isLogging(),
        sourceAlg->version());
    if (!alg) {
      throw std::runtime_error("Algorithm creation failed.");
    }
    // Don't make the new algorithm a child so that it's workspaces are stored
    // correctly
    alg->setChild(false);
    alg->setRethrows(true);
    alg->initialize();
    // Copy properties that aren't workspaces properties.
    sourceAlg->copyNonWorkspaceProperties(alg.get(), periodNumber);

    if (this->useCustomWorkspaceProperty()) {
      const std::string inputWorkspaces =
          createFormattedInputWorkspaceNames(i, vecMultiPeriodGroups);
      // Set the input workspace property.
      alg->setPropertyValue(this->m_workspacePropertyName, inputWorkspaces);
    } else {
      // Configure input properties that are group workspaces.
      copyInputWorkspaceProperties(alg.get(), sourceAlg, periodNumber);
    }
    const std::string outName_i = outName + "_" + Strings::toString(i + 1);
    alg->setPropertyValue("OutputWorkspace", outName_i);
    // Run the spawned algorithm.
    if (!alg->execute()) {
      throw std::runtime_error("Execution of " + sourceAlg->name() +
                               " for group entry " + Strings::toString(i + 1) +
                               " failed.");
    }
    // Add the output workpace from the spawned algorithm to the group.
    outputWS->add(outName_i);
  }

  sourceAlg->setProperty("OutputWorkspace", outputWS);

  return true;
}