struct ipmipower_connection *
ipmipower_connection_array_create(const char *hostname, unsigned int *len) 
{
  char *str = NULL;
  int index = 0;
  hostlist_t hl = NULL;
  hostlist_iterator_t itr = NULL;
  struct ipmipower_connection *ics;
  int size = sizeof(struct ipmipower_connection);
  int hl_count;
  int errcount = 0;
  int emfilecount = 0;

  assert(hostname && len); 

  *len = 0;
  
  if (!(hl = hostlist_create(hostname)))
    {
      ipmipower_output(MSG_TYPE_HOSTNAME_INVALID, hostname);
      return NULL;
    }
  
  if (!(itr = hostlist_iterator_create(hl)))
    ierr_exit("hostlist_iterator_create() error"); 
  
  hostlist_uniq(hl);

  hl_count = hostlist_count(hl);

  ics = (struct ipmipower_connection *)Malloc(size * hl_count);
  
  memset(ics, '\0', (size * hl_count));
  
  while ((str = hostlist_next(itr))) 
    {
      ics[index].ipmi_fd = -1;
      ics[index].ping_fd = -1;
      
      /* cleanup only at the end, gather all error outputs for
       * later 
       */
      if (_connection_setup(&ics[index], str) < 0) 
        {
          if (errno == EMFILE && !emfilecount)
            {
              cbuf_printf(ttyout, "file descriptor limit reached\n");
              emfilecount++;
            }
          errcount++;
        }
       
      free(str);
      index++;
    }

  hostlist_iterator_destroy(itr);
  hostlist_destroy(hl);

  if (errcount)
    {
      int i;
      for (i = 0; i < hl_count; i++) 
        {
          close(ics[i].ipmi_fd);
          close(ics[i].ping_fd);
          if (ics[i].ipmi_in)
            cbuf_destroy(ics[i].ipmi_in);
          if (ics[i].ipmi_out)
            cbuf_destroy(ics[i].ipmi_out);
          if (ics[i].ping_in)
            cbuf_destroy(ics[i].ping_in);
          if (ics[i].ping_out)
            cbuf_destroy(ics[i].ping_out);
        }
      Free(ics);
      return NULL;
    }

  *len = hl_count;
  return ics;
}