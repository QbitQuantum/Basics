/**
 * Handles a request to preview the symmetrise.
 *
 * Runs Symmetrise on the current spectrum and plots in preview mini plot.
 *
 * @see IndirectSymmetrise::previewAlgDone()
 */
void IndirectSymmetrise::preview() {
  // Handle algorithm completion signal
  connect(m_batchAlgoRunner, SIGNAL(batchComplete(bool)), this,
          SLOT(previewAlgDone(bool)));

  // Do nothing if no data has been laoded
  QString workspaceName = m_uiForm.dsInput->getCurrentDataName();
  if (workspaceName.isEmpty())
    return;

  double e_min = m_dblManager->value(m_properties["EMin"]);
  double e_max = m_dblManager->value(m_properties["EMax"]);
  long spectrumNumber =
      static_cast<long>(m_dblManager->value(m_properties["PreviewSpec"]));
  std::vector<long> spectraRange(2, spectrumNumber);

  // Run the algorithm on the preview spectrum only
  IAlgorithm_sptr symmetriseAlg =
      AlgorithmManager::Instance().create("Symmetrise", -1);
  symmetriseAlg->initialize();
  symmetriseAlg->setProperty("InputWorkspace", workspaceName.toStdString());
  symmetriseAlg->setProperty("XMin", e_min);
  symmetriseAlg->setProperty("XMax", e_max);
  symmetriseAlg->setProperty("SpectraRange", spectraRange);
  symmetriseAlg->setProperty("OutputWorkspace", "__Symmetrise_temp");
  symmetriseAlg->setProperty("OutputPropertiesTable", "__SymmetriseProps_temp");

  runAlgorithm(symmetriseAlg);
}