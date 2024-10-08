netio_ie5_t * 
netio_ie5_connect (char const *url)
{
  int resend = 0;
  DWORD type, type_s;
  netio_ie5_t * netio_ie5_conn;
  DWORD dw_ret;
  DWORD flags =
 /*    INTERNET_FLAG_DONT_CACHE |*/
    INTERNET_FLAG_KEEP_CONNECTION |
    INTERNET_FLAG_PRAGMA_NOCACHE |
    INTERNET_FLAG_RELOAD |
    INTERNET_FLAG_NO_CACHE_WRITE |
    INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_PASSIVE;

  if (internet == 0)
    {
      HINSTANCE h = LoadLibrary ("wininet.dll");
      if (!h)
	{
          /* XXX - how to return an error code? */
          g_warning("Failed to load wininet.dll");
	  return NULL;
	}
      /* pop-up dialup dialog box */
      /* XXX - do we need the dialup box or simply don't attempt an update in this case? */
      dw_ret = InternetAttemptConnect (0);
      if (dw_ret != ERROR_SUCCESS) {
        g_warning("InternetAttemptConnect failed: %u", dw_ret);
        return NULL;
      }
      internet = InternetOpen ("Wireshark Update", INTERNET_OPEN_TYPE_PRECONFIG,
			       NULL, NULL, 0);
      if(internet == NULL) {
        g_warning("InternetOpen failed %u", GetLastError());
        return NULL;
      }
    }

  netio_ie5_conn = g_malloc(sizeof(netio_ie5_t));

  netio_ie5_conn->connection = InternetOpenUrl (internet, url, NULL, 0, flags, 0);

try_again:

#if 0
	/* XXX - implement this option */
  if (net_user && net_passwd)
    {
      InternetSetOption (connection, INTERNET_OPTION_USERNAME,
			 net_user, strlen (net_user));
      InternetSetOption (connection, INTERNET_OPTION_PASSWORD,
			 net_passwd, strlen (net_passwd));
    }
#endif

#if 0
	/* XXX - implement this option */
  if (net_proxy_user && net_proxy_passwd)
    {
      InternetSetOption (connection, INTERNET_OPTION_PROXY_USERNAME,
			 net_proxy_user, strlen (net_proxy_user));
      InternetSetOption (connection, INTERNET_OPTION_PROXY_PASSWORD,
			 net_proxy_passwd, strlen (net_proxy_passwd));
    }
#endif

  if (resend)
    if (!HttpSendRequest (netio_ie5_conn->connection, 0, 0, 0, 0))
      netio_ie5_conn->connection = 0;

  if (!netio_ie5_conn->connection)
    {
      switch(GetLastError ()) {
      case ERROR_INTERNET_EXTENDED_ERROR:
          {
	  char buf[2000];
	  DWORD e, l = sizeof (buf);
	  InternetGetLastResponseInfo (&e, buf, &l);
	  MessageBox (0, buf, "Internet Error", 0);
          }
          break;
      case ERROR_INTERNET_NAME_NOT_RESOLVED:
          g_warning("Internet error: The servername could not be resolved");
          break;
      case ERROR_INTERNET_CANNOT_CONNECT:
          g_warning("Internet error: Could not connect to the server");
          break;
      default:
          g_warning("Internet error: %u", GetLastError ());
      }
      return NULL;
    }

  type_s = sizeof (type);
  InternetQueryOption (netio_ie5_conn->connection, INTERNET_OPTION_HANDLE_TYPE,
		       &type, &type_s);

  switch (type)
    {
    case INTERNET_HANDLE_TYPE_HTTP_REQUEST:
    case INTERNET_HANDLE_TYPE_CONNECT_HTTP:
      type_s = sizeof (DWORD);
      if (HttpQueryInfo (netio_ie5_conn->connection,
			 HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			 &type, &type_s, NULL))
	{
	  if (type == 401)	/* authorization required */
	    {
	      netio_ie5_flush_io (netio_ie5_conn);
              /* XXX - query net_user && net_passwd from user
	      get_auth (NULL);*/
	      resend = 1;
	      goto try_again;
	    }
	  else if (type == 407)	/* proxy authorization required */
	    {
	      netio_ie5_flush_io (netio_ie5_conn);
              /* XXX - query net_proxy_user && net_proxy_passwd from user
	      get_proxy_auth (NULL);*/
	      resend = 1;
	      goto try_again;
	    }
	  else if (type >= 300)
	    {
              g_warning("Failed with HTTP response %u", type);
              g_free(netio_ie5_conn);
	      return NULL;
	    }
	}
    }
	
	return netio_ie5_conn;
}