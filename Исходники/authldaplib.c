/*
 * Function: copy_value
 *   Copy value from a LDAP attribute to $copy
 * INPUT:
 *   $ld:       the connection with the LDAP server
 *   $entry:    the entry who contains attributes
 *   $attribut: this attribut
 *   $copy:     where data can go
 * OUTPUT:
 *   void
 */
static void copy_value(LDAP *ld, LDAPMessage *entry, const char *attribut,
	char **copy, const char *username)
{
  char ** values;
  values=ldap_get_values(ld,entry, (char *)attribut);

	if (values==NULL)
	{
#ifdef HAVE_LDAP_RESULT2ERROR
	  int ld_errno = ldap_result2error(ld,entry,0);
	  if (ld_errno && ld_errno != LDAP_DECODING_ERROR)
	    /* We didn't ask for this attribute */
	    ldap_perror(ld,"ldap_get_values");
#else
		if (ld->ld_errno != LDAP_DECODING_ERROR)
			/* We didn't ask for this attribute */
			ldap_perror(ld,"ldap_get_values");
#endif
		*copy=NULL;
		return;
	}
  /* We accept only attribute with one value */
	else if (ldap_count_values(values)>1)
	 {
		 *copy=strdup(values[0]);
		 syslog(LOG_DAEMON,
			"authldaplib: duplicate attribute %s for %s\n",
			attribut,
			username);
		 *copy=NULL;
	 }
  /* We accept only attribute with one value */
	else if (ldap_count_values(values)!=1)
	 {
		 *copy=NULL;
	 }
  else
	 {
		 *copy=strdup(values[0]);
	 }
#if DEBUG_LDAP
  syslog(LOG_DAEMON|LOG_CRIT,"copy_value %s: %s\n",attribut,values[0]);
#endif
  ldap_value_free(values);
}