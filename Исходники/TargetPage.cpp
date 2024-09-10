wstring TargetPage::getEnvironmentVariable(const wchar_t *name)
{
  wchar_t
    *buffer;

  size_t
    length;

  wstring
    value;

  if (_wdupenv_s(&buffer,&length,name) == 0)
  {
    if (length > 0)
    {
      value=wstring(buffer);
      free(buffer);
      return(value);
    }
  }

  return(value);
}