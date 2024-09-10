static int
gethostbyname_resolve (struct GNUNET_SERVER_TransmitContext *tc,
                       const char *hostname)
{
  struct hostent *hp;

  hp = GETHOSTBYNAME (hostname);
  if (NULL == hp)
  {
    GNUNET_log (GNUNET_ERROR_TYPE_INFO,
                _("Could not find IP of host `%s': %s\n"),
                hostname,
                hstrerror (h_errno));
    return GNUNET_SYSERR;
  }
  if (hp->h_addrtype != AF_INET)
  {
    GNUNET_break (0);
    return GNUNET_SYSERR;
  }
  GNUNET_assert (hp->h_length == sizeof (struct in_addr));
  GNUNET_SERVER_transmit_context_append_data (tc,
					      hp->h_addr_list[0],
					      hp->h_length,
                                              GNUNET_MESSAGE_TYPE_RESOLVER_RESPONSE);
  return GNUNET_OK;
}