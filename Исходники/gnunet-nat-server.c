/**
 * Main function that will be run.
 *
 * @param cls closure
 * @param args remaining command-line arguments
 * @param cfgfile name of the configuration file used (for saving, can be NULL!)
 * @param c configuration
 */
static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *c)
{
  static const struct GNUNET_SERVER_MessageHandler handlers[] = {
    {&test, NULL, GNUNET_MESSAGE_TYPE_NAT_TEST,
     sizeof (struct GNUNET_NAT_TestMessage)},
    {NULL, NULL, 0, 0}
  };
  unsigned int port;
  struct sockaddr_in in4;
  struct sockaddr_in6 in6;

  socklen_t slen[] = {
    sizeof (in4),
    sizeof (in6),
    0
  };
  struct sockaddr *sa[] = {
    (struct sockaddr *) &in4,
    (struct sockaddr *) &in6,
    NULL
  };

  cfg = c;
  if ((args[0] == NULL) || (1 != SSCANF (args[0], "%u", &port)) || (0 == port)
      || (65536 <= port))
  {
    FPRINTF (stderr,
             _
             ("Please pass valid port number as the first argument! (got `%s')\n"),
             args[0]);
    return;
  }
  memset (&in4, 0, sizeof (in4));
  memset (&in6, 0, sizeof (in6));
  in4.sin_family = AF_INET;
  in4.sin_port = htons ((uint16_t) port);
  in6.sin6_family = AF_INET6;
  in6.sin6_port = htons ((uint16_t) port);
#if HAVE_SOCKADDR_IN_SIN_LEN
  in4.sin_len = sizeof (in4);
  in6.sin6_len = sizeof (in6);
#endif
  server =
      GNUNET_SERVER_create (NULL, NULL, (struct sockaddr * const *) sa, slen,
                            GNUNET_TIME_UNIT_SECONDS, GNUNET_YES);
  GNUNET_SERVER_add_handlers (server, handlers);
  GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_UNIT_FOREVER_REL, &shutdown_task,
                                NULL);
}