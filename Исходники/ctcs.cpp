int Ctcs::Set_Config(const char *origmsg)
{
  char *msgbuf, *msgptr;
  size_t msglen;

  msglen = strpbrk(origmsg, "\r\n") - origmsg;
  msgbuf = new char[msglen + 1];
  if( !msgbuf ){
    CONSOLE.Warning(1, "error, failed to allocate memory for config");
    return -1;
  }
  strncpy(msgbuf, origmsg, msglen);
  msgbuf[msglen] = '\0';
  msgptr = msgbuf;

  if( m_protocol >= 3 ){
    char *name, *valstr;
    ConfigGen *config;
    if( !(name = strtok(strchr(msgbuf, ' '), " ")) ||
        strlen(name) >= strlen(origmsg) - (name - msgbuf) ){
      goto err;
    }
    valstr = name + strlen(name);
    for( ++valstr; *valstr==' '; valstr++ );

    if( (config = CONFIG[name]) ){
      if( !config->Scan(valstr) ) goto err;
    }else{
      CONSOLE.Warning(2, "Unknown config option %s", name);
      goto err;
    }
  }else{  // m_protocol <= 2
    if( msgptr[9] != '.' ){
      int arg = atoi(msgptr+9);
      cfg_verbose = arg;
    }
    if( msgptr[11] != '.' ) cfg_seed_hours = strtoul(msgptr+11, NULL, 10);
    if( !(msgptr = strchr(msgptr+11, ' ')) ) goto err;
    if( *++msgptr != '.' ) cfg_seed_ratio = atof(msgptr);
    if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
    if( *++msgptr != '.' ) cfg_max_peers = (dt_count_t)atoi(msgptr);
    if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
    if( *++msgptr != '.' ) cfg_min_peers = (dt_count_t)atoi(msgptr);
    if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
    if( *++msgptr != '.' ){
      char *tmp, *p = strchr(msgptr, ' ');
      if( !p ) goto err;
      tmp = new char[p - msgptr + 2 + 1];
      if( !tmp )
        CONSOLE.Warning(1, "error, failed to allocate memory for option");
      else{
        strncpy(tmp, msgptr, p - msgptr);
        tmp[p - msgptr] = '\0';
        strcat(tmp, ",*");  // mock old behavior
      }
      cfg_file_to_download = tmp;
      if( tmp ) delete []tmp;
    }
    if( m_protocol >= 2 ){
      if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
      if( *++msgptr != '.' ){
        cfg_cache_size = atoi(msgptr);
      }
    }
    if( m_protocol == 1 ){
      if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
      ++msgptr;
      // old cfg_exit_zero_peers option
    }
    if( !(msgptr = strchr(msgptr, ' ')) ) goto err;
    if( *++msgptr != '.' ){
      cfg_pause = atoi(msgptr);
    }
  }

  delete []msgbuf;
  return 0;

 err:
  const char *p, *s;
  p = (const char *)memchr(origmsg, '\r', in_buffer.Count());
  s = (const char *)memchr(origmsg, '\n', in_buffer.Count());
  if( p && s > p ) s = p;
  CONSOLE.Warning(2, "Malformed or invalid input from CTCS: %.*s",
    (int)(s - origmsg), origmsg);
  delete []msgbuf;
  return -1;
}