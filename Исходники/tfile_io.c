char *convertWCHAR2CHAR(const wchar_t *fname) {
  int size      = 0;
  LPCWSTR lpw   = fname;
  char *name    = NULL;
  char *outName = 0;
  if (lpw) {
    LPSTR pStr = 0;
    size       = (lstrlenW(lpw) + 1) * 2;
    pStr       = (LPSTR)malloc(size * sizeof(char));
    name       = AtlW2AHelper(pStr, lpw, size, 0);
  }
  return name;
}