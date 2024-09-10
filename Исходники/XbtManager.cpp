std::string CXbtManager::NormalizePath(const CURL& path)
{
  if (path.IsProtocol("xbt"))
    return path.GetHostName();

  return path.Get();
}