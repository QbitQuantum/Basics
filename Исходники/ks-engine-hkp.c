/* Map the host name NAME to the actual to be used host name.  This
   allows us to manage round robin DNS names.  We use our own strategy
   to choose one of the hosts.  For example we skip those hosts which
   failed for some time and we stick to one host for a time
   independent of DNS retry times.  */
static char *
map_host (const char *name)
{
  hostinfo_t hi;
  int idx;

  /* No hostname means localhost.  */
  if (!name || !*name)
    return xtrystrdup ("localhost");

  /* See whether the host is in our table.  */
  idx = find_hostinfo (name);
  if (idx == -1)
    {
      /* We never saw this host.  Allocate a new entry.  */
      struct addrinfo hints, *aibuf, *ai;
      int *reftbl;
      size_t reftblsize;
      int refidx;

      reftblsize = 100;
      reftbl = xtrymalloc (reftblsize * sizeof *reftbl);
      if (!reftbl)
        return NULL;
      refidx = 0;

      idx = create_new_hostinfo (name);
      if (idx == -1)
        {
          xfree (reftbl);
          return NULL;
        }
      hi = hosttable[idx];

      /* Find all A records for this entry and put them into the pool
         list - if any.  */
      memset (&hints, 0, sizeof (hints));
      hints.ai_socktype = SOCK_STREAM;
      if (!getaddrinfo (name, NULL, &hints, &aibuf))
        {
          for (ai = aibuf; ai; ai = ai->ai_next)
            {
              char tmphost[NI_MAXHOST];
              int tmpidx;
              int ec;
              int i;

              if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6)
                continue;

              log_printhex ("getaddrinfo returned", ai->ai_addr,ai->ai_addrlen);
              if ((ec=getnameinfo (ai->ai_addr, ai->ai_addrlen,
                                   tmphost, sizeof tmphost,
                                   NULL, 0, NI_NAMEREQD)))
                log_info ("getnameinfo failed while checking '%s': %s\n",
                          name, gai_strerror (ec));
              else if (refidx+1 >= reftblsize)
                {
                  log_error ("getnameinfo returned for '%s': '%s'"
                            " [index table full - ignored]\n", name, tmphost);
                }
              else
                {

                  if ((tmpidx = find_hostinfo (tmphost)) != -1)
                    {
                      log_info ("getnameinfo returned for '%s': '%s'"
                                " [already known]\n", name, tmphost);
                      if (ai->ai_family == AF_INET)
                        hosttable[tmpidx]->v4 = 1;
                      if (ai->ai_family == AF_INET6)
                        hosttable[tmpidx]->v6 = 1;

                      for (i=0; i < refidx; i++)
                        if (reftbl[i] == tmpidx)
                      break;
                      if (!(i < refidx) && tmpidx != idx)
                        reftbl[refidx++] = tmpidx;
                    }
                  else
                    {
                      log_info ("getnameinfo returned for '%s': '%s'\n",
                                name, tmphost);
                      /* Create a new entry.  */
                      tmpidx = create_new_hostinfo (tmphost);
                      if (tmpidx == -1)
                        log_error ("map_host for '%s' problem: %s - '%s'"
                                   " [ignored]\n",
                                   name, strerror (errno), tmphost);
                      else
                        {
                          if (ai->ai_family == AF_INET)
                            hosttable[tmpidx]->v4 = 1;
                          if (ai->ai_family == AF_INET6)
                            hosttable[tmpidx]->v6 = 1;

                          for (i=0; i < refidx; i++)
                            if (reftbl[i] == tmpidx)
                              break;
                          if (!(i < refidx) && tmpidx != idx)
                            reftbl[refidx++] = tmpidx;
                        }
                    }
                }
            }
        }
      reftbl[refidx] = -1;
      if (refidx)
        {
          assert (!hi->pool);
          hi->pool = xtryrealloc (reftbl, (refidx+1) * sizeof *reftbl);
          if (!hi->pool)
            {
              log_error ("shrinking index table in map_host failed: %s\n",
                         strerror (errno));
              xfree (reftbl);
            }
          qsort (reftbl, refidx, sizeof *reftbl, sort_hostpool);
        }
      else
        xfree (reftbl);
    }

  hi = hosttable[idx];
  if (hi->pool)
    {
      /* If the currently selected host is now marked dead, force a
         re-selection .  */
      if (hi->poolidx >= 0 && hi->poolidx < hosttable_size
          && hosttable[hi->poolidx] && hosttable[hi->poolidx]->dead)
        hi->poolidx = -1;

      /* Select a host if needed.  */
      if (hi->poolidx == -1)
        {
          hi->poolidx = select_random_host (hi->pool);
          if (hi->poolidx == -1)
            {
              log_error ("no alive host found in pool '%s'\n", name);
              return NULL;
            }
        }

      assert (hi->poolidx >= 0 && hi->poolidx < hosttable_size);
      hi = hosttable[hi->poolidx];
      assert (hi);
    }

  if (hi->dead)
    {
      log_error ("host '%s' marked as dead\n", hi->name);
      return NULL;
    }

  return xtrystrdup (hi->name);
}