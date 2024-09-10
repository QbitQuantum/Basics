/**
* Handles completion of the unit conversion and saving algorithm.
*
* @param error True if algorithm failed.
*/
void ApplyPaalmanPings::postProcessComplete(bool error) {
  disconnect(m_batchAlgoRunner, SIGNAL(batchComplete(bool)), this,
             SLOT(postProcessComplete(bool)));

  if (error) {
    emit showMessageBox("Unable to process corrected workspace.\nSee Results "
                        "Log for more details.");
    return;
  }

  // Handle preview plot
  plotPreview(m_uiForm.spPreviewSpec->value());

  // Handle Mantid plotting
  QString plotType = m_uiForm.cbPlotOutput->currentText();

  if (plotType == "Spectra" || plotType == "Both")
    plotSpectrum(QString::fromStdString(m_pythonExportWsName));

  if (plotType == "Contour" || plotType == "Both")
    plot2D(QString::fromStdString(m_pythonExportWsName));

  // Clean up unwanted workspaces
  IAlgorithm_sptr deleteAlg =
      AlgorithmManager::Instance().create("DeleteWorkspace");
  deleteAlg->initialize();
  deleteAlg->setProperty("Workspace", "__algorithm_can");
  deleteAlg->execute();
  const auto conv =
      AnalysisDataService::Instance().doesExist("__algorithm_can_Wavelength");
  if (conv) {
    deleteAlg->setProperty("Workspace", "__algorithm_can_Wavelength");
    deleteAlg->execute();
  }
}