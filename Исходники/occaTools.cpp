  void releaseFile(const std::string &filename){
    std::string lockDir = getFileLock(filename);
#if (OCCA_OS == LINUX_OS) || (OCCA_OS == OSX_OS)
    rmdir(lockDir.c_str());
#else
    BOOL retStatus = RemoveDirectoryA(lockDir.c_str());
    assert(retStatus == TRUE);
#endif
  }