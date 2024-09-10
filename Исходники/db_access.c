DB_url_t *DB_decode_url(char *url_string)
{
  static char *routine_name = "DB_decode_url";
  
  static DB_url_t url_struct;
  static int first_time = TRUE;
  
  char *begin_string = url_string;
  char *delim_pos;
  int string_len;
  
  /*
   * Initialize the returned values.
   */

  if (!first_time)
  {
    if (url_struct.protocol != (char *)NULL)
      ufree(url_struct.protocol);

    if (url_struct.translator != (char *)NULL)
      ufree(url_struct.translator);
    
    if (url_struct.param_file != (char *)NULL)
      ufree(url_struct.translator);
    
    if (url_struct.host != (char *)NULL)
      ufree(url_struct.host);
    
    if (url_struct.file != (char *)NULL)
      ufree(url_struct.file);
    
    if (url_struct.args != (char *)NULL)
      ufree(url_struct.args);
  }
  
  first_time = FALSE;

  url_struct.protocol = (char *)NULL;
  url_struct.translator = (char *)NULL;
  url_struct.param_file = (char *)NULL;
  url_struct.host = (char *)NULL;
  url_struct.port = 0;
  url_struct.file = (char *)NULL;
  url_struct.args = (char *)NULL;
  
  /*
   * Pull off the required protocol string.
   */

  if ((delim_pos = strstr(begin_string, DB_PROTO_TRANS_DELIM))
      == (char *)NULL)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't contain protocol/translator delimiter \"%s\"\n",
	    DB_PROTO_TRANS_DELIM);
    
    return((DB_url_t *)NULL);
  }
  
  if (delim_pos == begin_string)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't have a protocol specified\n");
    
    return((DB_url_t *)NULL);
  }
  
  string_len = delim_pos - begin_string + 1;
  url_struct.protocol = (char *)umalloc(string_len);
  STRcopy(url_struct.protocol, begin_string, string_len);
  
  begin_string = delim_pos + strlen(DB_PROTO_TRANS_DELIM);
  
  /*
   * Pull off the optional translator string.
   */

  if ((delim_pos = strstr(begin_string, DB_TRANS_PARAMS_DELIM))
      == (char *)NULL)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't contain translator/params delimiter \"%s\"\n",
	    DB_TRANS_PARAMS_DELIM);
    
    return((DB_url_t *)NULL);
  }
  
  if (delim_pos != begin_string)
  {
    string_len = delim_pos - begin_string + 1;
    url_struct.translator = (char *)umalloc(string_len);
    STRcopy(url_struct.translator, begin_string, string_len);
  }
  
  begin_string = delim_pos + strlen(DB_TRANS_PARAMS_DELIM);
  
  /*
   * Pull off the optional parameter file string.
   */

  if ((delim_pos = strstr(begin_string, DB_PARAMS_HOST_DELIM))
      == (char *)NULL)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't contain params/host delimiter \"%s\"\n",
	    DB_PARAMS_HOST_DELIM);
    
    return((DB_url_t *)NULL);
  }
  
  if (delim_pos != begin_string)
  {
    string_len = delim_pos - begin_string + 1;
    url_struct.param_file = (char *)umalloc(string_len);
    STRcopy(url_struct.param_file, begin_string, string_len);
  }
  
  begin_string = delim_pos + strlen(DB_PARAMS_HOST_DELIM);
  
  /*
   * Pull off the optional host string.
   */

  if ((delim_pos = strstr(begin_string, DB_HOST_PORT_DELIM))
      == (char *)NULL)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't contain host/port delimiter \"%s\"\n",
	    DB_HOST_PORT_DELIM);
    
    return((DB_url_t *)NULL);
  }
  
  if (delim_pos != begin_string)
  {
    string_len = delim_pos - begin_string + 1;
    url_struct.host = (char *)umalloc(string_len);
    STRcopy(url_struct.host, begin_string, string_len);
  }
  
  begin_string = delim_pos + strlen(DB_HOST_PORT_DELIM);
  
  /*
   * Pull off the optional port number.  Need to add error checking
   * for non-numeric in port number.
   */

  if ((delim_pos = strstr(begin_string, DB_PORT_FILE_DELIM))
      == (char *)NULL)
  {
    fprintf(stderr,
	    "ERROR: %s::%s\n", Module_name, routine_name);
    fprintf(stderr,
	    "URL string doesn't contain port/file delimiter \"%s\"\n",
	    DB_PORT_FILE_DELIM);
    
    return((DB_url_t *)NULL);
  }
  
  if (delim_pos != begin_string)
  {
    char port_string[BUFSIZ];
    
    string_len = delim_pos - begin_string + 1;
    STRcopy(port_string, begin_string, string_len);

    url_struct.port = atoi(port_string);
  }
  
  begin_string = delim_pos + strlen(DB_PORT_FILE_DELIM);
  
  /*
   * Pull off the required file string and the optional args
   * string.  Note that the file/args delimiter is optional unless
   * an args string is specified.
   */

  if ((delim_pos = strstr(begin_string, DB_FILE_ARGS_DELIM))
      == (char *)NULL)
  {
    if (strlen(begin_string) <= 0)
    {
      fprintf(stderr,
	      "ERROR: %s::%s\n", Module_name, routine_name);
      fprintf(stderr,
	      "URL doesn't contain required file field\n");
      
      return((DB_url_t *)NULL);
    }
	
    url_struct.file = STRdup(begin_string);
  }
  else
  {
    if (delim_pos == begin_string)
    {
      fprintf(stderr,
	      "ERROR: %s::%s\n", Module_name, routine_name);
      fprintf(stderr,
	      "URL doesn't contain required file field\n");
      
      return((DB_url_t *)NULL);
    }
  
    string_len = delim_pos - begin_string + 1;
    url_struct.file = (char *)umalloc(string_len);
    STRcopy(url_struct.file, begin_string, string_len);
  
    begin_string = delim_pos + strlen(DB_PROTO_TRANS_DELIM);
  
    if (strlen(begin_string) > 0)
      url_struct.args = STRdup(begin_string);
  }
  
  return(&url_struct);
}