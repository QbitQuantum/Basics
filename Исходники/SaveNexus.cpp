void SaveNexus::runSaveNexusProcessed() {
  IAlgorithm_sptr saveNexusPro =
      createChildAlgorithm("SaveNexusProcessed", 0.0, 1.0, true);
  // Pass through the same output filename
  saveNexusPro->setPropertyValue("Filename", m_filename);
  // Set the workspace property
  std::string inputWorkspace = "InputWorkspace";
  saveNexusPro->setProperty(inputWorkspace, m_inputWorkspace);
  //
  std::vector<int> specList = getProperty("WorkspaceIndexList");
  if (!specList.empty())
    saveNexusPro->setPropertyValue("WorkspaceIndexList",
                                   getPropertyValue("WorkspaceIndexList"));
  //
  int specMax = getProperty("WorkspaceIndexMax");
  if (specMax != Mantid::EMPTY_INT()) {
    saveNexusPro->setPropertyValue("WorkspaceIndexMax",
                                   getPropertyValue("WorkspaceIndexMax"));
    saveNexusPro->setPropertyValue("WorkspaceIndexMin",
                                   getPropertyValue("WorkspaceIndexMin"));
  }
  std::string title = getProperty("Title");
  if (!title.empty())
    saveNexusPro->setPropertyValue("Title", getPropertyValue("Title"));

  // Pass through the append property
  saveNexusPro->setProperty<bool>("Append", getProperty("Append"));

  // If we're tracking history, add the entry before we save it to file
  if (trackingHistory()) {
    m_history->fillAlgorithmHistory(
        this, Mantid::Kernel::DateAndTime::getCurrentTime(), 0,
        Algorithm::g_execCount);
    if (!isChild()) {
      m_inputWorkspace->history().addHistory(m_history);
    }
    // this is a child algorithm, but we still want to keep the history.
    else if (isRecordingHistoryForChild() && m_parentHistory) {
      m_parentHistory->addChildHistory(m_history);
    }
  }
  // Now execute the Child Algorithm. Catch and log any error, but don't stop.
  try {
    saveNexusPro->execute();
  } catch (std::runtime_error &) {
    g_log.error(
        "Unable to successfully run SaveNexusprocessed Child Algorithm");
  }
  if (!saveNexusPro->isExecuted())
    g_log.error(
        "Unable to successfully run SaveNexusProcessed Child Algorithm");
  //
  progress(1);
}