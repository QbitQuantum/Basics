HANDLE init_tap()
{
  HANDLE hTAP32 = INVALID_HANDLE_VALUE;
  HKEY key;
  int enum_index, retry_attempts;
  char devid[1024], devname[1024];
  long len;
  ULONG status = TRUE;
  HKEY interface_key;
  char path[1024];
  struct sockaddr_in dns;
  char *addr_string;
  MIB_IPFORWARDROW route;
  DWORD dw;
  /* LPVOID lpMsgBuf; */ /* debug */

  printf("init_tap()\n");

  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NETWORK_CONNECTIONS_KEY, 0,
                   KEY_READ, &key))
    {
      printf("Unable to read registry:\n");
      return(NULL);
    }

  /* find the adapter with .tap suffix */
  for (enum_index = 0;; enum_index++)
    {
      len = sizeof(devid);
      if (RegEnumKeyEx(key, enum_index, devid, &len,
                       0, 0, 0, NULL) != ERROR_SUCCESS)
        {
          RegCloseKey(key);
          /* we've hit the end of the network connections list */
          printf("init_tap(): Couldn't find TAP-Win32 adapter.\n");
          return(NULL);
        }

      retry_attempts = 0;
init_tap_create_file_retry:
      sprintf(devname, "\\\\.\\Global\\%s.tap", devid);
      hTAP32 = CreateFile(devname,
                          GENERIC_WRITE | GENERIC_READ,
                          0,
                          0,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_SYSTEM,
                          0);

      dw = GetLastError();
      /* This is the most common error. We are trying to open
       * this device as a TAP but it is not a TAP-Win32 device,
       * so continue with the search.
       */
      if (dw == ERROR_FILE_NOT_FOUND)
        {
          continue;
          /* This error "A device attached to the system is not
           * functioning." occurs when we've found the TAP but
           * cannot open it. This could be restarting the HIP
           * service, so try again.
           */
        }
      else if (dw == ERROR_GEN_FAILURE)
        {
          if (retry_attempts < 3)
            {
              /* pause 400ms for device to become ready */
              Sleep(400);
              retry_attempts++;
              printf("Retrying open on TAP device...\n");
              goto init_tap_create_file_retry;
            }
        }

      /* debug
       *  FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER|
       *               FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw,
       *               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
       *               (LPTSTR) &lpMsgBuf, 0, NULL);
       *
       *  printf("DEBUG: devname %s error %d: %s\n",
       *       devname, dw, lpMsgBuf);
       *  LocalFree(lpMsgBuf); */

      /* dw == NO_ERROR */
      if (hTAP32 != INVALID_HANDLE_VALUE)
        {
          RegCloseKey(key);
          CloseHandle(hTAP32);
          break;
        }
    }

  /* Get the MAC address of the TAP-Win32
   * which is of the form 00:FF:{GID}
   */
  g_tap_mac = gid_to_mac(devid + 1);

  if (check_and_set_tun_address(devid, 1) < 0)
    {
      printf("TAP-Win32 setup failed.\n");
      return(NULL);
    }

  /* Open TAP-Win32 device */
  hTAP32 = CreateFile(devname, GENERIC_WRITE | GENERIC_READ, 0, 0,
                      OPEN_EXISTING,
                      FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_OVERLAPPED, 0);
  if (hTAP32 == INVALID_HANDLE_VALUE)
    {
      printf("Could not open Windows tap device\n");
      return(NULL);
    }

  /* set TAP-32 status to connected */
  if (!DeviceIoControl (hTAP32, TAP_IOCTL_SET_MEDIA_STATUS,
                        &status, sizeof (status),
                        &status, sizeof (status), &len, NULL))
    {
      printf("failed to set TAP-Win32 status as 'connected'.\n");
      return(NULL);
    }

  Sleep(10);

  /* set NameServer address on TAP-Win32 adapter to 1.x.x.x */
  sprintf (path, "%s\\%s", REG_INTERFACES_KEY, devid);
  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0,
                   KEY_WRITE, &interface_key) != ERROR_SUCCESS)
    {
      printf("Error opening registry key: %s", path);
      return(NULL);
    }

  memset(&dns, 0, sizeof(struct sockaddr_in));
  dns.sin_family = AF_INET;
  if (is_dns_thread_disabled())
    {
      memset(SA2IP(&dns), 0, 4);
    }
  else
    {
      get_preferred_lsi(SA(&dns));
    }
  addr_string = inet_ntoa(dns.sin_addr);
  if (RegSetValueEx(interface_key, "NameServer", 0, REG_SZ,
                    addr_string, strlen(addr_string)) != ERROR_SUCCESS)
    {
      printf("Changing TAP-Win32 adapter's NameServer failed\n");
      return(NULL);
    }
  RegCloseKey(interface_key);

  /* also add route for 1.0.0.0/8 to TAP-Win32 */
  memset(&route, 0, sizeof(route));
  route.dwForwardDest = htonl(0x01000000L);
  route.dwForwardMask = htonl(0xFF000000L);
  CreateIpForwardEntry(&route);

  /* add 2001:10::/28 HIT to TAP-Win32 */
  /* TODO */
  /* IPv6 may not be installed */
  /* equivalent of netsh interface ipv6 add address 2001:007x:xxxx ... */
  /* */

  return(hTAP32);
}