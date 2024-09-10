    /**
     * Updates the analyser and reflection names in the UI when an instrument is selected.
     *
     * @param instrumentName Nmae of instrument
     */
    void IndirectInstrumentConfig::updateInstrumentConfigurations(const QString & instrumentName)
    {
      if(instrumentName.isEmpty())
        return;

      g_log.debug() << "Loading configuration for instrument: " << instrumentName.toStdString() << std::endl;

      bool analyserPreviousBlocking = m_uiForm.cbAnalyser->signalsBlocked();
      m_uiForm.cbAnalyser->blockSignals(true);

      m_uiForm.cbAnalyser->clear();

      IAlgorithm_sptr loadInstAlg = AlgorithmManager::Instance().create("CreateSimulationWorkspace");
      loadInstAlg->initialize();
      loadInstAlg->setChild(true);
      loadInstAlg->setProperty("Instrument", instrumentName.toStdString());
      loadInstAlg->setProperty("BinParams", "0,0.5,1");
      loadInstAlg->setProperty("OutputWorkspace", "__empty_instrument_workspace");
      loadInstAlg->execute();
      MatrixWorkspace_sptr instWorkspace = loadInstAlg->getProperty("OutputWorkspace");

      QList<QPair<QString, QString>> instrumentModes;
      Instrument_const_sptr instrument = instWorkspace->getInstrument();

      std::vector<std::string> ipfAnalysers = instrument->getStringParameter("analysers");
      if(ipfAnalysers.size() == 0)
        return;

      QStringList analysers = QString::fromStdString(ipfAnalysers[0]).split(",");

      for(auto it = analysers.begin(); it != analysers.end(); ++it)
      {
        QString analyser = *it;
        std::string ipfReflections = instrument->getStringParameter("refl-" + analyser.toStdString())[0];
        QStringList reflections = QString::fromStdString(ipfReflections).split(",");

        if(m_removeDiffraction && analyser == "diffraction")
          continue;

        if(m_forceDiffraction && analyser != "diffraction")
          continue;

        if(reflections.size() > 0)
        {
          QVariant data = QVariant(reflections);
          m_uiForm.cbAnalyser->addItem(analyser, data);
        }
        else
        {
          m_uiForm.cbAnalyser->addItem(analyser);
        }
      }

      int index = m_uiForm.cbAnalyser->currentIndex();
      updateReflectionsList(index);

      m_uiForm.cbAnalyser->blockSignals(analyserPreviousBlocking);
    }