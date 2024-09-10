UString GetOSName2(const UString &name)
{
  if (name.IsEmpty())
    return UString();
  UString newName = GetOSName(name);
  if (newName[newName.Length() - 1] == kOSDirDelimiter)
    newName.Delete(newName.Length() - 1);
  return newName;
}