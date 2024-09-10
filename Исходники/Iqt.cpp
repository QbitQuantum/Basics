/**
 * Calculates binning parameters.
 */
void Iqt::calculateBinning() {
  using namespace Mantid::API;

  disconnect(m_dblManager, SIGNAL(valueChanged(QtProperty *, double)), this,
             SLOT(updatePropertyValues(QtProperty *, double)));

  QString wsName = m_uiForm.dsInput->getCurrentDataName();
  QString resName = m_uiForm.dsResolution->getCurrentDataName();
  if (wsName.isEmpty() || resName.isEmpty())
    return;

  double energyMin = m_dblManager->value(m_properties["ELow"]);
  double energyMax = m_dblManager->value(m_properties["EHigh"]);
  double numBins = m_dblManager->value(m_properties["SampleBinning"]);
  if (numBins == 0)
    return;

  IAlgorithm_sptr furyAlg =
      AlgorithmManager::Instance().create("TransformToIqt");
  furyAlg->initialize();

  furyAlg->setProperty("SampleWorkspace", wsName.toStdString());
  furyAlg->setProperty("ResolutionWorkspace", resName.toStdString());
  furyAlg->setProperty("ParameterWorkspace", "__FuryProperties_temp");

  furyAlg->setProperty("EnergyMin", energyMin);
  furyAlg->setProperty("EnergyMax", energyMax);
  furyAlg->setProperty("BinReductionFactor", numBins);

  furyAlg->setProperty("DryRun", true);

  furyAlg->execute();

  // Get property table from algorithm
  ITableWorkspace_sptr propsTable =
      AnalysisDataService::Instance().retrieveWS<ITableWorkspace>(
          "__FuryProperties_temp");

  // Get data from property table
  double energyWidth = propsTable->getColumn("EnergyWidth")->cell<float>(0);
  int sampleBins = propsTable->getColumn("SampleOutputBins")->cell<int>(0);
  int resolutionBins = propsTable->getColumn("ResolutionBins")->cell<int>(0);

  // Update data in property editor
  m_dblManager->setValue(m_properties["EWidth"], energyWidth);
  m_dblManager->setValue(m_properties["ResolutionBins"], resolutionBins);
  m_dblManager->setValue(m_properties["SampleBins"], sampleBins);

  connect(m_dblManager, SIGNAL(valueChanged(QtProperty *, double)), this,
          SLOT(updatePropertyValues(QtProperty *, double)));

  // Warn for low number of resolution bins
  int numResolutionBins =
      static_cast<int>(m_dblManager->value(m_properties["ResolutionBins"]));
  if (numResolutionBins < 5)
    showMessageBox("Number of resolution bins is less than 5.\nResults may be "
                   "inaccurate.");
}