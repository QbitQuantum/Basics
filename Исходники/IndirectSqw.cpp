  /**
   * Handles the Plot Input button
   *
   * Creates a colour 2D plot of the data
   */
  void IndirectSqw::plotContour()
  {
    if(m_uiForm.dsSampleInput->isValid())
    {
      QString sampleWsName = m_uiForm.dsSampleInput->getCurrentDataName();

      QString convertedWsName = sampleWsName.left(sampleWsName.length() - 4) + "_rqw";

      IAlgorithm_sptr convertSpecAlg = AlgorithmManager::Instance().create("ConvertSpectrumAxis");
      convertSpecAlg->initialize();

      convertSpecAlg->setProperty("InputWorkspace", sampleWsName.toStdString());
      convertSpecAlg->setProperty("OutputWorkspace", convertedWsName.toStdString());
      convertSpecAlg->setProperty("Target", "ElasticQ");
      convertSpecAlg->setProperty("EMode", "Indirect");

      convertSpecAlg->execute();

      QString pyInput = "plot2D('" + convertedWsName + "')\n";
      m_pythonRunner.runPythonCode(pyInput);
    }
    else
    {
      emit showMessageBox("Invalid filename.");
    }
  }