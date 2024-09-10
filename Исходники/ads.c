static char *get_attr_value(LDAP *ld, LDAPMessage *m, char *attr)
{
   char **vals;
   char *val = NULL;
   if (vals = ldap_get_values(ld, m, attr)) {
      // syslog(LOG_DEBUG, "ldap val %s: %s\n", attr, vals[0] );
      val = strdup(vals[0]);
      ldap_value_free( vals );
   }
   return (val);
}