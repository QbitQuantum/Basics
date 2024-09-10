int
main (int argc, char **argv)
{
  int ret;
  GUID id = GNUNET_NAMESPACE_PROVIDER_DNS;
  WSADATA wsd;

  if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
  {
    fprintf (stderr, "WSAStartup() failed: %lu\n", GetLastError());
    return 5;
  }

  ret = WSCUnInstallNameSpace (&id);
  if (ret == NO_ERROR)
  {
    WSACleanup ();
    return 0;
  }
  fprintf (stderr, "WSCUnInstallNameSpace() failed: %lu\n", GetLastError ());
  WSACleanup ();
  return 1;
}