void WorkspacePresenter::groupWorkspaces() {
  auto view = lockView();
  auto selected = view->getSelectedWorkspaceNames();

  std::string groupName("NewGroup");
  // get selected workspaces
  if (selected.size() < 2) {
    view->showCriticalUserMessage("Cannot Group Workspaces",
                                  "Select at least two workspaces to group ");
    return;
  }

  if (m_adapter->doesWorkspaceExist(groupName)) {
    if (!view->askUserYesNo("",
                            "Workspace " + groupName +
                                " already exists. Do you want to replace it?"))
      return;
  }

  try {
    std::string algName("GroupWorkspaces");
    Mantid::API::IAlgorithm_sptr alg =
        Mantid::API::AlgorithmManager::Instance().create(algName, -1);
    alg->initialize();
    alg->setProperty("InputWorkspaces", selected);
    alg->setPropertyValue("OutputWorkspace", groupName);
    // execute the algorithm
    bool bStatus = alg->execute();
    if (!bStatus) {
      view->showCriticalUserMessage("MantidPlot - Algorithm error",
                                    " Error in GroupWorkspaces algorithm");
    }
  } catch (...) {
    view->showCriticalUserMessage("MantidPlot - Algorithm error",
                                  " Error in GroupWorkspaces algorithm");
  }
}