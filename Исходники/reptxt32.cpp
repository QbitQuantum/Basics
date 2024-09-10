DWORD
process(const char cFilename[], const char cmpstr[],
	const char newstr[], DWORD txtlen, DWORD dwCmpFlags)
{
  HANDLE hFile = CreateFile(cFilename, GENERIC_READ | GENERIC_WRITE,
			    FILE_SHARE_DELETE, NULL, OPEN_ALWAYS,
			    FILE_FLAG_SEQUENTIAL_SCAN, NULL);

  if (hFile == INVALID_HANDLE_VALUE)
    {
      win_perror(cFilename);
      return 0;
    }

  printf("\rReading %s...", cFilename);
  clreol();

  HANDLE hMap = CreateFileMapping(hFile, NULL,
				  PAGE_READWRITE | SEC_COMMIT | SEC_NOCACHE,
				  0, 0,
				  NULL);
  if (hMap == NULL)
    {
      win_perror(cFilename);
      CloseHandle(hFile);
      return 0;
    }

  char *buffer = (char *)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  if (!buffer)
    {
      win_perror();
      CloseHandle(hMap);
      CloseHandle(hFile);
      return 0;
    }

  printf("\rSearching \"%s\"...", cFilename);
  clreol();

  DWORD stoppos = GetFileSize(hFile, NULL) - txtlen;
  DWORD occur = 0;
  LCID lcidLocale = MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
			     SORT_DEFAULT);
  for (DWORD now = 0; now <= stoppos; now++)
    {
      if (CompareString(lcidLocale, dwCmpFlags, buffer + now, txtlen, cmpstr,
			txtlen) == 2)
	{
	  CopyMemory(buffer + now, newstr, txtlen);
	  ++occur;

	  printf("\r%u replacement%s in \"%s\"...",
		 occur, occur > 1 ? "s" : "", cFilename);
	  clreol();
	}

      Sleep(0);
    }

  UnmapViewOfFile(buffer);
  CloseHandle(hMap);
  CloseHandle(hFile);

  return occur;
}