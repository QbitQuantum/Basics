abook_fielddata *
abook_ldap_fetch(char *alias, int *count)
{
  int i, rc, ldapcount, mappedfieldcount;
  char *ptr;
  char prefix[1024];
  char filter[1024];
  abook_fielddata *fdata, *fptr;
  char *searchattr;
  char *searchkey;
  LDAP *ld;
  LDAPMessage *results, *entry;
  char **values;
  
  if (config_ldap() < 0) {
    syslog(LOG_ERR, "abook_ldap_fetch: failed to configure LDAP");
    return NULL;
  }
  
  /*
   * Decide how to search for the user.
   */
  
  snprintf(prefix, sizeof(prefix), "[%s:", config.uniqueattr);
  ptr = strstr(alias, prefix);
  if (ptr != NULL) {
    *ptr = '\0';
    ptr += 1 /*[*/ + strlen(config.uniqueattr) + 1 /*:*/;
    searchkey = ptr;
    ptr += strlen(ptr) - 1 /*]*/;
    *ptr = '\0';
    searchattr = config.uniqueattr;
  } else {
    searchkey  = alias;
    searchattr = config.fullnameattr;
  }
  snprintf(filter, sizeof(filter), "(&%s(%s=%s))", config.defaultfilter, 
	  searchattr, searchkey);
  
  ld = ldap_init(config.ldaphost, config.ldapport);
  if (ld == NULL) {
    syslog(LOG_ERR, "abook_ldap_fetch: LDAP init failed: %s",
	   strerror(errno));
    return NULL;
  }
  
  rc = ldap_simple_bind_s(ld, NULL, NULL);
  if (rc != LDAP_SUCCESS) {
    syslog(LOG_ERR, "abook_ldap_fetch: simple bind failed: %s",
	   ldap_err2string(rc));
    return NULL;
  }
  
  rc = ldap_search_s(ld, config.searchbase, config.scope, filter, 
		     NULL/*get all attrs*/, 0/*attrs-only*/, &results);
  if (rc != LDAP_SUCCESS) {
    syslog(LOG_ERR, "abook_ldap_fetch: LDAP search failed: %s",
	   ldap_err2string(rc));
    ldap_unbind(ld);
    return NULL;
    }
  
  ldapcount = ldap_count_entries(ld, results);

  if (ldapcount == 0) {
    /* no matches on primary search, try secondary search if configured */
    
    if (secondaryconfig.ldaphost) {
      
      /* close the connection to the primary server */
      ldap_unbind(ld);

      snprintf(prefix, sizeof(prefix), "[%s:", secondaryconfig.uniqueattr);
      ptr = strstr(alias, prefix);
      if (ptr != NULL) {
	*ptr = '\0';
	ptr += 1 /*[*/ + strlen(secondaryconfig.uniqueattr) + 1 /*:*/;
	searchkey = ptr;
	ptr += strlen(ptr) - 1 /*]*/;
	*ptr = '\0';
	searchattr = secondaryconfig.uniqueattr;
      } else {
	searchkey  = alias;
	searchattr = secondaryconfig.fullnameattr;
      }
      snprintf(filter, sizeof(filter), "(&%s(%s=%s))", secondaryconfig.defaultfilter, 
	      searchattr, searchkey);
      
      ld=ldap_init(secondaryconfig.ldaphost, secondaryconfig.ldapport);
      if (ld == NULL){
	syslog(LOG_ERR, "abook_ldap_fetch: LDAP secondary init failed: %s",
	       strerror(errno));
	return NULL;
      }
      
      rc = ldap_simple_bind_s(ld, NULL, NULL);
      if (rc != LDAP_SUCCESS) {
	syslog(LOG_ERR, "abook_ldap_fetch: simple secondary bind failed: %s",
	       ldap_err2string(rc));
	return NULL;
      }
      
      rc = ldap_search_s(ld, secondaryconfig.searchbase, secondaryconfig.scope, filter, 
			 NULL/*get all attrs*/, 0/*attrs-only*/, &results);
      
      if (rc != LDAP_SUCCESS) {
	syslog(LOG_ERR, "abook_ldap_fetch: LDAP secondary search failed: %s",
	       ldap_err2string(rc));
	ldap_unbind(ld);
	return NULL;
      }
      
      ldapcount = ldap_count_entries(ld, results);
      
      if (ldapcount != 1) {
	syslog(LOG_ERR, "abook_ldap_fetch: unexpected count of secondary search"
	       " hits: %d", ldapcount);
	(void) ldap_msgfree(results);  /* ignore message type return value */
	ldap_unbind(ld);
	return NULL;
      }	       
      
      entry = ldap_first_entry(ld, results);
      if (entry == NULL) {
	  syslog(LOG_ERR, "abook_ldap_fetch: ldap_first_entry failed");
	  (void) ldap_msgfree(results);  /* ignore message type return value */
	  ldap_unbind(ld);
	  return NULL;
      }
      
      /* This memory is freed by abook_fetchdone() which is called by 
       * show_address() after it's finished sending the field/data pairs 
       * back to the IMSP client
       */
      
      mappedfieldcount = 0;
      for (i = 0; secondaryconfig.map[i].field != NULL; i++) {
	if (secondaryconfig.map[i].attr != NULL)
	  mappedfieldcount++;
      }
      
      fdata = (abook_fielddata *) 
	malloc(sizeof (abook_fielddata) * mappedfieldcount);
      if (fdata == NULL) {
	syslog(LOG_ERR, "abook_ldap_fetch: Out of memory");
	(void) ldap_msgfree(results);  /* ignore message type return value */
	ldap_unbind(ld);
	return NULL;
      }
      
      *count = 0;
      fptr = fdata;
      
      for (i = 0; secondaryconfig.map[i].field != NULL; i++) {
	if ((secondaryconfig.map[i].attr != NULL) &&
	    (strcmp(secondaryconfig.map[i].attr, secondaryconfig.fullnameattr) != 0)) {
	  values = ldap_get_values(ld, entry, secondaryconfig.map[i].attr);
	  if (values != NULL && values[0] != NULL) {
	    fptr->field = strdup(secondaryconfig.map[i].field);
	    if (secondaryconfig.map[i].append != NULL) {
	      int fptrdatalen = strlen(values[0])+strlen(secondaryconfig.map[i].append)+1;
	      fptr->data=malloc(fptrdatalen);
	      if(!fptr->data) fatal("out of memory", EC_TEMPFAIL);
	      strlcpy(fptr->data, values[0], fptrdatalen);
	      strlcat(fptr->data, secondaryconfig.map[i].append, fptrdatalen);
	    } else {
	      fptr->data  = strdup(values[0]);
	      if(!fptr->data) fatal("out of memory", EC_TEMPFAIL);
	    }
	    (*count)++;
	    fptr++;
	  }
	  if (values != NULL)
	    ldap_value_free(values);
	}
      }
      
      (void) ldap_msgfree(results);  /* ignore message type return value */
      ldap_unbind(ld);
      
      return (fdata);
    }
  }

  if (ldapcount != 1) {
	syslog(LOG_ERR, "abook_ldap_fetch: unexpected count of search"
	       " hits: %d", ldapcount);
	(void) ldap_msgfree(results);  /* ignore message type return value */
	ldap_unbind(ld);
	return NULL;
    }	       

    entry = ldap_first_entry(ld, results);
    if (entry == NULL) {
	syslog(LOG_ERR, "abook_ldap_fetch: ldap_first_entry failed");
	(void) ldap_msgfree(results);  /* ignore message type return value */
	ldap_unbind(ld);
	return NULL;
    }

    /* This memory is freed by abook_fetchdone() which is called by 
     * show_address() after it's finished sending the field/data pairs 
     * back to the IMSP client
     */
    
    mappedfieldcount = 0;
    for (i = 0; config.map[i].field != NULL; i++) {
	if (config.map[i].attr != NULL)
	    mappedfieldcount++;
    }

    fdata = (abook_fielddata *) 
	malloc(sizeof (abook_fielddata) * mappedfieldcount);
    if (fdata == NULL) {
	syslog(LOG_ERR, "abook_ldap_fetch: Out of memory");
	(void) ldap_msgfree(results);  /* ignore message type return value */
	ldap_unbind(ld);
	return NULL;
    }

    *count = 0;
    fptr = fdata;
    
    for (i = 0; config.map[i].field != NULL; i++) {
	if ((config.map[i].attr != NULL) &&
	    (strcmp(config.map[i].attr, config.fullnameattr) != 0)) {
	    values = ldap_get_values(ld, entry, config.map[i].attr);
	    if (values != NULL && values[0] != NULL) {
		fptr->field = strdup(config.map[i].field);
		if (config.map[i].append != NULL) {
		  printf("appending %s to field: %s value: %s\n", config.map[i].append, config.map[i].field,values[0]);

		  fptr->data=malloc(strlen(values[0])+strlen(config.map[i].append)+1);
		  fptr->data=strcat(fptr->data, values[0]);
		  fptr->data=strcat(fptr->data, config.map[i].append);
		} else {
		  fptr->data  = strdup(values[0]);
		}
		(*count)++;
		fptr++;
	    }
	    if (values != NULL)
		ldap_value_free(values);
	}
    }

    (void) ldap_msgfree(results);  /* ignore message type return value */
    ldap_unbind(ld);

    return (fdata);
}