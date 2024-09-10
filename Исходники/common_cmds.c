int parse_variable_list(
  job_data_container *dest_hash, /* This is the dest hashmap for vars found */
  job_data_container *user_env,  /* This is the source hashmap */
  int                var_type,  /* Type for vars not pulled from the source hash */
  int                op_type,   /* Op for vars not pulled from the source hash */
  char               *the_list)  /* name=value,name1=value1,etc to be parsed */

  {
  int             alloc_size = 0;
  std::string     job_env = "";
  char            name[JOB_ENV_START_SIZE];
  char           *s = NULL;
  char           *c = NULL;
  char           *delim = NULL;

  s = the_list;

  while (s)
    {
    delim = strpbrk(s, "=,");

    if (delim == s)
      {
      fprintf(stderr, "invalid -v syntax\n");
      return(3);
      }

    /* If delim is ','or NULL we have no value. Get the environment variable in s */ 
    /* If delim is '=' and delim+1 is ',' or NULL we also need to get 
       the environment variable in s */
    if (delim == NULL || *delim == ',' ||
       ((*delim == '=') && (*(delim + 1) == ',')) ||
       ((*delim == '=') && ((delim + 1) == NULL)))
      {
      if (delim == NULL)
        alloc_size = strlen(s);
      else
        alloc_size = delim - s;

      memcpy(name, s, alloc_size);
      name[alloc_size] = '\0';
      c = getenv(name);

      if (c != NULL)
        {
        job_env += name;
        job_env += "=";
        job_env += c;
        if (delim == NULL)
          s = NULL;
        else
          {
          job_env += ",";
          s = delim + 1;
          if (*s == ',') /* This ended in '='. Move one more */
            s++;
          }
        }
      else
        {
        /* No environment variable set for this name. Pass it on with value "" */
        if (delim == NULL)
          {
          snprintf(name, sizeof(name), "%s", s);
          job_env += "name";
          job_env += "=";
          s = NULL;
          }
        else
          {
          memcpy(name, s, delim - s);
          name[delim - s] = '\0';
          job_env += name;
          job_env += "=,";
          s = delim + 1;
          }
        }
      }
    else
      {
      /* We have a key value pair */
      delim = strchr(s, ',');
      if (delim == NULL)
        {
        alloc_size = strlen(s);
        /* we are at the end */
        job_env += s;
        s = NULL;
        }
      else
        {
        /* We have another variable in the list. Take care of the current one */
        alloc_size = delim - s;
        memcpy(name, s, alloc_size);
        name[alloc_size] = '\0';
        job_env += name;
        job_env += ",";
        s = delim + 1;
        }
      }
    }

  hash_add_or_exit(dest_hash, ATTR_v, job_env.c_str(), ENV_DATA);

  return(PBSE_NONE);
  } /* END parse_variable_list() */ 