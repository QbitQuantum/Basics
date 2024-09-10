/**
 * Load a set of hosts from a configuration file.
 *
 * @param filename file with the host specification
 * @param cfg the configuration to use as a template while starting a controller
 *          on any of the loaded hosts.  Operation queue sizes specific to a host
 *          are also read from this configuration handle
 * @param hosts set to the hosts found in the file; caller must free this if
 *          number of hosts returned is greater than 0
 * @return number of hosts returned in 'hosts', 0 on error
 */
unsigned int
GNUNET_TESTBED_hosts_load_from_file (const char *filename,
                                     const struct GNUNET_CONFIGURATION_Handle
                                     *cfg,
                                     struct GNUNET_TESTBED_Host ***hosts)
{
  //struct GNUNET_TESTBED_Host **host_array;
  struct GNUNET_TESTBED_Host *starting_host;
  char *data;
  char *buf;
  char *username;
  char *hostname;
  regex_t rex;
  regmatch_t pmatch[6];
  uint64_t fs;
  short int port;
  unsigned int offset;
  unsigned int count;


  GNUNET_assert (NULL != filename);
  if (GNUNET_YES != GNUNET_DISK_file_test (filename))
  {
    LOG (GNUNET_ERROR_TYPE_WARNING, _("Hosts file %s not found\n"), filename);
    return 0;
  }
  if (GNUNET_OK !=
      GNUNET_DISK_file_size (filename, &fs, GNUNET_YES, GNUNET_YES))
    fs = 0;
  if (0 == fs)
  {
    LOG (GNUNET_ERROR_TYPE_WARNING, _("Hosts file %s has no data\n"), filename);
    return 0;
  }
  data = GNUNET_malloc (fs);
  if (fs != GNUNET_DISK_fn_read (filename, data, fs))
  {
    GNUNET_free (data);
    LOG (GNUNET_ERROR_TYPE_WARNING, _("Hosts file %s cannot be read\n"),
         filename);
    return 0;
  }
  buf = data;
  offset = 0;
  starting_host = NULL;
  count = 0;
  /* refer RFC 952 and RFC 1123 for valid hostnames */
  GNUNET_assert (0 == regcomp (&rex,
                               "^(([[:alnum:]]+)@)?" /* username */
                               "([[:alnum:]]+[-[:alnum:]_\\.]+)" /* hostname */
                               "(:([[:digit:]]{1,5}))?", /* port */
                               REG_EXTENDED | REG_ICASE));
  while (offset < (fs - 1))
  {
    offset++;
    if (((data[offset] == '\n')) && (buf != &data[offset]))
    {
      unsigned int size;

      data[offset] = '\0';
      username = NULL;
      hostname = NULL;
      port = 0;
      if ((REG_NOMATCH == regexec (&rex, buf, 6, pmatch, 0))
          || (-1 == pmatch[3].rm_so))
      {
        GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                    "Error reading line `%s' in hostfile\n", buf);
        buf = &data[offset + 1];
        continue;
      }
      if (-1 != pmatch[2].rm_so)
      {
        size = pmatch[2].rm_eo - pmatch[2].rm_so;
        username = GNUNET_malloc (size + 1);
        username[size] = '\0';
        GNUNET_assert (NULL != strncpy (username, buf + pmatch[2].rm_so, size));
      }
      if (-1 != pmatch[5].rm_so)
      {
        (void) SSCANF (buf + pmatch[5].rm_so, "%5hd", &port);
      }
      size = pmatch[3].rm_eo - pmatch[3].rm_so;
      hostname = GNUNET_malloc (size + 1);
      hostname[size] = '\0';
      GNUNET_assert (NULL != strncpy (hostname, buf + pmatch[3].rm_so, size));
      LOG (GNUNET_ERROR_TYPE_DEBUG,
           "Successfully read host %s, port %d and user %s from file\n",
           (NULL == hostname) ? "NULL" : hostname,
           port,
           (NULL == username) ? "NULL" : username);
      /* We store hosts in a static list; hence we only require the starting
       * host pointer in that list to access the newly created list of hosts */
      if (NULL == starting_host)
        starting_host = GNUNET_TESTBED_host_create (hostname, username, cfg,
                                                    port);
      else
        (void) GNUNET_TESTBED_host_create (hostname, username, cfg, port);
      count++;
      GNUNET_free_non_null (username);
      GNUNET_free (hostname);
      buf = &data[offset + 1];
    }
    else if ((data[offset] == '\n') || (data[offset] == '\0'))
      buf = &data[offset + 1];
  }
  regfree (&rex);
  GNUNET_free (data);
  if (NULL == starting_host)
    return 0;
  *hosts = GNUNET_malloc (sizeof (struct GNUNET_TESTBED_Host *) * count);
  memcpy (*hosts, &host_list[GNUNET_TESTBED_host_get_id_ (starting_host)],
          sizeof (struct GNUNET_TESTBED_Host *) * count);
  return count;
}