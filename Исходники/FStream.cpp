Result FStream_Unget(FStream* pfStream, wchar_t ch)
{
  int r = ungetwc(ch, pfStream->pFile);
  if (r == WEOF)
  {
  }
  return RESULT_OK;
}