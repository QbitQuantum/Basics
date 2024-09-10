/*
 * This function will look in ldap id the token correspond to the
 * requested user. It will returns 0 for failure and 1 for success.
 *
 * For the moment ldaps is not supported. ldap serve can be on a
 * remote host.
 *
 * You need the following parameters in you pam config:
 * ldapserver=  OR ldap_uri=
 * ldapdn=
 * user_attr=
 * yubi_attr=
 *
 */
static char * authorize_user_token_ldap (const char *ldapserver,
			   const char *ldap_uri,
			   const char *ldapdn,
			   const char *user_attr,
			   const char *yubi_attr,
			   const char *user)
{

  DEBUG(("called"));
  int retval = 0;
#ifdef HAVE_LIBLDAP
  LDAP *ld;
  LDAPMessage *result, *e;
  BerElement *ber;
  char *a;

  struct berval **vals;
  int i, rc;

  /* Allocation of memory for search strings depending on input size */
  char *find = malloc((strlen(user_attr)+strlen(ldapdn)+strlen(user)+3)*sizeof(char));
  char *sr = malloc((strlen(yubi_attr)+4)*sizeof(char));

  char sep[2] = ",";
  char eq[2] = "=";
  char sren[4] = "=*)";

  sr[0] = '(';
  sr[1] = '\0';
  find[0]='\0';

  strcat (find, user_attr);
  strcat (find, eq);
  strcat (find, user);
  strcat (find, sep);
  strcat (find, ldapdn);

  strcat (sr, yubi_attr);
  strcat (sr, sren);

  DEBUG(("find: %s",find));
  DEBUG(("sr: %s",sr));

  /* Get a handle to an LDAP connection. */
  if (ldap_uri)
    {
      rc = ldap_initialize (&ld,ldap_uri);
      if (rc != LDAP_SUCCESS)
	{
	  DEBUG (("ldap_init: %s", ldap_err2string (rc)));
	  return NULL;
	}
    }
  else
    {
      if ((ld = ldap_init (ldapserver, PORT_NUMBER)) == NULL)
	{
	  DEBUG (("ldap_init"));
	  return NULL;
	}
    }

  /* Bind anonymously to the LDAP server. */
  rc = ldap_simple_bind_s (ld, NULL, NULL);
  if (rc != LDAP_SUCCESS)
    {
      DEBUG (("ldap_simple_bind_s: %s", ldap_err2string (rc)));
      return NULL;
    }

  /* Search for the entry. */
  DEBUG (("ldap-dn: %s", find));
  DEBUG (("ldap-filter: %s", sr));

  if ((rc = ldap_search_ext_s (ld, find, LDAP_SCOPE_BASE,
			       sr, NULL, 0, NULL, NULL, LDAP_NO_LIMIT,
			       LDAP_NO_LIMIT, &result)) != LDAP_SUCCESS)
    {
      DEBUG (("ldap_search_ext_s: %s", ldap_err2string (rc)));

      return NULL;
    }

  e = ldap_first_entry (ld, result);
  if (e != NULL)
    {

      /* Iterate through each attribute in the entry. */
      for (a = ldap_first_attribute (ld, e, &ber);
	   a != NULL; a = ldap_next_attribute (ld, e, ber))
	{
	  if ((vals = ldap_get_values_len (ld, e, a)) != NULL)
	    {
	      for (i = 0; vals[i] != NULL; i++)
		{
                        return vals[i]->bv_val;
		}
	      ldap_value_free (vals);
	    }
	  ldap_memfree (a);
	}
      if (ber != NULL)
	{
	  ber_free (ber, 0);
	}

    }

  ldap_msgfree (result);
  ldap_unbind (ld);

  /* free memory allocated for search strings */
  free(find);
  free(sr);

#else
  DEBUG (("Trying to use LDAP, but this function is not compiled in pam_yubico!!"));
  DEBUG (("Install libldap-dev and then recompile pam_yubico."));
#endif
  return NULL;
}