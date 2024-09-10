AWavefrontDecoder::AWavefrontDecoder(const char *fname) : AMeshDecoder(fname)
{
  init();
  openFile(fname);
  readObjects();
}