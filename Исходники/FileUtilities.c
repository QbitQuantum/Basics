boolByte removeDirectory(const CharString absolutePath) {
  boolByte result = false;

#if UNIX
  if(!fileExists(absolutePath->data)) {
    return false;
  }

  // This is a bit lazy, perhaps...
  CharString removeCommand = newCharString();
  snprintf(removeCommand->data, removeCommand->length, "/bin/rm -rf \"%s\"", absolutePath->data);
  result = system(removeCommand->data);
  freeCharString(removeCommand);
  return (result == 0);
#elif WINDOWS
  SHFILEOPSTRUCTA fileOperation = {0};
  fileOperation.wFunc = FO_DELETE;
  fileOperation.pFrom = absolutePath->data;
  fileOperation.fFlags = FOF_NO_UI;
  return (SHFileOperationA(&fileOperation) == 0);
#else
  logUnsupportedFeature("Copy directory recursively");
  return false;
#endif
}