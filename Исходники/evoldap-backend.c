static char *
get_variable (const char  *varname,
	      LDAP        *connection,
	      LDAPMessage *entry)
{
  BerElement *berptr;
  const char *attr;
  char       *retval;

  if (strcmp (varname, "USER") == 0)
    return g_strdup (g_get_user_name ());

  if (strcmp (varname, "EVOLUTION_UID") == 0)
    return get_evolution_uid ();

  if (connection == NULL || entry == NULL)
    return g_strdup ("");

  if (strncmp (varname, "LDAP_ATTR_", 10) != 0)
    return g_strdup ("");

  varname += 10;

  retval = NULL;

  berptr = NULL;
  attr = ldap_first_attribute (connection, entry, &berptr);
  while (attr != NULL && retval == NULL)
    {
      struct berval **values;

      if (strcmp (attr, varname) == 0)
	{
	  values = ldap_get_values_len (connection, entry, attr);
	  if (values != NULL && values[0] != NULL)
	    retval = g_strdup (values[0]->bv_val);
	  ldap_value_free_len (values);
	}

      attr = ldap_next_attribute (connection, entry, berptr);
    }

  ber_free (berptr, 0);

  return retval ? retval : g_strdup ("");
}