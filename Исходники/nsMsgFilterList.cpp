NS_IMETHODIMP nsMsgFilterList::ClearLog()
{
  bool loggingEnabled = m_loggingEnabled;

  // disable logging while clearing
  m_loggingEnabled = false;

#ifdef DEBUG
  nsresult rv =
#endif
    TruncateLog();
  NS_ASSERTION(NS_SUCCEEDED(rv), "failed to truncate filter log");

  m_loggingEnabled = loggingEnabled;

  return NS_OK;
}