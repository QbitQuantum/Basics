/**
 * Handles saving the reductions from the generic algorithm.
 */
void IndirectDiffractionReduction::saveGenericReductions() {
  for (auto it = m_plotWorkspaces.begin(); it != m_plotWorkspaces.end(); ++it) {
    std::string wsName = *it;

    if (m_uiForm.ckGSS->isChecked()) {
      std::string tofWsName = wsName + "_tof";

      // Convert to TOF for GSS
      IAlgorithm_sptr convertUnits =
          AlgorithmManager::Instance().create("ConvertUnits");
      convertUnits->initialize();
      convertUnits->setProperty("InputWorkspace", wsName);
      convertUnits->setProperty("OutputWorkspace", tofWsName);
      convertUnits->setProperty("Target", "TOF");
      m_batchAlgoRunner->addAlgorithm(convertUnits);

      BatchAlgorithmRunner::AlgorithmRuntimeProps inputFromConvUnitsProps;
      inputFromConvUnitsProps["InputWorkspace"] = tofWsName;

      // Save GSS
      std::string gssFilename = wsName + ".gss";
      IAlgorithm_sptr saveGSS = AlgorithmManager::Instance().create("SaveGSS");
      saveGSS->initialize();
      saveGSS->setProperty("Filename", gssFilename);
      m_batchAlgoRunner->addAlgorithm(saveGSS, inputFromConvUnitsProps);
    }

    if (m_uiForm.ckNexus->isChecked()) {
      // Save NEXus using SaveNexusProcessed
      std::string nexusFilename = wsName + ".nxs";
      IAlgorithm_sptr saveNexus =
          AlgorithmManager::Instance().create("SaveNexusProcessed");
      saveNexus->initialize();
      saveNexus->setProperty("InputWorkspace", wsName);
      saveNexus->setProperty("Filename", nexusFilename);
      m_batchAlgoRunner->addAlgorithm(saveNexus);
    }

    if (m_uiForm.ckAscii->isChecked()) {
      // Save ASCII using SaveAscii version 1
      std::string asciiFilename = wsName + ".dat";
      IAlgorithm_sptr saveASCII =
          AlgorithmManager::Instance().create("SaveAscii", 1);
      saveASCII->initialize();
      saveASCII->setProperty("InputWorkspace", wsName);
      saveASCII->setProperty("Filename", asciiFilename);
      m_batchAlgoRunner->addAlgorithm(saveASCII);
    }
  }

  m_batchAlgoRunner->executeBatchAsync();
}