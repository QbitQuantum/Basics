unsigned long LdapValues::length(void) {
  return ldap_count_values_len(_vals);
}