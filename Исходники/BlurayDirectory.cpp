CURL CBlurayDirectory::GetUnderlyingCURL(const CURL& url)
{
  assert(url.IsProtocol("bluray"));
  std::string host = url.GetHostName();
  std::string filename = url.GetFileName();
  return CURL(host.append(filename));
}