bool CTVOSFile::WantsFile(const CURL& url)
{
  if (!StringUtils::EqualsNoCase(url.GetFileType(), "xml"))
    return false;
  return CDarwinNSUserDefaults::IsKeyFromPath(url.Get());
}