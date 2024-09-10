/**
 * Main function that will be run by the scheduler.
 *
 * @param cls closure
 * @param args remaining command-line arguments
 * @param cfgfile name of the configuration file used (for saving, can be NULL!)
 * @param cfg configuration
 */
static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  int dst_af;
  int req_af;
  struct GNUNET_PeerIdentity peer;
  struct GNUNET_HashCode sd;
  const void *addr;
  struct in_addr v4;
  struct in6_addr v6;
  uint8_t protocol;
  struct GNUNET_TIME_Absolute etime;

  etime = GNUNET_TIME_relative_to_absolute (duration);
  GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_UNIT_FOREVER_REL,
				&do_disconnect, NULL);
  handle = GNUNET_VPN_connect (cfg);
  if (NULL == handle)
    goto error;
  req_af = AF_UNSPEC;
  if (ipv4)
  {
    if (ipv6)
    {
      FPRINTF (stderr, _("Option `%s' makes no sense with option `%s'.\n"),
               "-4", "-6");
      goto error;
    }
    req_af = AF_INET;
  }
  if (ipv6)
    req_af = AF_INET6;

  if (NULL == target_ip)
  {
    if (NULL == service_name)
    {
      FPRINTF (stderr, _("Option `%s' or `%s' is required.\n"),
               "-i", "-s");
      goto error;
    }
    if (NULL == peer_id)
    {
      FPRINTF (stderr, _("Option `%s' is required when using option `%s'.\n"),
               "-p", "-s");
      goto error;
    }
    if (! (tcp | udp) )
    {
      FPRINTF (stderr, _("Option `%s' or `%s' is required when using option `%s'.\n"),
               "-t", "-u", "-s");
      goto error;
    }
    if (tcp & udp)
    {
      FPRINTF (stderr, _("Option `%s' makes no sense with option `%s'.\n"),
               "-t", "-u");
      goto error;
    }
    if (tcp)
      protocol = IPPROTO_TCP;
    if (udp)
      protocol = IPPROTO_UDP;
    if (GNUNET_OK !=
	GNUNET_CRYPTO_eddsa_public_key_from_string (peer_id,
                                                    strlen (peer_id),
                                                    &peer.public_key))
    {
      FPRINTF (stderr,
               _("`%s' is not a valid peer identifier.\n"),
               peer_id);
      goto error;
    }
    GNUNET_TUN_service_name_to_hash (service_name,
                                     &sd);
    request = GNUNET_VPN_redirect_to_peer (handle,
					   req_af,
					   protocol,
					   &peer,
					   &sd,
					   etime,
					   &allocation_cb, NULL);
  }
  else
  {
    if (1 != inet_pton (AF_INET6, target_ip, &v6))
    {
      if (1 != inet_pton (AF_INET, target_ip, &v4))
      {
	FPRINTF (stderr, _("`%s' is not a valid IP address.\n"),
		 target_ip);
	goto error;
      }
      else
      {
	dst_af = AF_INET;
	addr = &v4;
      }
    }
    else
    {
      dst_af = AF_INET6;
      addr = &v6;
    }
    request = GNUNET_VPN_redirect_to_ip (handle,
					 req_af,
					 dst_af,
					 addr,
					 etime,
					 &allocation_cb, NULL);
  }
  return;

 error:
  GNUNET_SCHEDULER_shutdown ();
  ret = 1;
}