/****************************************************************************
  Begin a metaserver scan for servers.  This just initiates the connection
  to the metaserver; later get_meta_server_list should be called whenever
  the socket has data pending to read and parse it.

  Returns FALSE on error (in which case errbuf will contain an error
  message).
****************************************************************************/
static bool begin_metaserver_scan(struct server_scan *scan)
{
  union fc_sockaddr addr;
  int s;

  scan->meta.urlpath = fc_lookup_httpd(scan->meta.name, &scan->meta.port,
				       metaserver);
  if (!scan->meta.urlpath) {
    scan->error_func(scan,
                     _("Invalid $http_proxy or metaserver value, must "
                       "start with 'http://'"));
    return FALSE;
  }

  if (!net_lookup_service(scan->meta.name, scan->meta.port, &addr, FALSE)) {
    scan->error_func(scan, _("Failed looking up metaserver's host"));
    return FALSE;
  }
  
  if ((s = socket(addr.saddr.sa_family, SOCK_STREAM, 0)) == -1) {
    scan->error_func(scan, fc_strerror(fc_get_errno()));
    return FALSE;
  }

  fc_nonblock(s);
  
  if (fc_connect(s, &addr.saddr, sockaddr_size(&addr)) == -1) {
    if (errno == EINPROGRESS) {
      /* With non-blocking sockets this is the expected result. */
      scan->meta.state = META_CONNECTING;
      scan->sock = s;
    } else {
      fc_closesocket(s);
      scan->error_func(scan, fc_strerror(fc_get_errno()));
      return FALSE;
    }
  } else {
    /* Instant connection?  Whoa. */
    scan->sock = s;
    scan->meta.state = META_CONNECTING;
    meta_send_request(scan);
  }

  return TRUE;
}