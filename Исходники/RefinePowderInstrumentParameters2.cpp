  /** Fit function
    * Minimizer: "Levenberg-MarquardtMD"/"Simplex"
   */
  bool RefinePowderInstrumentParameters2::doFitFunction(IFunction_sptr function, Workspace2D_sptr dataws, int wsindex,
                                                        string minimizer, int numiters, double& chi2, string& fitstatus)
  {
    // 0. Debug output
    stringstream outss;
    outss << "Fit function: " << m_positionFunc->asString() << endl << "Data To Fit: \n";
    for (size_t i = 0; i < dataws->readX(0).size(); ++i)
      outss << dataws->readX(wsindex)[i] << "\t\t" << dataws->readY(wsindex)[i] << "\t\t"
            << dataws->readE(wsindex)[i] << "\n";
    g_log.information() << outss.str();

    // 1. Create and setup fit algorithm
    API::IAlgorithm_sptr fitalg = createChildAlgorithm("Fit", 0.0, 0.2, true);
    fitalg->initialize();

    fitalg->setProperty("Function", function);
    fitalg->setProperty("InputWorkspace", dataws);
    fitalg->setProperty("WorkspaceIndex", wsindex);
    fitalg->setProperty("Minimizer", minimizer);
    fitalg->setProperty("CostFunction", "Least squares");
    fitalg->setProperty("MaxIterations", numiters);
    fitalg->setProperty("CalcErrors", true);

    // 2. Fit
    bool successfulfit = fitalg->execute();
    if (!fitalg->isExecuted() || ! successfulfit)
    {
      // Early return due to bad fit
      g_log.warning("Fitting to instrument geometry function failed. ");
      chi2 = DBL_MAX;
      fitstatus = "Minimizer throws exception.";
      return false;
    }

    // 3. Understand solution
    chi2 = fitalg->getProperty("OutputChi2overDoF");
    string tempfitstatus = fitalg->getProperty("OutputStatus");
    fitstatus = tempfitstatus;

    bool goodfit = fitstatus.compare("success") == 0;

    stringstream dbss;
    dbss << "Fit Result (GSL):  Chi^2 = " << chi2
         << "; Fit Status = " << fitstatus << ", Return Bool = " << goodfit << std::endl;
    vector<string> funcparnames = function->getParameterNames();
    for (size_t i = 0; i < funcparnames.size(); ++i)
      dbss << funcparnames[i] << " = " << setw(20) << function->getParameter(funcparnames[i])
           << " +/- " << function->getError(i) << "\n";
    g_log.debug() << dbss.str();

    return goodfit;
  }