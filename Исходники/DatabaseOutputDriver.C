void DatabaseOutputDriver::vlog(TestOutputStream stream, const char *fmt,
				va_list args)
{
  FILE *dbout = NULL;

  if (dblogFilename.empty()) {
#if defined(os_windows_test)
     char *tfile = _tempnam(".", "dts");
     if (tfile) {
        dbout = fopen(tfile, "w+b");
     }
#else
    dbout = tmpfile();
#endif
    if (NULL == dbout) {
      fprintf(stderr, "[%s:%u] - Error opening temp log file\n", __FILE__, __LINE__);
    } else { // FIXME Check return values
      int count = vfprintf(dbout, fmt, args);
      fflush(dbout);
      fseek(dbout, 0, SEEK_SET);
      char *buffer = new char[count];
      fread(buffer, sizeof (char), count, dbout);
      pretestLog.write(buffer, count);
      delete [] buffer;
      fclose(dbout);
    }
  } else {
    dbout = fopen(dblogFilename.c_str(), "a");
    if (NULL == dbout) {
      fprintf(stderr, "[%s:%u] - Error opening log file\n", __FILE__, __LINE__);
      return;
    }
    vfprintf(dbout, fmt, args);
    fclose(dbout);
  }
}