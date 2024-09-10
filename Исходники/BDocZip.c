uLong filetime(const char *f, tm_zip *tmzip, uLong *dt)
{
  int ret = 0;

  FILETIME ftLocal;
  HANDLE hFind;
  WIN32_FIND_DATA  ff32;
	FILETIME tmp;

  hFind = FindFirstFile(f,&ff32);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
    FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
    FindClose(hFind);
    ret = 1;
  } else {
		GetSystemTimeAsFileTime(&tmp);
		FileTimeToLocalFileTime(&tmp,&ftLocal);
    FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
	}

  return ret;
}