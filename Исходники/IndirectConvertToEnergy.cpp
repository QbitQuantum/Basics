  /**
   * This function creates the mapping/grouping file for the data analysis.
   * @param groupType :: Type of grouping (All, Group, Indiviual)
   * @return path to mapping file, or an empty string if file could not be created.
   */
  QString IndirectConvertToEnergy::createMapFile(const QString& groupType)
  {
    QString specRange = m_uiForm.spSpectraMin->text() + "," + m_uiForm.spSpectraMax->text();

    if(groupType == "File")
    {
      QString groupFile = m_uiForm.dsMapFile->getFirstFilename();
      if(groupFile == "")
      {
        emit showMessageBox("You must enter a path to the .map file.");
      }
      return groupFile;
    }
    else if(groupType == "Groups")
    {
      QString groupWS = "__Grouping";

      IAlgorithm_sptr groupingAlg = AlgorithmManager::Instance().create("CreateGroupingWorkspace");
      groupingAlg->initialize();

      groupingAlg->setProperty("FixedGroupCount", m_uiForm.spNumberGroups->value());
      groupingAlg->setProperty("InstrumentName", getInstrumentConfiguration()->getInstrumentName().toStdString());
      groupingAlg->setProperty("ComponentName", getInstrumentConfiguration()->getAnalyserName().toStdString());
      groupingAlg->setProperty("OutputWorkspace", groupWS.toStdString());

      m_batchAlgoRunner->addAlgorithm(groupingAlg);

      return groupWS;
    }
    else
    {
      // Catch All and Individual
      return groupType;
    }
  }