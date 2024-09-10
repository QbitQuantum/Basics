/**
 * Handles a new file being selected by the browser.
 */
void DensityOfStates::handleFileChange() {
  QString filename = m_uiForm.mwInputFile->getFirstFilename();

  // Check if we have a .phonon file
  QFileInfo fileInfo(filename);
  bool isPhononFile = fileInfo.suffix() == "phonon";

  std::string filePropName("CASTEPFile");
  if (isPhononFile)
    filePropName = "PHONONFile";

  // Need a .phonon file for ion contributions
  if (isPhononFile) {
    // Load the ion table to populate the list of ions
    IAlgorithm_sptr ionTableAlgo =
        AlgorithmManager::Instance().create("SimulatedDensityOfStates");
    ionTableAlgo->initialize();
    ionTableAlgo->setProperty(filePropName, filename.toStdString());
    ionTableAlgo->setProperty("SpectrumType", "IonTable");
    ionTableAlgo->setProperty("OutputWorkspace", "__dos_ions");

    m_batchAlgoRunner->addAlgorithm(ionTableAlgo);

    connect(m_batchAlgoRunner, SIGNAL(batchComplete(bool)), this,
            SLOT(ionLoadComplete(bool)));
    m_batchAlgoRunner->executeBatchAsync();
  } else {