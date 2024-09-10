/**
 * Sorts the peak workspace by a specified column name in ascending or
 * descending order.
 * @param byColumnName The column by which the workspace is to be sorted.
 * @param ascending If the workspace is to be sorted in a ascending or
 * descending manner.
 */
void ConcretePeaksPresenterVsi::sortPeaksWorkspace(
    const std::string &byColumnName, const bool ascending) {
  Mantid::API::IPeaksWorkspace_sptr peaksWS =
      boost::const_pointer_cast<Mantid::API::IPeaksWorkspace>(
          this->m_peaksWorkspace);

  // Sort the Peaks in-place.
  Mantid::API::IAlgorithm_sptr alg =
      Mantid::API::AlgorithmManager::Instance().create("SortPeaksWorkspace");
  alg->setChild(true);
  alg->setRethrows(true);
  alg->initialize();
  alg->setProperty("InputWorkspace", peaksWS);
  alg->setPropertyValue("OutputWorkspace", "SortedPeaksWorkspace");
  alg->setProperty("OutputWorkspace", peaksWS);
  alg->setProperty("SortAscending", ascending);
  alg->setPropertyValue("ColumnNameToSortBy", byColumnName);
  alg->execute();
}