bool dirExists(const std::string& dirName)
{
#ifdef _WIN32
  DWORD ftyp = GetFileAttributesA(dirName.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!
#else
  struct stat sb;

  if (stat(dirName.c_str(), &sb)==0 && S_ISDIR(sb.st_mode))
  {
    return true;
  }
#endif

  return false;
}