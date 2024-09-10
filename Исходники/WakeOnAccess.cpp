bool CWakeOnAccess::WakeUpHost(const CURL& url)
{
  std::string hostName = url.GetHostName();

  if (!hostName.empty())
    return WakeUpHost (hostName, url.Get());
  return true;
}