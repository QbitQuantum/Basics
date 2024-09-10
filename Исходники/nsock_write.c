/* Same as nsock_write except you can use a printf-style format and you can only use this for ASCII strings */
nsock_event_id nsock_printf(nsock_pool ms_pool, nsock_iod ms_iod,
          nsock_ev_handler handler, int timeout_msecs, void *userdata, char *format, ...) {
  mspool *nsp = (mspool *)ms_pool;
  msiod *nsi = (msiod *)ms_iod;
  msevent *nse;
  char buf[4096];
  char *buf2 = NULL;
  int res, res2;
  int strlength = 0;
  char displaystr[256];

  va_list ap;
  va_start(ap,format);

  nse = msevent_new(nsp, NSE_TYPE_WRITE, nsi, timeout_msecs, handler, userdata);
  assert(nse);

  res = Vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);

  if (res != -1) {
    if (res > sizeof(buf)) {
      buf2 = (char * )safe_malloc(res + 16);
      res2 = Vsnprintf(buf2, sizeof(buf), format, ap);
      if (res2 == -1 || res2 > res) {
        free(buf2);
        buf2 = NULL;
      } else
        strlength = res2;
    } else {
      buf2 = buf;
      strlength = res;
    }
  }

  if (!buf2) {
    nse->event_done = 1;
    nse->status = NSE_STATUS_ERROR;
    nse->errnum = EMSGSIZE;
  } else {
    if (strlength == 0) {
      nse->event_done = 1;
      nse->status = NSE_STATUS_SUCCESS;
    } else {
      fs_cat(&nse->iobuf, buf2, strlength);
    }
  }

  if (nsp->loglevel == NSOCK_LOG_DBG_ALL && nse->status != NSE_STATUS_ERROR && strlength < 80) {
    memcpy(displaystr, ": ", 2);
    memcpy(displaystr + 2, buf2, strlength);
    displaystr[2 + strlength] = '\0';
    replacenonprintable(displaystr + 2, strlength, '.');
  } else {
    displaystr[0] = '\0';
  }

  nsock_log_debug(nsp, "Write request for %d bytes to IOD #%li EID %li [%s]%s",
                  strlength, nsi->id, nse->id, get_peeraddr_string(nsi), displaystr);

  if (buf2 != buf)
    free(buf2);

  nsp_add_event(nsp, nse);

  return nse->id;
}