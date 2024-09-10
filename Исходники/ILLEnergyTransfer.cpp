  void ILLEnergyTransfer::run()
  {
    QMap<QString, QString> instDetails = getInstrumentDetails();

    IAlgorithm_sptr reductionAlg = AlgorithmManager::Instance().create("IndirectILLReduction");
    reductionAlg->initialize();

    reductionAlg->setProperty("Analyser", instDetails["analyser"].toStdString());
    reductionAlg->setProperty("Reflection", instDetails["reflection"].toStdString());

    // Handle input files
    QString runFilename = m_uiForm.rfInput->getFirstFilename();
    reductionAlg->setProperty("Run", runFilename.toStdString());

    // Handle calibration
    bool useCalibration = m_uiForm.ckUseCalibration->isChecked();
    if(useCalibration)
    {
      QString calibrationWsName = m_uiForm.dsCalibration->getCurrentDataName();
      reductionAlg->setProperty("CalibrationWorkspace", calibrationWsName.toStdString());
    }

    // Handle mapping file
    bool useMapFile = m_uiForm.cbGroupingType->currentText() == "File";
    if(useMapFile)
    {
      QString mapFilename = m_uiForm.rfMapFile->getFirstFilename();
      reductionAlg->setProperty("MapFile", mapFilename.toStdString());
    }

    // Set mirror mode option
    bool mirrorMode = m_uiForm.ckMirrorMode->isChecked();
    reductionAlg->setProperty("MirrorMode", mirrorMode);

    // Get the name format for output files
    QFileInfo runFileInfo(runFilename);
    QString outputFilenameBase = runFileInfo.baseName() +
                                 "_" + instDetails["analyser"] +
                                 "_" + instDetails["reflection"];
    std::string outputFilenameBaseStd = outputFilenameBase.toStdString();

    // Set left and right workspaces when using mirror mode
    if(mirrorMode)
    {
      reductionAlg->setProperty("LeftWorkspace", outputFilenameBaseStd + "_left");
      reductionAlg->setProperty("RightWorkspace", outputFilenameBaseStd + "_right");
    }

    // Set output workspace properties
    reductionAlg->setProperty("RawWorkspace", outputFilenameBaseStd + "_raw");
    reductionAlg->setProperty("ReducedWorkspace", outputFilenameBaseStd + "_red");

    // Set output options
    reductionAlg->setProperty("Plot", m_uiForm.ckPlot->isChecked());
    reductionAlg->setProperty("Save", m_uiForm.ckSave->isChecked());

    m_batchAlgoRunner->addAlgorithm(reductionAlg);
    m_batchAlgoRunner->executeBatchAsync();
  }