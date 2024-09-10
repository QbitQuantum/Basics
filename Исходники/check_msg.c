static FILE* open_tmp_file(FILE** file)
{
  *file = tmpfile();
#ifdef WIN32
  if (*file == NULL)
  {
    char* tmp = getenv("TEMP");
    char* tmpFile = _tempnam(tmp, "check_");
    *file = fopen(tmpFile, "w+b");
    free(tmpFile);
  }
#endif
  return *file;
}