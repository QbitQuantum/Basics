static int portable_seek(FILE *f, AutoFile::fsize_t pos, int origin)
{
  return _fseeki64(f, pos, origin);
}