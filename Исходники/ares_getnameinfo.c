static void append_scopeid(struct sockaddr_in6 *addr6, unsigned int flags,
                           char *buf, size_t buflen)
{
#ifdef HAVE_IF_INDEXTONAME
  int is_ll, is_mcll;
#endif
  static const char fmt_u[] = "%u";
  static const char fmt_lu[] = "%lu";
  char tmpbuf[IF_NAMESIZE + 2];
  size_t bufl;
  const char *fmt = (sizeof(addr6->sin6_scope_id) > sizeof(unsigned int))?
    fmt_lu:fmt_u;

  tmpbuf[0] = '%';

#ifdef HAVE_IF_INDEXTONAME
  is_ll = IN6_IS_ADDR_LINKLOCAL(&addr6->sin6_addr);
  is_mcll = IN6_IS_ADDR_MC_LINKLOCAL(&addr6->sin6_addr);
  if ((flags & ARES_NI_NUMERICSCOPE) ||
      (!is_ll && !is_mcll))
    {
       sprintf(&tmpbuf[1], fmt, addr6->sin6_scope_id);
    }
  else
    {
      if (if_indextoname(addr6->sin6_scope_id, &tmpbuf[1]) == NULL)
        sprintf(&tmpbuf[1], fmt, addr6->sin6_scope_id);
    }
#else
  sprintf(&tmpbuf[1], fmt, addr6->sin6_scope_id);
  (void) flags;
#endif
  tmpbuf[IF_NAMESIZE + 1] = '\0';
  bufl = strlen(buf);

  if(bufl + strlen(tmpbuf) < buflen)
    /* only append the scopeid string if it fits in the target buffer */
    strcpy(&buf[bufl], tmpbuf);
}