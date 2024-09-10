void palIntin( const char * string, int *nstrt,
               long *ireslt, int *jflag ) {

  const char *strstart = NULL; /* Pointer to start of search */
  const char * ctemp = NULL; /* Pointer into string */
  char * endptr = NULL;/* Pointer to string after number */
  int retval;       /* Return value from strtol */
  int hasminus;     /* is this a -0 */

  /* strtol man page indicates that we should reset errno before
     calling strtod */
  errno = 0;

  /* Locate the start postion */
  strstart = &(string[*nstrt-1]);

  /* We have to be able to deal with -0 so we have to search the
     string first and look for the negative */
  hasminus = 0;
  ctemp = strstart;
  while ( ctemp != '\0' ) {
    if (isdigit(*ctemp)) break;
    /* Reset so that - 12345 is not a negative number */
    hasminus = 0;
    /* Flag that we have found a minus */
    if (*ctemp == '-') hasminus = 1;
    ctemp++;
  }

  /* Look for the number using the system call, offsetting using
     1-based counter. */
  retval = strtol( strstart, &endptr, 10 );
  if (retval == 0.0 && endptr == strstart) {
    /* conversion did not find anything */
    *jflag = 1;

    /* but SLA compatibility requires that we step
       through to remove leading spaces. We also step
       through alphabetic characters since they can never
       be numbers. Skip past a "+" since it doesn't gain
       us anything and matches slalib. */
    while (ISBLANK(*endptr) || isalpha(*endptr) || *endptr == '+' ) {
      endptr++;
    }

  } else if ( errno == ERANGE ) {
    *jflag = 2;
  } else {
    if ( retval < 0 || hasminus ) {
      *jflag = -1;
    } else {
      *jflag = 0;
    }
  }

  /* Sort out the position for the next index */
  *nstrt = endptr - string + 1;

  /* Skip a comma */
  if (*endptr == ',') {
    (*nstrt)++;
  } else {
    /* jump past any leading spaces for the next part of the string */
    ctemp = endptr;
    while ( ISBLANK(*ctemp) ) {
      (*nstrt)++;
      ctemp++;
    }
  }

  /* And the result unless we found nothing */
  if (*jflag != 1) *ireslt = retval;

}