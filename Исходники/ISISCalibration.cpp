  /**
   * Replots the energy mini plot
   */
  void ISISCalibration::calPlotEnergy()
  {
    if ( ! m_uiForm.leRunNo->isValid() )
    {
      emit showMessageBox("Run number not valid.");
      return;
    }

    QString files = m_uiForm.leRunNo->getFilenames().join(",");

    QFileInfo fi(m_uiForm.leRunNo->getFirstFilename());

    QString detRange = QString::number(m_dblManager->value(m_properties["ResSpecMin"])) + ","
                     + QString::number(m_dblManager->value(m_properties["ResSpecMax"]));

    IAlgorithm_sptr reductionAlg = AlgorithmManager::Instance().create("ISISIndirectEnergyTransfer");
    reductionAlg->initialize();
    reductionAlg->setProperty("Instrument", getInstrumentConfiguration()->getInstrumentName().toStdString());
    reductionAlg->setProperty("Analyser", getInstrumentConfiguration()->getAnalyserName().toStdString());
    reductionAlg->setProperty("Reflection", getInstrumentConfiguration()->getReflectionName().toStdString());
    reductionAlg->setProperty("InputFiles", files.toStdString());
    reductionAlg->setProperty("OutputWorkspace", "__IndirectCalibration_reduction");
    reductionAlg->setProperty("SpectraRange", detRange.toStdString());
    reductionAlg->execute();

    if(!reductionAlg->isExecuted())
    {
      g_log.warning("Could not generate energy preview plot.");
      return;
    }

    WorkspaceGroup_sptr reductionOutputGroup = AnalysisDataService::Instance().retrieveWS<WorkspaceGroup>("__IndirectCalibration_reduction");
    if(reductionOutputGroup->size() == 0)
    {
      g_log.warning("No result workspaces, cannot plot energy preview.");
      return;
	}

    MatrixWorkspace_sptr energyWs = boost::dynamic_pointer_cast<MatrixWorkspace>(reductionOutputGroup->getItem(0));
    if(!energyWs)
    {
      g_log.warning("No result workspaces, cannot plot energy preview.");
      return;
    }

    const Mantid::MantidVec & dataX = energyWs->readX(0);
    QPair<double, double> range(dataX.front(), dataX.back());

    auto resBackground = m_uiForm.ppResolution->getRangeSelector("ResBackground");
    setPlotPropertyRange(resBackground, m_properties["ResStart"], m_properties["ResEnd"], range);

    m_uiForm.ppResolution->clear();
    m_uiForm.ppResolution->addSpectrum("Energy", energyWs, 0);
    m_uiForm.ppResolution->resizeX();

    calSetDefaultResolution(energyWs);

    m_uiForm.ppResolution->replot();
  }