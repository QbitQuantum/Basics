void *
thread_read_write (void *arg)
{
  struct thread_info *info = (struct thread_info *) arg;
  int i, ret;
  int id, fd;

  /* for request */
  u_int32_t reqx, reqy;
  unsigned long boffset, nblock;
  struct sockaddr_in *serv_addr;
  struct key_request_packet kreq;

  /* for read */
  u_int32_t resx, resy;
  struct sockaddr_in addr;
  socklen_t addrlen;
  struct key_response_packet kresp;
  int kresperr, krespsuberr, krespkeylen;

  struct timeval start, end, res;
  double time;
  int success;
  unsigned long send_count, read_count;

  id = info->id;

  memset (&info->stats, 0, sizeof (struct horus_stats));
  send_count = read_count = 0;

  fd = socket (PF_INET, SOCK_DGRAM, 0);
  if (fd < 0)
    {
      printf ("thread[%d]: Unable to open socket!: %s\n",
              id, strerror (errno));
      return NULL;
    }

  serv_addr = info->serv_addr;
  boffset = info->boffset;
  nblock = info->nblock;
  memset (&kreq, 0, sizeof (kreq));

  reqx = info->level;
  kreq.x = htonl (reqx);
  strncpy (kreq.filename, info->filename, sizeof (kreq.filename));

  if (benchmark || horus_verbose)
    printf ("thread[%d]: server %s:%d bsize %d boffset %lu nblock %lu\n",
            id, info->server, ntohs (serv_addr->sin_port),
            HORUS_BLOCK_SIZE, boffset, nblock);

  if (spinwait)
    {
      fcntl (fd, F_SETFL, O_NONBLOCK);
      printf ("thread[%d]: spinwait: usleep %d nanosleep %ld "
              "nsend %d nread %d\n",
              id, useconds, nanoseconds, nsend, nread);
    }

  if (benchmark)
    gettimeofday (&start, NULL);

  for (i = 0; i < nblock; i++)
    {
      reqy = boffset + i;
      kreq.y = htonl (reqy);

      success = 0;
      send_count = nsend;
      do {
          ret = sendto (fd, &kreq, sizeof (key_request_packet), 0,
                        (struct sockaddr *) serv_addr,
                        sizeof (struct sockaddr_in));
          send_count--;
          if (ret != sizeof (key_request_packet))
            {
              if (horus_debug)
                printf ("thread[%d]: sendto(): failed: %d "
                        "send_count: %ld\n", id, ret, send_count);
              info->stats.sendfail++;
              continue;
            }
          else
            {
              if (horus_debug)
                printf ("thread[%d]: request %d,%d send_count: %ld\n",
                        id, reqx, reqy, send_count);
            }

          read_count = nread;
          do {
              if (spinwait)
                {
                  if (useconds)
                    usleep (useconds);
                  if (nanoseconds)
                    {
                      struct timespec nanospec;
                      nanospec.tv_sec = 0;
                      nanospec.tv_nsec = nanoseconds;
                      nanosleep (&nanospec, NULL);
                    }
                }

              addrlen = sizeof (struct sockaddr_in);
              ret = recvfrom (fd, &kresp, sizeof (key_response_packet), 0,
                              (struct sockaddr *) &addr, &addrlen);
              read_count--;
              if (ret != sizeof (key_response_packet))
                {
                  if (horus_debug)
                    printf ("thread[%d]: recvfrom(): failed: %d "
                            "read_count: %ld\n", id, ret, read_count);
                  info->stats.recvfail++;
                  continue;
                }
              else
                {
                  if (horus_debug)
                    printf ("thread[%d]: recvfrom(): received %d\n", id, ret);

                  resx = ntohl (kresp.x);
                  resy = ntohl (kresp.y);

                  if (resx == reqx && resy == reqy)
                    success++;
                  else
                    {
                      if (horus_debug)
                        printf ("thread[%d]: mismatch: "
                                "req: %d,%d: resp: %d,%d\n",
                                id, reqx, reqy, resx, resy);
                      info->stats.resmismatch++;
                    }
                }
          } while (! success && read_count > 0);
      } while (! success && send_count > 0);

      info->stats.sendretry += nsend - send_count - 1;
      info->stats.recvretry += nread - read_count - 1;

      if (! success)
        {
          if (horus_verbose)
            printf ("thread[%d]: give up K_%d,%d: resend: %lu reread: %lu\n",
                    id, reqx, reqy, send_count, read_count);
          info->stats.giveup++;
          continue;
        }
      info->stats.success++;

      kresperr = (int) ntohs (kresp.err);
      krespsuberr = (int) ntohs (kresp.suberr);
      krespkeylen = (int) ntohl (kresp.key_len);
      horus_stats_record (&info->stats, kresperr, krespsuberr);

      if (horus_verbose && ! benchmark)
        {
          if (kresperr)
            printf ("thread[%d]: err = %d : %s\n", id,
                    kresperr, horus_strerror (kresperr));
          if (krespsuberr)
            printf ("thread[%d]: suberr = %d : %s\n", id,
                    krespsuberr, strerror (krespsuberr));
          if (! kresperr)
            printf ("thread[%d]: key_%d,%d: key_%d,%d/%d = %s\n", id,
                    reqx, reqy, resx, resy, krespkeylen,
                    print_key (kresp.key, krespkeylen));
        }

      if (simulate && ! kresperr)
        {
          char key[HORUS_MAX_KEY_LEN];
          size_t key_len;
          int simx, simy;
          unsigned long sboffset, snblock;
          u_int32_t *kht_block_size;
          int j;

          assert (reqx == resx && reqy == resy);
          simx = info->leaf_level;
          kht_block_size = info->kht_block_size;

          sboffset = resy * (kht_block_size[resx] / kht_block_size[simx]);
          snblock = kht_block_size[resx];

          if (resx == info->leaf_level)
            {
              info->stats.keycalculated = info->stats.success;
            }
          else
            {
              for (j = 0; j < snblock; j++)
                {
                  simy = sboffset + j;
                  key_len = sizeof (key);
                  horus_block_key (key, &key_len, simx, simy,
                                   kresp.key, krespkeylen, resx, resy,
                                   kht_block_size);
                  info->stats.keycalculated++;
                  if (horus_verbose && ! benchmark)
                    printf ("thread[%d]: simulated: K_%d,%d = %s\n", id,
                            simx, simy, print_key (key, key_len));
                }
            }
        }
    }

  if (benchmark)
    gettimeofday (&end, NULL);

  close (fd);

  if (benchmark)
    {
      timeval_sub (&end, &start, &res);
      time = res.tv_sec + res.tv_usec * 0.000001;
      info->timeval = res;
      printf ("thread[%d]: %llu/%lu keys in %f secs ( %f q/s\n",
              id, info->stats.success, nblock, time, info->stats.success/time);
      if (simulate)
        printf ("thread[%d]: %llu keys calculated in %f secs ( %f q/s\n",
                id, info->stats.keycalculated, time,
                info->stats.keycalculated/time);
    }
  else if (horus_verbose)
    {
      printf ("thread[%d]: %llu/%lu keys processed.\n",
              id, info->stats.success, nblock);
      if (simulate)
        printf ("thread[%d]: %llu keys calculated\n",
                id, info->stats.keycalculated);
    }

  return NULL;
}