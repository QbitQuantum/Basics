bool Configuration::Load(const char *filename)
{
  bool result = true;
  FILE *fp;
  ConfigGen *config;
  char buffer[MAXPATHLEN] = "";
  char *current = buffer, *endpos, *valpos, *tmppos;
  size_t buflen = 0, curlen = 0, count;

  fp = fopen(filename, "r");
  if( !fp ){
    if( 0 != strcmp(filename, cfg_config_file.Sdefault()) ){
      CONSOLE.Warning(2, "error opening configuration file \"%s\":  %s",
        filename, strerror(errno));
    }
    result = false;
    goto done;
  }
  CONSOLE.Debug("Reading configuration from %s", filename);

  while( true ){
    curlen = buflen - (current - buffer);
    if( 0==curlen || !memchr(current, '\n', curlen) ){
      if( current != buffer ){
        if( curlen ) memmove(buffer, current, curlen);
        current = buffer;
        buflen = curlen;
      }else buflen = 0;
      count = fread(buffer + buflen, 1, sizeof(buffer) - buflen - 1, fp);
      if( 0==count ) break;
      buflen += count;
      buffer[buflen] = '\0';
    }
    while(isspace(*current)) current++;
    if( (endpos = strpbrk(current, "\r\n")) ){
      *endpos = '\0';
      if( *current != '#' && (valpos = strchr(current, '=')) ){
        tmppos = valpos;
        while(isspace(*++valpos));
        while(isspace(*--tmppos));
        *++tmppos = '\0';
        if( (config = CONFIG[current]) ){
          config->Scan(valpos);
          config->Save();
        }else CONSOLE.Debug("Unrecognized tag \"%s\" in config file", current);
      }
      current = endpos + 1;
      if( (size_t)(current - buffer) >= buflen ) continue;
      while(strchr("\r\n", *current)) current++;
    }
  }

  if( fclose(fp) != 0 ){
    CONSOLE.Warning(2, "error closing configuration file \"%s\":  %s",
      filename, strerror(errno));
    result = false;
  }
 done:
  DiskAccess();
  return result;
}