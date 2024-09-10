int
main (int argc, char **argv)
{
  int ret;
  int r = 1;
  WSADATA wsd;
  GUID id = GNUNET_NAMESPACE_PROVIDER_DNS;
  wchar_t *cmdl;
  int wargc;
  wchar_t **wargv;
  /* Allocate a 4K buffer to retrieve all the namespace providers */
  DWORD dwInitialBufferLen = 4096;
  DWORD dwBufferLen;
  WSANAMESPACE_INFO *pi;
  int p_count;
  int i;

  if (WSAStartup (MAKEWORD (2,2), &wsd) != 0)
  {
    fprintf (stderr, "WSAStartup () failed: %lu\n", GetLastError ());
    return 5;
  }

  dwBufferLen = dwInitialBufferLen;
  pi = malloc (dwBufferLen);
  if (NULL == pi)
  {
    fprintf (stderr, "malloc (%lu) failed: %d\n", dwBufferLen, errno);
    WSACleanup ();
    return 6;
  }
  p_count = WSAEnumNameSpaceProviders (&dwBufferLen, pi);
  if (SOCKET_ERROR == p_count)
  {
    DWORD err = GetLastError ();
    if (WSAEFAULT == err && dwBufferLen != dwInitialBufferLen)
    {
      free (pi);

      pi = malloc (dwBufferLen);
      if (pi == NULL)
      {
        fprintf (stderr, "malloc (%lu) failed: %d\n", dwBufferLen, errno);
        WSACleanup ();
        return 6;
      }

      p_count = WSAEnumNameSpaceProviders (&dwBufferLen, pi);
      if (SOCKET_ERROR == p_count)
      {
        fprintf (stderr, "WSAEnumNameSpaceProviders (&%lu, %p) failed: %lu\n", dwBufferLen, pi, GetLastError ());
        free (pi);
        WSACleanup ();
        return 7;
      }
    }
    else
    {
      fprintf (stderr, "WSAEnumNameSpaceProviders (&%lu, %p) failed: %lu\n", dwBufferLen, pi, GetLastError ());
      free (pi);
      WSACleanup ();
      return 8;
    }
  }
  for (i= 0; i < p_count; i++)
  {
    if (IsEqualGUID (&pi[i].NSProviderId, &id))
    {
      fprintf (stderr, "GNUnet DNS provider is already installed\n");
      free (pi);
      WSACleanup ();
      return 0;
    }
  }
  free (pi);

  cmdl = GetCommandLineW ();
  if (cmdl == NULL)
  {
    WSACleanup ();
    return 2;
  }
  wargv = CommandLineToArgvW (cmdl, &wargc);
  if (wargv == NULL)
  {
    WSACleanup ();
    return 3;
  }
  r = 4;

  if (wargc == 2)
  {
    ret = WSCInstallNameSpace (L"GNUnet DNS provider", wargv[1], NS_DNS, 0, &id);
    if (ret == NO_ERROR)
    {
      fprintf (stderr, "Installed GNUnet DNS provider\n");
      r = 0;
    }
    else
    {
      r = 1;
      fprintf (stderr,
          "WSCInstallNameSpace (L\"GNUnet DNS provider\", \"%S\", %d, 0, %p) failed: %lu\n",
          wargv[1], NS_DNS, &id, GetLastError ());
    }
  }
  else
    fprintf (stderr, "Usage: %S <path-to-libw32nsp>\n", wargv[0]);
  WSACleanup ();
  return r;
}