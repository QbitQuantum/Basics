/** Makes up the correct history of the output workspace
*/
void ConjoinXRuns::fillHistory() {
  // If this is not a child algorithm add the history
  if (!isChild()) {
    // Loop over the input workspaces, making the call that copies their
    // history to the output one
    for (auto &inWS : m_inputWS) {
      m_outWS->history().addHistory(inWS->getHistory());
    }
    // Add the history for the current algorithm to the output
    m_outWS->history().addHistory(m_history);
  }
  // this is a child algorithm, but we still want to keep the history.
  else if (isRecordingHistoryForChild() && m_parentHistory) {
    m_parentHistory->addChildHistory(m_history);
  }
}