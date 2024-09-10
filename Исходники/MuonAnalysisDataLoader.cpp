/**
 * Correct loaded data for dead times (if present) and group
 * @param loadedData :: [input] Load result
 * @param grouping :: [input] Grouping to use
 * @returns :: Workspace containing processed data
 */
Workspace_sptr MuonAnalysisDataLoader::correctAndGroup(
    const Muon::LoadResult &loadedData,
    const Mantid::API::Grouping &grouping) const {
  ITableWorkspace_sptr deadTimes;
  try { // to get the dead time correction
    deadTimes = getDeadTimesTable(loadedData);
  } catch (const std::exception &e) {
    // If dead correction wasn't applied we can still continue, though should
    // make user aware of that
    g_log.warning() << "No dead time correction applied: " << e.what() << "\n";
  }

  // Now apply DTC, if used, and grouping
  Workspace_sptr correctedGroupedWS;
  IAlgorithm_sptr alg =
      AlgorithmManager::Instance().createUnmanaged("MuonProcess");
  alg->initialize();
  alg->setProperty("InputWorkspace", loadedData.loadedWorkspace);
  alg->setProperty("Mode", "CorrectAndGroup");
  if (deadTimes) {
    alg->setProperty("ApplyDeadTimeCorrection", true);
    alg->setProperty("DeadTimeTable", deadTimes);
  }
  alg->setProperty("LoadedTimeZero", loadedData.timeZero);
  alg->setProperty("DetectorGroupingTable", grouping.toTable());
  alg->setChild(true);
  alg->setPropertyValue("OutputWorkspace", "__NotUsed");
  alg->execute();
  correctedGroupedWS = alg->getProperty("OutputWorkspace");
  return correctedGroupedWS;
}