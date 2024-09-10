// get generic socket error info string about last error
CTString CCommunicationInterface::GetSocketError(INDEX iError)
{
  CTString strError;
  strError.PrintF(TRANSV("Socket %d, Error %d (%s)"),
    cci_hSocket, iError, ErrorDescription(&SocketErrors, iError));
  return strError;
};