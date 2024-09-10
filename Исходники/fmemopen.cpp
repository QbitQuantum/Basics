FILE *fmemopen (void *buf, size_t size, const char *opentype)
{
  FILE *f;
  assert(strcmp(opentype, "r") == 0);
#ifdef WIN32
  char* tmp_fname = _tempnam("%TMP%", "fmemopen");
  f = fopen(tmp_fname, "wt");
  fwrite(buf, 1, size, f);
  fclose(f);
  f = fopen(tmp_fname, "rt");
#else
  f = tmpfile();
  fwrite(buf, 1, size, f);
  rewind(f);
#endif
  return f;
}