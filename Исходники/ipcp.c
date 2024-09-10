/*
 * ipcp_nakci - Peer has sent a NAK for some of our CIs.
 * This should not modify any state if the Nak is bad
 * or if IPCP is in the LS_OPENED state.
 *
 * Returns:
 *  0 - Nak was bad.
 *  1 - Nak was good.
 */
static int
ipcp_nakci(fsm *f, u_char *p, int len)
{
  ipcp_options *go = &ipcp_gotoptions[f->unit];
  u_char cimaxslotindex, cicflag;
  u_char citype, cilen, *next;
  u_short cishort;
  u32_t ciaddr1, ciaddr2, l, cidnsaddr;
  ipcp_options no;    /* options we've seen Naks for */
  ipcp_options try;    /* options to request next time */

  BZERO(&no, sizeof(no));
  try = *go;

  /*
   * Any Nak'd CIs must be in exactly the same order that we sent.
   * Check packet length and CI length at each step.
   * If we find any deviations, then this packet is bad.
   */
#define NAKCIADDR(opt, neg, old, code) \
  if (go->neg && \
      len >= (cilen = (old? CILEN_ADDRS: CILEN_ADDR)) && \
      p[1] == cilen && \
      p[0] == opt) { \
    len -= cilen; \
    INCPTR(2, p); \
    GETLONG(l, p); \
    ciaddr1 = htonl(l); \
    if (old) { \
      GETLONG(l, p); \
      ciaddr2 = htonl(l); \
      no.old_addrs = 1; \
    } else { \
      ciaddr2 = 0; \
    } \
    no.neg = 1; \
    code \
  }

#define NAKCIVJ(opt, neg, code) \
  if (go->neg && \
      ((cilen = p[1]) == CILEN_COMPRESS || cilen == CILEN_VJ) && \
      len >= cilen && \
      p[0] == opt) { \
    len -= cilen; \
    INCPTR(2, p); \
    GETSHORT(cishort, p); \
    no.neg = 1; \
    code \
  }
  
#define NAKCIDNS(opt, neg, code) \
  if (go->neg && \
      ((cilen = p[1]) == CILEN_ADDR) && \
      len >= cilen && \
      p[0] == opt) { \
    len -= cilen; \
    INCPTR(2, p); \
    GETLONG(l, p); \
    cidnsaddr = htonl(l); \
    no.neg = 1; \
    code \
  }

  /*
   * Accept the peer's idea of {our,his} address, if different
   * from our idea, only if the accept_{local,remote} flag is set.
   */
  NAKCIADDR((go->old_addrs? CI_ADDRS: CI_ADDR), neg_addr, go->old_addrs,
    if (go->accept_local && ciaddr1) { /* Do we know our address? */
      try.ouraddr = ciaddr1;
      IPCPDEBUG((LOG_INFO, "local IP address %s\n",
           inet_ntoa(ciaddr1)));
    }
    if (go->accept_remote && ciaddr2) { /* Does he know his? */
      try.hisaddr = ciaddr2;
      IPCPDEBUG((LOG_INFO, "remote IP address %s\n",
           inet_ntoa(ciaddr2)));
    }
  );

  /*
   * Accept the peer's value of maxslotindex provided that it
   * is less than what we asked for.  Turn off slot-ID compression
   * if the peer wants.  Send old-style compress-type option if
   * the peer wants.
   */
  NAKCIVJ(CI_COMPRESSTYPE, neg_vj,
    if (cilen == CILEN_VJ) {
      GETCHAR(cimaxslotindex, p);
      GETCHAR(cicflag, p);
      if (cishort == IPCP_VJ_COMP) {
        try.old_vj = 0;
        if (cimaxslotindex < go->maxslotindex) {
          try.maxslotindex = cimaxslotindex;
        }
        if (!cicflag) {
          try.cflag = 0;
        }
      } else {
        try.neg_vj = 0;