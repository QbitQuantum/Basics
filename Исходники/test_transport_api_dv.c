static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  char *topology_str;
  char *connect_topology_str;
  char *blacklist_topology_str;
  char *connect_topology_option_str;
  char *connect_topology_option_modifier_string;

  ok = 1;

  dotOutFile = fopen (dotOutFileName, "w");
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
      GNUNET_log_config_invalid (GNUNET_ERROR_TYPE_WARNING,
				 "testing", "connect_topology_option_modifier",
				 "expected float");
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
  if (GNUNET_SYSERR ==
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing", "num_peers",
                                             &num_peers))
    num_peers = DEFAULT_NUM_PEERS;

  if (GNUNET_SYSERR ==
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing",
                                             "additional_messages",
                                             &num_additional_messages))
    num_additional_messages = DEFAULT_ADDITIONAL_MESSAGES;

  main_cfg = cfg;

  GNUNET_assert (num_peers > 0 && num_peers < (unsigned int) -1);
  peers_left = num_peers;

  /* Set up a task to end testing if peer start fails */
  die_task =
      GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply
                                    (GNUNET_TIME_UNIT_MINUTES, 5), &end_badly,
                                    "didn't start all daemons in reasonable amount of time!!!");

  peer_daemon_hash = GNUNET_CONTAINER_multihashmap_create (peers_left, GNUNET_NO);
  pg = GNUNET_TESTING_daemons_start (cfg, peers_left,   /* Total number of peers */
                                     peers_left,        /* Number of outstanding connections */
                                     peers_left,        /* Number of parallel ssh connections, or peers being started at once */
                                     TIMEOUT, &hostkey_callback, NULL,
                                     &peers_started_callback, NULL,
                                     &topology_callback, NULL, NULL);

}