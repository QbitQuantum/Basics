MarFile *mar_wopen(const wchar_t *path) {
  FILE *fp;

  _wfopen_s(&fp, path, L"rb");
  if (!fp) {
    fprintf(stderr, "ERROR: could not open file in mar_wopen()\n");
    _wperror(path);
    return NULL;
  }

  return mar_fpopen(fp);
}