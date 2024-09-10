static int verify_single_result(LDAP *l, int always_log, char *reason, LDAPMessage *messages)
{
  int rc, erc, num_entries;
  char *errmsg;

  rc = ldap_parse_result(l, messages, &erc, NULL, &errmsg,
			 NULL, NULL, 0);
  if (rc != LDAP_SUCCESS) {
    prtmsg("Failed to %s (parse_result): %s", reason, ldap_err2string(rc));
    return 0;
  }
  if (erc != LDAP_SUCCESS) {
    prtmsg("Failed to %s (server response): %s%s%s", reason, ldap_err2string(erc),
	   (errmsg?", ":""), (errmsg?errmsg:""));
    if (errmsg)
      ldap_memfree(errmsg);
    return 0;
  }
  if (errmsg)
    ldap_memfree(errmsg);
  num_entries=ldap_count_entries(l, messages);
  if (num_entries == 0) {
    if (always_log) 
      prtmsg("Failed to %s (no entries returned)", reason);
    return 0;
  }
  if (num_entries > 1) {
    prtmsg("Failed to %s (too many entries: %d)", reason, num_entries);
    return 0;
  }
  return 1;
}