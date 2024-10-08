HTTPResult
HTTP_get(struct HTTP_ctx *http, const char *url, HTTP_read_callback *cb)
{
  char *host, *path;
  char *p1, *p2;
  char hbuf[256];
  int port = 80;
#ifdef CRYPTO
  int ssl = 0;
#endif
  int hlen, flen = 0;
  int rc, i;
  int len_known;
  HTTPResult ret = HTTPRES_OK;
  struct sockaddr_in sa;
  RTMPSockBuf sb = {0};

  http->status = -1;

  memset(&sa, 0, sizeof(struct sockaddr_in));
  sa.sin_family = AF_INET;

  /* we only handle http here */
  if (strncasecmp(url, "http", 4))
    return HTTPRES_BAD_REQUEST;

  if (url[4] == 's')
    {
#ifdef CRYPTO
      ssl = 1;
      port = 443;
      if (!RTMP_TLS_ctx)
	RTMP_TLS_Init();
#else
      return HTTPRES_BAD_REQUEST;
#endif
    }

  p1 = strchr(url + 4, ':');
  if (!p1 || strncmp(p1, "://", 3))
    return HTTPRES_BAD_REQUEST;

  host = p1 + 3;
  path = strchr(host, '/');
  hlen = path - host;
  strncpy(hbuf, host, hlen);
  hbuf[hlen] = '\0';
  host = hbuf;
  p1 = strrchr(host, ':');
  if (p1)
    {
      *p1++ = '\0';
      port = atoi(p1);
    }

  sa.sin_addr.s_addr = inet_addr(host);
  if (sa.sin_addr.s_addr == INADDR_NONE)
    {
      struct hostent *hp = gethostbyname(host);
      if (!hp || !hp->h_addr)
	return HTTPRES_LOST_CONNECTION;
      sa.sin_addr = *(struct in_addr *)hp->h_addr;
    }
  sa.sin_port = htons(port);
  sb.sb_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sb.sb_socket == -1)
    return HTTPRES_LOST_CONNECTION;
  i =
    sprintf(sb.sb_buf,
	    "GET %s HTTP/1.0\r\nUser-Agent: %s\r\nHost: %s\r\nReferrer: %.*s\r\n",
	    path, AGENT, host, (int)(path - url + 1), url);
  if (http->date[0])
    i += sprintf(sb.sb_buf + i, "If-Modified-Since: %s\r\n", http->date);
  i += sprintf(sb.sb_buf + i, "\r\n");

  if (connect
      (sb.sb_socket, (struct sockaddr *)&sa, sizeof(struct sockaddr)) < 0)
    {
      ret = HTTPRES_LOST_CONNECTION;
      goto leave;
    }
#ifdef CRYPTO
  if (ssl)
    {
#ifdef NO_SSL
      RTMP_Log(RTMP_LOGERROR, "%s, No SSL/TLS support", __FUNCTION__);
      ret = HTTPRES_BAD_REQUEST;
      goto leave;
#else
      TLS_client(RTMP_TLS_ctx, sb.sb_ssl);
      TLS_setfd(sb.sb_ssl, sb.sb_socket);
      if ((i = TLS_connect(sb.sb_ssl)) < 0)
	{
	  RTMP_Log(RTMP_LOGERROR, "%s, TLS_Connect failed", __FUNCTION__);
	  ret = HTTPRES_LOST_CONNECTION;
	  goto leave;
	}
#endif
    }
#endif
  RTMPSockBuf_Send(&sb, sb.sb_buf, i);

  /* set timeout */
#define HTTP_TIMEOUT	5
  {
    SET_RCVTIMEO(tv, HTTP_TIMEOUT);
    if (setsockopt
        (sb.sb_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)))
      {
        RTMP_Log(RTMP_LOGERROR, "%s, Setting socket timeout to %ds failed!",
	    __FUNCTION__, HTTP_TIMEOUT);
      }
  }

  sb.sb_size = 0;
  sb.sb_timedout = FALSE;
  if (RTMPSockBuf_Fill(&sb) < 1)
    {
      ret = HTTPRES_LOST_CONNECTION;
      goto leave;
    }
  if (strncmp(sb.sb_buf, "HTTP/1", 6))
    {
      ret = HTTPRES_BAD_REQUEST;
      goto leave;
    }

  p1 = strchr(sb.sb_buf, ' ');
  rc = atoi(p1 + 1);
  http->status = rc;

  if (rc >= 300)
    {
      if (rc == 304)
	{
	  ret = HTTPRES_OK_NOT_MODIFIED;
	  goto leave;
	}
      else if (rc == 404)
	ret = HTTPRES_NOT_FOUND;
      else if (rc >= 500)
	ret = HTTPRES_SERVER_ERROR;
      else if (rc >= 400)
	ret = HTTPRES_BAD_REQUEST;
      else
	ret = HTTPRES_REDIRECTED;
    }

  p1 = memchr(sb.sb_buf, '\n', sb.sb_size);
  if (!p1)
    {
      ret = HTTPRES_BAD_REQUEST;
      goto leave;
    }
  sb.sb_start = p1 + 1;
  sb.sb_size -= sb.sb_start - sb.sb_buf;

  while ((p2 = memchr(sb.sb_start, '\r', sb.sb_size)))
    {
      if (*sb.sb_start == '\r')
	{
	  sb.sb_start += 2;
	  sb.sb_size -= 2;
	  break;
	}
      else
	if (!strncasecmp
	    (sb.sb_start, "Content-Length: ", sizeof("Content-Length: ") - 1))
	{
	  flen = atoi(sb.sb_start + sizeof("Content-Length: ") - 1);
	}
      else
	if (!strncasecmp
	    (sb.sb_start, "Last-Modified: ", sizeof("Last-Modified: ") - 1))
	{
	  *p2 = '\0';
	  strcpy(http->date, sb.sb_start + sizeof("Last-Modified: ") - 1);
	}
      p2 += 2;
      sb.sb_size -= p2 - sb.sb_start;
      sb.sb_start = p2;
      if (sb.sb_size < 1)
	{
	  if (RTMPSockBuf_Fill(&sb) < 1)
	    {
	      ret = HTTPRES_LOST_CONNECTION;
	      goto leave;
	    }
	}
    }

  len_known = flen > 0;
  while ((!len_known || flen > 0) &&
	 (sb.sb_size > 0 || RTMPSockBuf_Fill(&sb) > 0))
    {
      cb(sb.sb_start, 1, sb.sb_size, http->data);
      if (len_known)
	flen -= sb.sb_size;
      http->size += sb.sb_size;
      sb.sb_size = 0;
    }

  if (flen > 0)
    ret = HTTPRES_LOST_CONNECTION;

leave:
  RTMPSockBuf_Close(&sb);
  return ret;
}