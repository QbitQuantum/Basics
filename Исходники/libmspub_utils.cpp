const char *windowsCharsetNameByOriginalCharset(const char *name)
{
  if (strcmp(name, "Shift_JIS") == 0)
  {
    return "windows-932";
  }
  if (strcmp(name, "GB18030") == 0)
  {
    return "windows-936";
  }
  if (strcmp(name, "Big5") == 0)
  {
    return "windows-950";
  }
  if (strcmp(name, "ISO-8859-1") == 0)
  {
    return "windows-1252";
  }
  if (strcmp(name, "ISO-8859-2") == 0)
  {
    return "windows-1250";
  }
  if (strcmp(name, "windows-1251") == 0)
  {
    return "windows-1251";
  }
  if (strcmp(name, "windows-1256") == 0)
  {
    return "windows-1256";
  }
  return nullptr;
}