// If there is Reprase data already, it still writes new Reparse data
bool SetReparseData(CFSTR path, bool isDir, const void *data, DWORD size)
{
  NFile::NFind::CFileInfo fi;
  if (fi.Find(path))
  {
    if (fi.IsDir() != isDir)
    {
      ::SetLastError(ERROR_DIRECTORY);
      return false;
    }
  }
  else
  {
    if (isDir)
    {
      if (!NDir::CreateComplexDir(path))
        return false;
    }
    else
    {
      CreatePrefixDirOfFile(path);
      COutFile file;
      if (!file.Create(path, CREATE_NEW))
        return false;
    }
  }

  COutFile file;
  if (!file.Open(path,
      FILE_SHARE_WRITE,
      OPEN_EXISTING,
      FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS))
    return false;

  DWORD returnedSize;
  if (!file.DeviceIoControl(my_FSCTL_SET_REPARSE_POINT, (void *)data, size, NULL, 0, &returnedSize))
    return false;
  return true;
}