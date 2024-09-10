bool AreTheFileNamesDirDelimiterEqual(const UString &name1, const UString &name2)
{
  if(name1.Length() != name2.Length())
    return false;
  for(int i = 0; i < name1.Length(); i++)
  {
    wchar_t char1 = name1[i], char2 = name2[i];
    if (char1 == char2)
      continue;
    if (IsCharDirLimiter(char1) && IsCharDirLimiter(char2))
      continue;
    return false;
  }
  return true;
}