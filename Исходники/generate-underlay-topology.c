/**
 * Main run function.
 *
 * @param cls NULL
 * @param args arguments passed to GNUNET_PROGRAM_run
 * @param cfgfile the path to configuration file
 * @param cfg the configuration file handle
 */
static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *config)
{
  const char *dbfile;
  const char *topology_string;
  unsigned int arg_uint1;
  unsigned int arg_uint2;
  const char *arg_str1;
  const char *value;
  unsigned int argc;

  argc = 0;
  arg_uint1 = 0; /* make compilers happy */
  arg_uint2 = 0; /* make compilers happy */
  if (NULL == args)
  {
    LOG_ERROR (_("Need at least 2 arguments\n"));
    return;
  }
  if (NULL == (dbfile = args[argc++]))
  {
    LOG_ERROR (_("Database filename missing\n"));
    return;
  }
  if (GNUNET_OK != setup_db (dbfile))
    return;
  if (NULL == (topology_string = args[argc++]))
  {
    LOG_ERROR (_("Topology string missing\n"));
    return;
  }
  if (GNUNET_YES != GNUNET_TESTBED_topology_get_ (&topology, topology_string))
  {
    LOG_ERROR (_("Invalid topology: %s\n"), topology_string);
    return;
  }
  arg_str1 = NULL;
  /* parse for first TOPOOPT.  This can either be arg_uint1 or arg_str1 */
  switch (topology)
  {
  case GNUNET_TESTBED_TOPOLOGY_ERDOS_RENYI:
  case GNUNET_TESTBED_TOPOLOGY_SMALL_WORLD_RING:
  case GNUNET_TESTBED_TOPOLOGY_SMALL_WORLD:
  case GNUNET_TESTBED_TOPOLOGY_SCALE_FREE:
    if (NULL == (value = args[argc++]))
    {
      LOG_ERROR (_("An argument is missing for given topology `%s'\n"),
                 topology_string);
      return;
    }
    if (-1 == SSCANF (value, "%u", &arg_uint1))
    {
      LOG_ERROR (_("Invalid argument `%s' given as topology argument\n"),
                 value);
      return;
    }
    break;
  case GNUNET_TESTBED_TOPOLOGY_FROM_FILE:
    if (NULL == (arg_str1 = args[argc++]))
    {
      LOG_ERROR (_("Filename argument missing for topology `%s'\n"),
                 topology_string);
      return;
    }
    break;
  default:
    break;
  }
  /* parse for second TOPOOPT.  Only required for SCALE_FREE topology */
  switch (topology)
  {
  case GNUNET_TESTBED_TOPOLOGY_SCALE_FREE:
    if (NULL == (value = args[argc++]))
    {
      LOG_ERROR (_("Second argument for topology `%s' is missing\n"),
                 topology_string);
      return;
    }
    if (-1 == SSCANF (value, "%u", &arg_uint2))
    {
      LOG_ERROR (_("Invalid argument `%s'; expecting unsigned int\n"), value);
      return;
    }
    break;
  default:
    break;
  }
  /* contruct topologies */
  switch (topology)
  {
  case GNUNET_TESTBED_TOPOLOGY_LINE:
  case GNUNET_TESTBED_TOPOLOGY_RING:
  case GNUNET_TESTBED_TOPOLOGY_CLIQUE:
  case GNUNET_TESTBED_TOPOLOGY_2D_TORUS:
    GNUNET_TESTBED_underlay_construct_ (num_peers, link_processor, NULL,
                                        topology);
    break;
  case GNUNET_TESTBED_TOPOLOGY_ERDOS_RENYI:
  case GNUNET_TESTBED_TOPOLOGY_SMALL_WORLD_RING:
  case GNUNET_TESTBED_TOPOLOGY_SMALL_WORLD:
    GNUNET_TESTBED_underlay_construct_ (num_peers, link_processor, NULL,
                                        topology,
                                        arg_uint1);
    break;
  case GNUNET_TESTBED_TOPOLOGY_FROM_FILE:
    GNUNET_TESTBED_underlay_construct_ (num_peers, link_processor, NULL,
                                        topology,
                                        arg_str1);
    break;
  case GNUNET_TESTBED_TOPOLOGY_SCALE_FREE:
    GNUNET_TESTBED_underlay_construct_ (num_peers, link_processor, NULL,
                                        topology,
                                        arg_uint1,
                                        arg_uint2);
    break;
  default:
    GNUNET_assert (0);
  }
}