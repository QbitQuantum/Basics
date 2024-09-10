FileInformation FileDescriptor::getInfo() const {
#ifndef _WIN32
  struct stat st;
  if (fstat(fd_, &st)) {
    int err = errno;
    throw std::system_error(err, std::generic_category(), "fstat");
  }
  return FileInformation(st);
#else // _WIN32
  FILE_BASIC_INFO binfo;
  FILE_STANDARD_INFO sinfo;

  if (!GetFileInformationByHandleEx(
          (HANDLE)handle(), FileBasicInfo, &binfo, sizeof(binfo))) {
    throw std::system_error(
        GetLastError(),
        std::system_category(),
        "GetFileInformationByHandleEx FileBasicInfo");
  }

  FileInformation info(binfo.FileAttributes);

  FILETIME_LARGE_INTEGER_to_timespec(binfo.CreationTime, &info.ctime);
  FILETIME_LARGE_INTEGER_to_timespec(binfo.LastAccessTime, &info.atime);
  FILETIME_LARGE_INTEGER_to_timespec(binfo.LastWriteTime, &info.mtime);

  if (!GetFileInformationByHandleEx(
          (HANDLE)handle(), FileStandardInfo, &sinfo, sizeof(sinfo))) {
    throw std::system_error(
        GetLastError(),
        std::system_category(),
        "GetFileInformationByHandleEx FileStandardInfo");
  }

  info.size = sinfo.EndOfFile.QuadPart;
  info.nlink = sinfo.NumberOfLinks;

  return info;
#endif
}