void
TKVList::ReadFileDSN (LPCTSTR filename, LPCTSTR names)
{
  TCHAR value[512];
  LPCTSTR key;
  WORD len;

  for (key = names; *key; key += _tcslen (key) + 1)
    {
      value[0] = 0;
      if (SQLReadFileDSN (filename, _T("ODBC"), key, value,
	  NUMCHARS (value), &len))
	{
	  Define (key, value);
	}
    }
}