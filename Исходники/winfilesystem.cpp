bool WinFileSystem::copyFile(const String& from, const String& to)
{
  return SUCCEEDED(CopyFile2(from.c_str(), to.c_str(), NULL));
}