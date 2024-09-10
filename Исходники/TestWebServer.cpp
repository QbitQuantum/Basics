  bool GetLastModifiedOfTestFile(const std::string& testFile, CDateTime& lastModified)
  {
    CFile file;
    if (!file.Open(URIUtils::AddFileToFolder(sourcePath, testFile), READ_NO_CACHE))
      return false;

    struct __stat64 statBuffer;
    if (file.Stat(&statBuffer) != 0)
      return false;

    struct tm *time;
#ifdef HAVE_LOCALTIME_R
    struct tm result = {};
    time = localtime_r((time_t*)&statBuffer.st_mtime, &result);
#else
    time = localtime((time_t *)&statBuffer.st_mtime);
#endif
    if (time == NULL)
      return false;

    lastModified = *time;
    return lastModified.IsValid();
  }