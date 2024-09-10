static enum nss_status
internal_getgrent_r (ent_t *ent, char *buffer, size_t buflen, const char *user,
		     gid_t group, long int *start, long int *size,
		     gid_t **groupsp, long int limit, int *errnop)
{
  struct parser_data *data = (void *) buffer;
  struct group grpbuf;

  if (!ent->files)
    return getgrent_next_nss (ent, buffer, buflen, user, group,
			      start, size, groupsp, limit, errnop);

  while (1)
    {
      fpos_t pos;
      int parse_res = 0;
      char *p;

      do
	{
	  /* We need at least 3 characters for one line.  */
	  if (__builtin_expect (buflen < 3, 0))
	    {
	    erange:
	      *errnop = ERANGE;
	      return NSS_STATUS_TRYAGAIN;
	    }

	  fgetpos (ent->stream, &pos);
	  buffer[buflen - 1] = '\xff';
	  p = fgets_unlocked (buffer, buflen, ent->stream);
	  if (p == NULL && feof_unlocked (ent->stream))
	    return NSS_STATUS_NOTFOUND;

	  if (p == NULL || __builtin_expect (buffer[buflen - 1] != '\xff', 0))
	    {
	    erange_reset:
	      fsetpos (ent->stream, &pos);
	      goto erange;
	    }

	  /* Terminate the line for any case.  */
	  buffer[buflen - 1] = '\0';

	  /* Skip leading blanks.  */
	  while (isspace (*p))
	    ++p;
	}
      while (*p == '\0' || *p == '#' ||	/* Ignore empty and comment lines. */
	     /* Parse the line.  If it is invalid, loop to
	        get the next line of the file to parse.  */
	     !(parse_res = _nss_files_parse_grent (p, &grpbuf, data, buflen,
						   errnop)));

      if (__builtin_expect (parse_res == -1, 0))
	/* The parser ran out of space.  */
	goto erange_reset;

      if (grpbuf.gr_name[0] != '+' && grpbuf.gr_name[0] != '-')
	/* This is a real entry.  */
	break;

      /* -group */
      if (grpbuf.gr_name[0] == '-' && grpbuf.gr_name[1] != '\0'
	  && grpbuf.gr_name[1] != '@')
	{
	  blacklist_store_name (&grpbuf.gr_name[1], ent);
	  continue;
	}

      /* +group */
      if (grpbuf.gr_name[0] == '+' && grpbuf.gr_name[1] != '\0'
	  && grpbuf.gr_name[1] != '@')
	{
	  if (in_blacklist (&grpbuf.gr_name[1],
			    strlen (&grpbuf.gr_name[1]), ent))
	    continue;
	  /* Store the group in the blacklist for the "+" at the end of
	     /etc/group */
	  blacklist_store_name (&grpbuf.gr_name[1], ent);
	  if (nss_getgrnam_r == NULL)
	    return NSS_STATUS_UNAVAIL;
	  else if (nss_getgrnam_r (&grpbuf.gr_name[1], &grpbuf, buffer,
				   buflen, errnop) != NSS_STATUS_SUCCESS)
	    continue;

	  check_and_add_group (user, group, start, size, groupsp,
			       limit, &grpbuf);

	  return NSS_STATUS_SUCCESS;
	}

      /* +:... */
      if (grpbuf.gr_name[0] == '+' && grpbuf.gr_name[1] == '\0')
	{
	  ent->files = FALSE;
	  return getgrent_next_nss (ent, buffer, buflen, user, group,
				    start, size, groupsp, limit, errnop);
	}
    }

  check_and_add_group (user, group, start, size, groupsp, limit, &grpbuf);

  return NSS_STATUS_SUCCESS;
}