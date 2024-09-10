int
__gnat_fseek64 (FILE *stream, __int64 offset, int origin)
{
  return _fseeki64 (stream, offset, origin);
}