/* Checks the depot status. */
int check_depot_status (LDAP *ldap, char *depotname)
{
  LDAPMessage *entry, *result;
  char	*filter;
  char	**status;
  int	length;

  length = strlen(depotname) + strlen("depotname=") + 1;
  filter = (char *) malloc (length);
  memset(filter, 0, length);
  sprintf(filter, "depotname=%s", depotname);
  
  ldap_search_s (ldap, "ou=depots,o=lbone", LDAP_SCOPE_SUBTREE, filter, NULL, 0, &result);
  entry = ldap_first_entry (ldap, result);
  status = ldap_get_values (ldap, entry, "status");
 
  if (strcmp(status[0], DEPOT_IDLE) == 0) return IDLE;
  if (strcmp(status[0], DEPOT_LOCKED) == 0) return LOCKED;
  return UNAVAIL;
}