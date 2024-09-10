int lib_hostfile_lookup(FAR const void *addr, socklen_t len, int type,
                        FAR struct hostent *host, FAR char *buf,
                        size_t buflen, int *h_errnop)
{
  FAR FILE *stream;
  int herrnocode;
  int nread;

  /* Search the hosts file for a match */

  stream = fopen(CONFIG_NETDB_HOSTCONF_PATH, "r");
  if (stream == NULL)
    {
      int errcode = get_errno();

      nerr("ERROR:  Failed to open the hosts file %s: %d\n",
           CONFIG_NETDB_HOSTCONF_PATH, errcode);
      UNUSED(errcode);

      herrnocode = NO_RECOVERY;
      goto errorout_with_herrnocode;
    }

  /* Loop reading entries from the hosts file until a match is found or
   * until we hit the end-of-file.
   */

  do
    {
      /* Read the next entry from the hosts file */

      nread = lib_parse_hostfile(stream, host, buf, buflen);
      if (nread < 0)
        {
          /* Possible errors:
           *     ERANGE - Buffer not big enough
           *     ESPIPE - End of file (or possibly a read error).
           *     EAGAIN - Error parsing the line (E.g., missing hostname)
           */

          if (nread == -ESPIPE)
            {
              nread = 0;
            }
          else if (nread != -EAGAIN)
            {
              herrnocode = NO_RECOVERY;
              goto errorout_with_stream;
            }
        }
      else if (nread > 0 && len == host->h_length && type == host->h_addrtype)
        {
          /* We successfully read the entry and the type and size of the
           * address is good.  Now compare the addresses:
           */

          FAR char *hostaddr = host->h_addr;
          if (hostaddr != NULL)
            {
              ninfo("Comparing addresses...\n");
              if (memcmp(addr, hostaddr, len) == 0)
                {
                   /* We have a match */

                  fclose(stream);
                  return OK;
                }
            }
        }
    }
  while (nread != 0);

  /* We get here when the end of the hosts file is encountered without
   * finding the hostname.
   */

  herrnocode = HOST_NOT_FOUND;

errorout_with_stream:
  fclose(stream);

errorout_with_herrnocode:
  if (h_errnop)
    {
      *h_errnop = herrnocode;
    }

  return ERROR;
}