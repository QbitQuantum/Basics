/**
 * gst_rtsp_url_parse:
 * @urlstr: the url string to parse
 * @url: location to hold the result.
 *
 * Parse the RTSP @urlstr into a newly allocated #GstRTSPUrl. Free after usage
 * with gst_rtsp_url_free().
 *
 * Returns: a #GstRTSPResult.
 */
GstRTSPResult
gst_rtsp_url_parse (const gchar * urlstr, GstRTSPUrl ** url)
{
  GstRTSPUrl *res;
  gchar *p, *delim, *at, *col;
  gchar *host_end = NULL;
  guint i;

  g_return_val_if_fail (urlstr != NULL, GST_RTSP_EINVAL);
  g_return_val_if_fail (url != NULL, GST_RTSP_EINVAL);

  res = g_new0 (GstRTSPUrl, 1);

  p = (gchar *) urlstr;

  col = strstr (p, "://");
  if (col == NULL)
    goto invalid;

  for (i = 0; i < G_N_ELEMENTS (rtsp_schemes_map); i++) {
    if (g_ascii_strncasecmp (rtsp_schemes_map[i].scheme, p, col - p) == 0) {
      res->transports = rtsp_schemes_map[i].transports;
      p = col + 3;
      break;
    }
  }

  if (res->transports == GST_RTSP_LOWER_TRANS_UNKNOWN)
    goto invalid;

  delim = strpbrk (p, "/?");
  at = strchr (p, '@');

  if (at && delim && at > delim)
    at = NULL;

  if (at) {
    col = strchr (p, ':');

    /* must have a ':' and it must be before the '@' */
    if (col == NULL || col > at)
      goto invalid;

    res->user = g_strndup (p, col - p);
    col++;
    res->passwd = g_strndup (col, at - col);

    /* move to host */
    p = at + 1;
  }

  if (*p == '[') {
    res->family = GST_RTSP_FAM_INET6;

    /* we have an IPv6 address in the URL, find the ending ] which must be
     * before any delimiter */
    host_end = strchr (++p, ']');
    if (!host_end || (delim && host_end >= delim))
      goto invalid;

    /* a port specifier must follow the address immediately */
    col = host_end[1] == ':' ? host_end + 1 : NULL;
  } else {
    res->family = GST_RTSP_FAM_INET;

    col = strchr (p, ':');

    /* we have a ':' and a delimiter but the ':' is after the delimiter, it's
     * not really part of the hostname */
    if (col && delim && col >= delim)
      col = NULL;

    host_end = col ? col : delim;
  }

  if (!host_end)
    res->host = g_strdup (p);
  else {
    res->host = g_strndup (p, host_end - p);

    if (col) {
      res->port = strtoul (col + 1, NULL, 10);
    } else {
      /* no port specified, set to 0. gst_rtsp_url_get_port() will return the
       * default port */
      res->port = 0;
    }
  }
  p = delim;

  if (p && *p == '/') {
    delim = strchr (p, '?');
    if (!delim)
      res->abspath = g_strdup (p);
    else
      res->abspath = g_strndup (p, delim - p);
    p = delim;
  } else {
    res->abspath = g_strdup ("/");
  }

  if (p && *p == '?')
    res->query = g_strdup (p + 1);

  *url = res;

  return GST_RTSP_OK;

  /* ERRORS */
invalid:
  {
    gst_rtsp_url_free (res);
    return GST_RTSP_EINVAL;
  }
}