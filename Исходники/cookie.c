struct Cookie *
Curl_cookie_add(struct CookieInfo *c,
                bool httpheader, /* TRUE if HTTP header-style line */
                char *lineptr,   /* first non-space of the line */
                char *domain)    /* default domain */
{
  struct Cookie *clist;
  char what[MAX_COOKIE_LINE];
  char name[MAX_NAME];
  char *ptr;
  char *semiptr;
  struct Cookie *co;
  struct Cookie *lastc=NULL;
  time_t now = time(NULL);
  bool replace_old = FALSE;

  /* First, alloc and init a new struct for it */
  co = (struct Cookie *)malloc(sizeof(struct Cookie));
  if(!co)
    return NULL; /* bail out if we're this low on memory */

  /* clear the whole struct first */
  memset(co, 0, sizeof(struct Cookie));
	    
  if(httpheader) {
    /* This line was read off a HTTP-header */
    char *sep;
    semiptr=strchr(lineptr, ';'); /* first, find a semicolon */
    ptr = lineptr;
    do {
      /* we have a <what>=<this> pair or a 'secure' word here */
      sep = strchr(ptr, '=');
      if(sep && (!semiptr || (semiptr>sep)) ) {
        /*
         * There is a = sign and if there was a semicolon too, which make sure
         * that the semicolon comes _after_ the equal sign.
         */

        name[0]=what[0]=0; /* init the buffers */
        if(1 <= sscanf(ptr, "%" MAX_NAME_TXT "[^;=]=%"
                       MAX_COOKIE_LINE_TXT "[^;\r\n]",
                       name, what)) {
          /* this is a <name>=<what> pair */

          /* Strip off trailing whitespace from the 'what' */
          int len=strlen(what);
          while(len && isspace((int)what[len-1])) {
            what[len-1]=0;
            len--;
          }

          if(strequal("path", name)) {
            co->path=strdup(what);
          }
          else if(strequal("domain", name)) {
            co->domain=strdup(what);
            co->field1= (what[0]=='.')?2:1;
          }
          else if(strequal("version", name)) {
            co->version=strdup(what);
          }
          else if(strequal("max-age", name)) {
            /* Defined in RFC2109:

               Optional.  The Max-Age attribute defines the lifetime of the
               cookie, in seconds.  The delta-seconds value is a decimal non-
               negative integer.  After delta-seconds seconds elapse, the
               client should discard the cookie.  A value of zero means the
               cookie should be discarded immediately.

             */
            co->maxage = strdup(what);
            co->expires =
              atoi((*co->maxage=='\"')?&co->maxage[1]:&co->maxage[0]) + now;
          }
          else if(strequal("expires", name)) {
            co->expirestr=strdup(what);
            co->expires = curl_getdate(what, &now);
          }
          else if(!co->name) {
            co->name = strdup(name);
            co->value = strdup(what);
          }
          /*
            else this is the second (or more) name we don't know
            about! */
        }
        else {
          /* this is an "illegal" <what>=<this> pair */
        }
      }
      else {
        if(sscanf(ptr, "%" MAX_COOKIE_LINE_TXT "[^;\r\n]",
                  what)) {
          if(strequal("secure", what))
            co->secure = TRUE;
          /* else,
             unsupported keyword without assign! */

        }
      }
      if(!semiptr || !*semiptr) {
        /* we already know there are no more cookies */
        semiptr = NULL;
        continue;
      }

      ptr=semiptr+1;
      while(ptr && *ptr && isspace((int)*ptr))
        ptr++;
      semiptr=strchr(ptr, ';'); /* now, find the next semicolon */

      if(!semiptr && *ptr)
        /* There are no more semicolons, but there's a final name=value pair
           coming up */
        semiptr=strchr(ptr, '\0');
    } while(semiptr);

    if(NULL == co->name) {
      /* we didn't get a cookie name, this is an illegal line, bail out */
      if(co->domain)
        free(co->domain);
      if(co->path)
        free(co->path);
      if(co->name)
        free(co->name);
      if(co->value)
        free(co->value);
      free(co);
      return NULL;
    }

    if(NULL == co->domain)
      /* no domain given in the header line, set the default now */
      co->domain=domain?strdup(domain):NULL;
  }
  else {
    /* This line is NOT a HTTP header style line, we do offer support for
       reading the odd netscape cookies-file format here */
    char *firstptr;
    char *tok_buf;
    int fields;

    if(lineptr[0]=='#') {
      /* don't even try the comments */
      free(co);
      return NULL;
    }
    /* strip off the possible end-of-line characters */
    ptr=strchr(lineptr, '\r');
    if(ptr)
      *ptr=0; /* clear it */
    ptr=strchr(lineptr, '\n');
    if(ptr)
      *ptr=0; /* clear it */

    firstptr=strtok_r(lineptr, "\t", &tok_buf); /* first tokenize it on the TAB */

    /* Here's a quick check to eliminate normal HTTP-headers from this */
    if(!firstptr || strchr(firstptr, ':')) {
      free(co);
      return NULL;
    }

    /* Now loop through the fields and init the struct we already have
       allocated */
    for(ptr=firstptr, fields=0; ptr; ptr=strtok_r(NULL, "\t", &tok_buf), fields++) {
      switch(fields) {
      case 0:
        co->domain = strdup(ptr);
        break;
      case 1:
        /* This field got its explanation on the 23rd of May 2001 by
           Andrés García:

           flag: A TRUE/FALSE value indicating if all machines within a given
           domain can access the variable. This value is set automatically by
           the browser, depending on the value you set for the domain.

           As far as I can see, it is set to true when the cookie says
           .domain.com and to false when the domain is complete www.domain.com

           We don't currently take advantage of this knowledge.
        */
        co->field1=strequal(ptr, "TRUE")+1; /* store information */
        break;
      case 2:
        /* It turns out, that sometimes the file format allows the path
           field to remain not filled in, we try to detect this and work
           around it! Andrés García made us aware of this... */
        if (strcmp("TRUE", ptr) && strcmp("FALSE", ptr)) {
          /* only if the path doesn't look like a boolean option! */
          co->path = strdup(ptr);
          break;
        }
        /* this doesn't look like a path, make one up! */
        co->path = strdup("/");
        fields++; /* add a field and fall down to secure */
        /* FALLTHROUGH */
      case 3:
        co->secure = strequal(ptr, "TRUE");
        break;
      case 4:
        co->expires = atoi(ptr);
        break;
      case 5:
        co->name = strdup(ptr);
        break;
      case 6:
        co->value = strdup(ptr);
        break;
      }
    }

    if(7 != fields) {
      /* we did not find the sufficient number of fields to recognize this
         as a valid line, abort and go home */

      if(co->domain)
        free(co->domain);
      if(co->path)
        free(co->path);
      if(co->name)
        free(co->name);
      if(co->value)
        free(co->value);

      free(co);
      return NULL;
    }

  }

  co->livecookie = c->running;

  /* now, we have parsed the incoming line, we must now check if this
     superceeds an already existing cookie, which it may if the previous have
     the same domain and path as this */

  clist = c->cookies;
  replace_old = FALSE;
  while(clist) {
    if(strequal(clist->name, co->name)) {
      /* the names are identical */

      if(clist->domain && co->domain) {
        if(strequal(clist->domain, co->domain))
          replace_old=TRUE;
      }
      else if(!clist->domain && !co->domain)
        replace_old = TRUE;

      if(replace_old) {
        /* the domains were identical */

        if(clist->path && co->path) {
          if(strequal(clist->path, co->path)) {
            replace_old = TRUE;
          }
          else
            replace_old = FALSE;
        }
        else if(!clist->path && !co->path)
          replace_old = TRUE;
        else
          replace_old = FALSE;
        
      }

      if(replace_old && !co->livecookie && clist->livecookie) {
        /* Both cookies matched fine, except that the already present
           cookie is "live", which means it was set from a header, while
           the new one isn't "live" and thus only read from a file. We let
           live cookies stay alive */

        /* Free the newcomer and get out of here! */
        if(co->domain)
          free(co->domain);
        if(co->path)
          free(co->path);
        if(co->name)
          free(co->name);
        if(co->value)
          free(co->value);

        free(co);
        return NULL;
      }

      if(replace_old) {
        co->next = clist->next; /* get the next-pointer first */

        /* then free all the old pointers */
        if(clist->name)
          free(clist->name);
        if(clist->value)
          free(clist->value);
        if(clist->domain)
          free(clist->domain);
        if(clist->path)
          free(clist->path);
        if(clist->expirestr)
          free(clist->expirestr);

        if(clist->version)
          free(clist->version);
        if(clist->maxage)
          free(clist->maxage);

        *clist = *co;  /* then store all the new data */

        free(co);   /* free the newly alloced memory */
        co = clist; /* point to the previous struct instead */

        /* We have replaced a cookie, now skip the rest of the list but
           make sure the 'lastc' pointer is properly set */
        do {
          lastc = clist;
          clist = clist->next;
        } while(clist);
        break;
      }
    }
    lastc = clist;
    clist = clist->next;
  }

  if(!replace_old) {
    /* then make the last item point on this new one */
    if(lastc)
      lastc->next = co;
    else
      c->cookies = co;
  }

  c->numcookies++; /* one more cookie in the jar */

  return co;
}