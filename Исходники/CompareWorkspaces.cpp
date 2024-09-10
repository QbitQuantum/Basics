/**
 * Process two groups and ensure the Result string is set properly on the final
 * algorithm.
 *
 * @return A boolean true if execution was sucessful, false otherwise
 */
bool CompareWorkspaces::processGroups() {
  m_Result = true;
  m_Messages->setRowCount(0); // Clear table

  // Get workspaces
  Workspace_const_sptr w1 = getProperty("Workspace1");
  Workspace_const_sptr w2 = getProperty("Workspace2");

  // Attempt to cast to WorkspaceGroups (will be nullptr on failure)
  WorkspaceGroup_const_sptr ws1 =
      boost::dynamic_pointer_cast<const WorkspaceGroup>(w1);
  WorkspaceGroup_const_sptr ws2 =
      boost::dynamic_pointer_cast<const WorkspaceGroup>(w2);

  if (ws1 && ws2) { // Both are groups
    processGroups(ws1, ws2);
  } else if (!ws1 && !ws2) { // Neither are groups (shouldn't happen)
    m_Result = false;
    throw std::runtime_error("CompareWorkspaces::processGroups - Neither "
                             "input is a WorkspaceGroup. This is a logical "
                             "error in the code.");
  } else if (!ws1 || !ws2) {
    recordMismatch(
        "Type mismatch. One workspace is a group, the other is not.");
  }

  if (m_Result && ws1 && ws2) {
    g_log.notice() << "All workspaces in workspace groups \"" << ws1->name()
                   << "\" and \"" << ws2->name() << "\" matched!" << std::endl;
  }

  setProperty("Result", m_Result);
  setProperty("Messages", m_Messages);

  // Store output workspace in AnalysisDataService
  if (!isChild())
    this->store();

  setExecuted(true);
  notificationCenter().postNotification(
      new FinishedNotification(this, this->isExecuted()));

  return true;
}