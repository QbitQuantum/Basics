int
MDICOMProxyTCP::acceptConnection(int timeout)
{
  MLogClient l;

  if (mAcceptor == 0) {
    l.log(MLogClient::MLOG_ERROR,
	"MDICOMProxyTCP::acceptConnection no port was registered");
    return 1;
  }

  if (mAcceptor->acceptConnection(mSocket, timeout) != 0) {
    l.log(MLogClient::MLOG_ERROR,
	"MDICOMProxyTCP::acceptConnection unable to accept connection");
    return 1;
  }
  return 0;
}