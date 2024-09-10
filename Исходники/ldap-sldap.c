static ns_ldap_return_code
__ns_ldap_unmapObjectClasses (ns_ldap_cookie_t * cookie, char **mappedClasses,
			      char ***pOrigClasses)
{
  char **origClasses = NULL;
  int count, i;

  count = ldap_count_values (mappedClasses);
  origClasses = (char **) calloc (count + 1, sizeof (char *));
  if (origClasses == NULL)
    {
      return NS_LDAP_MEMORY;
    }

  for (i = 0; i < count; i++)
    {
      origClasses[i] =
	strdup (_nss_ldap_unmap_oc (cookie->sel, mappedClasses[i]));
      if (origClasses[i] == NULL)
	{
	  ldap_value_free (origClasses);
	  return NS_LDAP_MEMORY;
	}
    }
  origClasses[i] = NULL;
  *pOrigClasses = origClasses;

  return NS_LDAP_SUCCESS;
}