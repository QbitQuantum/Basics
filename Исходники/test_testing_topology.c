static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  char *topology_str;
  char *connect_topology_str;
  char *blacklist_topology_str;
  char *connect_topology_option_str;
  char *connect_topology_option_modifier_string;
  unsigned long long max_outstanding_connections;

  ok = 1;

  dotOutFile = FOPEN (dotOutFileName, "w");
  if (dotOutFile != NULL)
  {
    FPRINTF (dotOutFile, "%s",  "strict graph G {\n");
  }

  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
              "Starting daemons based on config file %s\n", cfgfile);
  if (GNUNET_YES !=
      GNUNET_CONFIGURATION_get_value_string (cfg, "paths", "servicehome",
                                             &test_directory))
  {
    ok = 404;
    return;
  }

  if ((GNUNET_YES ==
       GNUNET_CONFIGURATION_get_value_string (cfg, "testing", "topology",
                                              &topology_str)) &&
      (GNUNET_NO == GNUNET_TESTING_topology_get (&topology, topology_str)))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                "Invalid topology `%s' given for section %s option %s\n",
                topology_str, "TESTING", "TOPOLOGY");
    topology = GNUNET_TESTING_TOPOLOGY_CLIQUE;  /* Defaults to NONE, so set better default here */
  }

  if ((GNUNET_YES ==
       GNUNET_CONFIGURATION_get_value_string (cfg, "testing",
                                              "connect_topology",
                                              &connect_topology_str)) &&
      (GNUNET_NO ==
       GNUNET_TESTING_topology_get (&connection_topology,
                                    connect_topology_str)))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                "Invalid connect topology `%s' given for section %s option %s\n",
                connect_topology_str, "TESTING", "CONNECT_TOPOLOGY");
  }
  GNUNET_free_non_null (connect_topology_str);
  if ((GNUNET_YES ==
       GNUNET_CONFIGURATION_get_value_string (cfg, "testing",
                                              "connect_topology_option",
                                              &connect_topology_option_str)) &&
      (GNUNET_NO ==
       GNUNET_TESTING_topology_option_get (&connect_topology_option,
                                           connect_topology_option_str)))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                "Invalid connect topology option `%s' given for section %s option %s\n",
                connect_topology_option_str, "TESTING",
                "CONNECT_TOPOLOGY_OPTION");
    connect_topology_option = GNUNET_TESTING_TOPOLOGY_OPTION_ALL;       /* Defaults to NONE, set to ALL */
  }
  GNUNET_free_non_null (connect_topology_option_str);
  if (GNUNET_YES ==
      GNUNET_CONFIGURATION_get_value_string (cfg, "testing",
                                             "connect_topology_option_modifier",
                                             &connect_topology_option_modifier_string))
  {
    if (SSCANF
        (connect_topology_option_modifier_string, "%lf",
         &connect_topology_option_modifier) != 1)
    {
      GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                  _
                  ("Invalid value `%s' for option `%s' in section `%s': expected float\n"),
                  connect_topology_option_modifier_string,
                  "connect_topology_option_modifier", "TESTING");
    }
    GNUNET_free (connect_topology_option_modifier_string);
  }

  if (GNUNET_YES !=
      GNUNET_CONFIGURATION_get_value_string (cfg, "testing",
                                             "blacklist_transports",
                                             &blacklist_transports))
    blacklist_transports = NULL;

  if ((GNUNET_YES ==
       GNUNET_CONFIGURATION_get_value_string (cfg, "testing",
                                              "blacklist_topology",
                                              &blacklist_topology_str)) &&
      (GNUNET_NO ==
       GNUNET_TESTING_topology_get (&blacklist_topology,
                                    blacklist_topology_str)))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                "Invalid topology `%s' given for section %s option %s\n",
                topology_str, "TESTING", "BLACKLIST_TOPOLOGY");
  }
  GNUNET_free_non_null (topology_str);
  GNUNET_free_non_null (blacklist_topology_str);

  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_time (cfg, "testing", "SETTLE_TIME",
                                           &settle_time))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR, "Must provide option %s:%s!\n",
                "testing", "SETTLE_TIME");
    return;
  }

  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_time (cfg, "testing", "CONNECT_TIMEOUT",
                                           &connect_timeout))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR, "Must provide option %s:%s!\n",
                "testing", "CONNECT_TIMEOUT");
    return;
  }


  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing", "connect_attempts",
                                             &connect_attempts))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR, "Must provide option %s:%s!\n",
                "testing", "connect_attempts");
    return;
  }

  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing",
                                             "max_outstanding_connections",
                                             &max_outstanding_connections))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR, "Must provide option %s:%s!\n",
                "testing", "max_outstanding_connections");
    return;
  }

  if (GNUNET_SYSERR ==
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing", "num_peers",
                                             &num_peers))
    num_peers = DEFAULT_NUM_PEERS;

  main_cfg = cfg;

  peers_left = num_peers;
  modnum = num_peers / 4;
  dotnum = (num_peers / 50) + 1;
  if (modnum == 0)
    modnum = 1;
  if (dotnum == 0)
    dotnum = 1;
#if PROGRESS_BARS
  FPRINTF (stdout, "%s",  "Hostkey generation progress: [");
#endif
  /* Set up a task to end testing if peer start fails */
  die_task =
      GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply
                                    (GNUNET_TIME_UNIT_SECONDS,
                                     SECONDS_PER_PEER_START * num_peers),
                                    &end_badly,
                                    "didn't generate all hostkeys within a reasonable amount of time!!!");

  GNUNET_assert (num_peers > 0 && num_peers < (unsigned int) -1);
  pg = GNUNET_TESTING_daemons_start (cfg, peers_left,
                                     max_outstanding_connections, peers_left,
                                     GNUNET_TIME_relative_multiply
                                     (GNUNET_TIME_UNIT_SECONDS,
                                      SECONDS_PER_PEER_START * num_peers),
                                     &hostkey_callback, NULL,
                                     &peers_started_callback, NULL,
                                     &topology_callback, NULL, NULL);

}