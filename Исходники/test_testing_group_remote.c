static void
run (void *cls, char *const *args, const char *cfgfile,
     const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  struct GNUNET_TESTING_Host *hosts;
  struct GNUNET_TESTING_Host *hostpos;
  struct GNUNET_TESTING_Host *temphost;
  char *hostfile;
  struct stat frstat;
  char *buf;
  char *data;
  int count;
  int ret;

  ok = 1;
#if VERBOSE
  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG, "Starting daemons.\n");
#endif

  if (GNUNET_SYSERR ==
      GNUNET_CONFIGURATION_get_value_number (cfg, "testing", "num_peers",
                                             &num_peers))
    num_peers = DEFAULT_NUM_PEERS;

  GNUNET_assert (num_peers > 0 && num_peers < (unsigned long long) -1);
  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_string (cfg, "testing", "hostfile",
                                             &hostfile))
    hostfile = NULL;

  hosts = NULL;
  data = NULL;
  if (hostfile != NULL)
  {
    if (GNUNET_OK != GNUNET_DISK_file_test (hostfile))
      GNUNET_DISK_fn_write (hostfile, NULL, 0,
                            GNUNET_DISK_PERM_USER_READ |
                            GNUNET_DISK_PERM_USER_WRITE);
    if ((0 != STAT (hostfile, &frstat)) || (frstat.st_size == 0))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  "Could not open file specified for host list, ending test!");
      ok = 1119;
      GNUNET_free (hostfile);
      return;
    }

    data = GNUNET_malloc_large (frstat.st_size);
    GNUNET_assert (data != NULL);
    if (frstat.st_size != GNUNET_DISK_fn_read (hostfile, data, frstat.st_size))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  "Could not read file %s specified for host list, ending test!",
                  hostfile);
      GNUNET_free (hostfile);
      GNUNET_free (data);
      return;
    }

    GNUNET_free_non_null (hostfile);

    buf = data;
    count = 0;
    while (count < frstat.st_size)
    {
      count++;
      if (count >= frstat.st_size)
        break;

      /* if (((data[count] == '\n') || (data[count] == '\0')) && (buf != &data[count])) */
      if (((data[count] == '\n')) && (buf != &data[count]))
      {
        data[count] = '\0';
        temphost = GNUNET_malloc (sizeof (struct GNUNET_TESTING_Host));
        ret =
            SSCANF (buf, "%a[a-zA-Z0-9]@%a[a-zA-Z0-9.]:%hd",
                    &temphost->username, &temphost->hostname, &temphost->port);
        if (3 == ret)
        {
          GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                      "Successfully read host %s, port %d and user %s from file\n",
                      temphost->hostname, temphost->port, temphost->username);
        }
        else
        {
          GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                      "Error reading line `%s' in hostfile\n", buf);
          GNUNET_free (temphost);
          buf = &data[count + 1];
          continue;
        }
        /* temphost->hostname = buf; */
        temphost->next = hosts;
        hosts = temphost;
        buf = &data[count + 1];
      }
      else if ((data[count] == '\n') || (data[count] == '\0'))
        buf = &data[count + 1];
    }
  }

  peers_left = num_peers;
  pg = GNUNET_TESTING_daemons_start (cfg, peers_left,   /* Total number of peers */
                                     peers_left,        /* Number of outstanding connections */
                                     peers_left,        /* Number of parallel ssh connections, or peers being started at once */
                                     TIMEOUT, NULL, NULL, &my_cb, NULL, NULL,
                                     NULL, hosts);
  hostpos = hosts;
  while (hostpos != NULL)
  {
    temphost = hostpos->next;
    GNUNET_free (hostpos->hostname);
    GNUNET_free (hostpos->username);
    GNUNET_free (hostpos);
    hostpos = temphost;
  }
  GNUNET_free_non_null (data);
  GNUNET_assert (pg != NULL);

}