http_t * oyGetCUPSConnection()
{
  if(!cups_http_)
  {
    httpInitialize();
    /* Open access to printer(s) installed on system. */
    cups_http_ = httpConnectEncrypt ( cupsServer(),
                                      ippPort(),
                                      cupsEncryption());
  }
  return cups_http_;
}