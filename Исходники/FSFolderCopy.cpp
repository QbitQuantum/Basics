HRESULT MyMoveFolder(
    const UString &srcPath,
    const UString &destPathSpec,
    IFolderOperationsExtractCallback *callback,
    UInt64 &completedSize)
{
  UString destPath = destPathSpec;
  int len = srcPath.Length();
  if (destPath.Length() >= len && srcPath.CompareNoCase(destPath.Left(len)) == 0)
  {
    if (destPath.Length() == len || destPath[len] == WCHAR_PATH_SEPARATOR)
    {
      UString message = UString(L"can not move folder \'") +
          destPath + UString(L"\' onto itself");
      RINOK(callback->ShowMessage(message));
      return E_ABORT;
    }
  }

  if (MyMoveFile(srcPath, destPath, callback, completedSize))
    return S_OK;

  if (!NDirectory::CreateComplexDirectory(destPath))
  {
    UString message = UString(L"can not create folder ") +  destPath;
    RINOK(callback->ShowMessage(message));
    return E_ABORT;
  }
  {
    CEnumeratorW enumerator(CombinePath(srcPath, L"*"));
    CFileInfoEx fi;
    while (enumerator.Next(fi))
    {
      const UString srcPath2 = CombinePath(srcPath, fi.Name);
      const UString destPath2 = CombinePath(destPath, fi.Name);
      if (fi.IsDir())
      {
        RINOK(MyMoveFolder(srcPath2, destPath2, callback, completedSize));
      }
      else
      {
        RINOK(MyMoveFile(srcPath2, fi, destPath2, callback, completedSize));
      }
    }
  }
  if (!NDirectory::MyRemoveDirectory(srcPath))
  {
    UString message = UString(L"can not remove folder") + srcPath;
    RINOK(callback->ShowMessage(message));
    return E_ABORT;
  }
  return S_OK;
}