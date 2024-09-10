ssize_t forward_udp(rlyinfo *ri, UDP_ATTR *udp, int method)
{
  settimer(TIMEOUTSEC);
  if (method == DIRECT) {
    switch (ri->dir) {
    case UP:
      ri->top = 0;
      ri->len = SS_LEN;
      readn(ri);
      if (ri->nread > 0) {
	/* (check and) save down-ward sockaddr */
	memcpy(&udp->si.prc.addr, ri->ss, ri->len);
	udp->si.prc.len = ri->len;

	/* decode socks udp header and set it to up-side sockaddr */
	if (decode_socks_udp(udp, (u_char *)ri->buf) < 0)
	  return(-1);
	/* shift buf top pointer by udp header length */
	ri->top = udp->sv.len;
	/* open upward socket unless opened yet */
	/* XXXX little bit ambiguous ?? */
	if (udp->u < 0) {
	  if ((udp->u = socket(udp->si.prs.addr.sa.sa_family,
				     SOCK_DGRAM, IPPROTO_IP)) < 0)
	    return(-1);
	  ri->to = udp->u;
	}
	/* set destination(up-ward) sockaddr */
	memcpy(ri->ss, &udp->si.prs.addr, udp->si.prs.len);
	ri->len = udp->si.prs.len;

	/* set write data len */
	if (ri->nread - udp->sv.len < 0)
	  return(-1);
	ri->nw = ri->nread - udp->sv.len;
      }
      break;
    case DOWN:
      if (udp->sv.len <= 0)
	return(-1);
      /* shift buf top pointer by udp header length */
      ri->top = udp->sv.len;
      ri->len = SS_LEN;
      readn(ri);
      if(ri->nread > 0) {
	/* (check and) save up-ward sockaddr */
	memcpy(&udp->si.prs.addr, ri->ss, ri->len);
	udp->si.prs.len = ri->len;

	/* prepend socks udp header to buffer */
	memcpy(ri->buf, udp->sv.data, udp->sv.len);
	/* set destination(down-ward) sockaddr */
	memcpy(ri->ss, &udp->si.prc.addr, udp->si.prc.len);
	ri->len = udp->si.prc.len;

	/* reset buf top */
	ri->top = 0;
	/* set write data len */
	ri->nw = ri->nread + udp->sv.len;
      }
      break;
    }
    writen(ri);
  } else {
    /* PROXY just relay */
    /* XXXXX  not yet */
  }
  settimer(0);
  if (ri->nread == 0)
    /* none the EOF case of UDP */
    return(0);
  if (ri->nread < 0)
    return(-1);
  return(ri->nwritten);
}