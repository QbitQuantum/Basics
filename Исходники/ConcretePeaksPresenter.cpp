void ConcretePeaksPresenter::sortPeaksWorkspace(const std::string &byColumnName,
                                                const bool ascending) {
  Mantid::API::IPeaksWorkspace_sptr peaksWS =
      boost::const_pointer_cast<Mantid::API::IPeaksWorkspace>(this->m_peaksWS);

  // Sort the Peaks in-place.
  Mantid::API::IAlgorithm_sptr alg =
      AlgorithmManager::Instance().create("SortPeaksWorkspace");
  alg->setChild(true);
  alg->setRethrows(true);
  alg->initialize();
  alg->setProperty("InputWorkspace", peaksWS);
  alg->setPropertyValue("OutputWorkspace", "SortedPeaksWorkspace");
  alg->setProperty("OutputWorkspace", peaksWS);
  alg->setProperty("SortAscending", ascending);
  alg->setPropertyValue("ColumnNameToSortBy", byColumnName);
  alg->execute();

  // Reproduce the views.
  this->produceViews();

  // Give the new views the current slice point.
  m_viewPeaks->setSlicePoint(this->m_slicePoint.slicePoint(), m_viewablePeaks);
}