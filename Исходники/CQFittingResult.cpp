void CQFittingResult::slotSave(void)
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          QString::null, "TEXT Files (*.txt);;All Files (*.*);;", "Save to");

      if (fileName.isEmpty()) return;

      if (!fileName.endsWith(".txt") &&
          !fileName.endsWith(".")) fileName += ".txt";

      fileName = fileName.remove(QRegExp("\\.$"));

      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(utf8ToLocale(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  unsigned C_INT32 i, imax;

  // The global result and statistics
  file << "Objective Value\tRoot Mean Square\tStandard Deviation" << std::endl;
  file << mpProblem->getSolutionValue() << "\t";
  file << mpProblem->getRMS() << "\t";
  file << mpProblem->getStdDeviation() << std::endl;

  file << "Function Evaluations\tCPU Time [s]\tEvaluations/second [1/s]" << std::endl;
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  file << FunctionEvaluations << "\t";
  file << ExecutionTime << "\t";
  file << FunctionEvaluations / ExecutionTime << std::endl;

  // Set up the parameters table
  file << std::endl << "Parameters:" << std::endl;
  file << "Parameter\tValue\tStd. Deviation\tCoeff. of Variation [%]\tGradient" << std::endl;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & StdDeviations = mpProblem->getVariableStdDeviations();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        pDataModel->getObject(Items[i]->getObjectCN());

      if (pObject)
        {
          std::string Experiments =
            static_cast<CFitItem *>(Items[i])->getExperiments();

          if (Experiments != "")
            Experiments = "; {" + Experiments + "}";

          file << pObject->getObjectDisplayName() << Experiments << "\t";
        }
      else
        file << "Not Found\t";

      const C_FLOAT64 & Solution = Solutions[i];
      file << Solution << "\t";
      const C_FLOAT64 & StdDeviation = StdDeviations[i];
      file << StdDeviation << "\t";
      file << fabs(100.0 * StdDeviation / Solution) << "\t";
      file << Gradients[i] << std::endl;
    }

  // Set up the experiments table
  file << std::endl << "Experiments:" << std::endl;
  file << "Experiment\tObjective Value\tRoot Mean Square\tError Mean\tError Mean Std. Deviation" << std::endl;

  // Loop over the experiments
  const CExperimentSet & Experiments = mpProblem->getExperiementSet();

  imax = Experiments.getExperimentCount();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  for (i = 0; i != imax; i++)
    {
      const CExperiment & Experiment = * Experiments.getExperiment(i);
      file << Experiment.getObjectName() << "\t";
      file << Experiment.getObjectiveValue() << "\t";
      file << Experiment.getRMS() << "\t";
      file << Experiment.getErrorMean() << "\t";
      file << Experiment.getErrorMeanSD() << std::endl;
    }

  // Set up the fitted values table
  file << std::endl << "Fitted Values:" << std::endl;
  file << "Fitted Value\tObjective Value\tRoot Mean Square\tError Mean\tError Mean Std. Deviation" << std::endl;

  // Loop over the fitted values objects
  imax = Experiments.getDependentObjects().size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  for (i = 0; i != imax; i++)
    {
      const CCopasiObject * pObject = Experiments.getDependentObjects()[i];

      if (pObject)
        file << pObject->getObjectDisplayName() << "\t";
      else
        file << "Not Found\t";

      file << Experiments.getDependentObjectiveValues()[i] << "\t";
      file << Experiments.getDependentRMS()[i] << "\t";
      file << Experiments.getDependentErrorMean()[i] << "\t";
      file << Experiments.getDependentErrorMeanSD()[i] << std::endl;
    }

  file << std::endl;

  // Save the parameter correlations
  file << mpProblem->getCorrelations() << std::endl;

  // Save the Fisher information
  file << mpProblem->getFisherInformation() << std::endl;

}