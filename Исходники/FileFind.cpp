bool MyGetLogicalDriveStrings(UStringVector &driveStrings)
{
  driveStrings.Clear();
  if (g_IsNT)
  {
    UINT32 size = GetLogicalDriveStringsW(0, NULL);
    if (size == 0)
      return false;
    UString buffer;
    UINT32 newSize = GetLogicalDriveStringsW(size, buffer.GetBuffer(size));
    if (newSize == 0)
      return false;
    if (newSize > size)
      return false;
    UString string;
    for (UINT32 i = 0; i < newSize; i++)
    {
      WCHAR c = buffer[i];
      if (c == L'\0')
      {
        driveStrings.Add(string);
        string.Empty();
      }
      else
        string += c;
    }
    return string.IsEmpty();
  }
  CSysStringVector driveStringsA;
  bool res = MyGetLogicalDriveStrings(driveStringsA);
  for (int i = 0; i < driveStringsA.Size(); i++)
    driveStrings.Add(GetUnicodeString(driveStringsA[i]));
  return res;
}