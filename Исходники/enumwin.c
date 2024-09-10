BOOL CALLBACK
EnumChildWindowProc(HWND hWnd, LPARAM lparam)
{
  char cBuf[MAX_PATH] = "";
  int i;

  if (bNoHidden)
    if (!IsWindowVisible(hWnd) | !IsWindowEnabled(hWnd))
      return TRUE;

  ++dwChildrenCount;

  ++iLevel;
  putch('\t');
  for (i = iLevel; i; i--)
    putch('\t');
  putch('\t');

  GetClassName(hWnd, cBuf, sizeof cBuf);
  CharToOem(cBuf, cBuf);
  printf("%s\\", cBuf);
  GetWindowText(hWnd, cBuf, sizeof cBuf);
  CharToOem(cBuf, cBuf);
  printf("%s\n", cBuf);

  EnumChildWindows(hWnd, (WNDENUMPROC)EnumChildWindowProc, 0);
  --iLevel;

  return TRUE;
}