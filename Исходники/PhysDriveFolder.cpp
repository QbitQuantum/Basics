STDMETHODIMP CPhysDriveFolder::CopyTo(const UInt32 * /* indices */, UInt32 numItems,
    const wchar_t *path, IFolderOperationsExtractCallback *callback)
{
  if (numItems == 0)
    return S_OK;
  UString destPath = path;
  if (destPath.IsEmpty())
    return E_INVALIDARG;
  bool directName = (destPath[destPath.Length() - 1] != WCHAR_PATH_SEPARATOR);
  if (directName)
  {
    if (numItems > 1)
      return E_INVALIDARG;
  }
  else
    destPath += _name;

  UInt64 fileSize;
  if (GetLength(fileSize) == S_OK)
  {
    RINOK(callback->SetTotal(fileSize));
  }

  Int32 writeAskResult;
  CMyComBSTR destPathResult;
  RINOK(callback->AskWrite(GetFullPath(), BoolToInt(false), NULL, &fileSize,
      destPath, &destPathResult, &writeAskResult));
  if (!IntToBool(writeAskResult))
    return S_OK;

  RINOK(callback->SetCurrentFilePath(GetFullPathWithName()));

  UInt32 bufferSize = (_driveType == DRIVE_REMOVABLE) ? (18 << 10) * 4 : kBufferSize;
  return CopyFileSpec(GetFullPath(), destPathResult, false, fileSize, bufferSize, callback);
}