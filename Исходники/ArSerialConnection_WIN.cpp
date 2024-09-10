AREXPORT bool ArSerialConnection::getRing(void)
{
  DWORD modemStat;
  if (GetCommModemStatus(myPort, &modemStat))
  {
    return (bool) (modemStat & MS_RING_ON);
  }
  else
  {
    fprintf(stderr, "problem with GetCommModemStatus\n");
    return false;
  }
}