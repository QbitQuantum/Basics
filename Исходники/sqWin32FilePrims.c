sqInt sqFileRenameOldSizeNewSize(char* oldNameIndex, sqInt oldNameSize, char* newNameIndex, sqInt newNameSize)
{
  WCHAR *oldPath = NULL;
  WCHAR *newPath = NULL;

  /* convert the file names into a null-terminated C string */
  ALLOC_WIN32_PATH(oldPath, oldNameIndex, oldNameSize);
  ALLOC_WIN32_PATH(newPath, newNameIndex, newNameSize);

  if(hasCaseSensitiveDuplicate(oldPath))
    FAIL();
  if(!MoveFileW(oldPath, newPath))
    FAIL();
  
  return 1;
}