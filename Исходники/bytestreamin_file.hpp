inline I64 ByteStreamInFile::tell() const
{
#ifdef _WIN32
  return _ftelli64(file);
#else
  return (I64)ftello(file);
#endif
}