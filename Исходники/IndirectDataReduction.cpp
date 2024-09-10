/**
 * Loads an empty instrument into a workspace and returns a pointer to it.
 *
 * If an analyser and reflection are supplied then the corresponding IPF is also
 *loaded.
 * The workspace is not stored in ADS.
 *
 * @param instrumentName Name of the instrument to load
 * @param analyser Analyser being used (optional)
 * @param reflection Relection being used (optional)
 * @returns Pointer to instrument workspace
 */
Mantid::API::MatrixWorkspace_sptr
IndirectDataReduction::loadInstrumentIfNotExist(std::string instrumentName,
                                                std::string analyser,
                                                std::string reflection) {
  std::string idfDirectory =
      Mantid::Kernel::ConfigService::Instance().getString(
          "instrumentDefinition.directory");

  try {
    std::string parameterFilename =
        idfDirectory + instrumentName + "_Definition.xml";
    IAlgorithm_sptr loadAlg =
        AlgorithmManager::Instance().create("LoadEmptyInstrument");
    loadAlg->setChild(true);
    loadAlg->setLogging(false);
    loadAlg->initialize();
    loadAlg->setProperty("Filename", parameterFilename);
    loadAlg->setProperty("OutputWorkspace", "__IDR_Inst");
    loadAlg->execute();
    MatrixWorkspace_sptr instWorkspace =
        loadAlg->getProperty("OutputWorkspace");

    // Load the IPF if given an analyser and reflection
    if (!analyser.empty() && !reflection.empty()) {
      std::string ipfFilename = idfDirectory + instrumentName + "_" + analyser +
                                "_" + reflection + "_Parameters.xml";
      IAlgorithm_sptr loadParamAlg =
          AlgorithmManager::Instance().create("LoadParameterFile");
      loadParamAlg->setChild(true);
      loadParamAlg->setLogging(false);
      loadParamAlg->initialize();
      loadParamAlg->setProperty("Filename", ipfFilename);
      loadParamAlg->setProperty("Workspace", instWorkspace);
      loadParamAlg->execute();
    }

    return instWorkspace;
  } catch (std::exception &ex) {
    g_log.warning() << "Failed to load instrument with error: " << ex.what()
                    << ". The current facility may not be fully "
                       "supported.\n";
    return MatrixWorkspace_sptr();
  }
}