void pdefCodeWriterFile::Printf(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  Indent();
  vfprintf_s(file, format, args);
  va_end(args);
}