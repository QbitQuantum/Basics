/* queries the ldap server for account..
 * if a single account match is found, 
 * email is allocated and set to the email address
 * and returns LDAP_SUCCESS. returns LDAP_OTHER if
 * 0 or 2+ entries are matched, or the proper ldap error
 * code for other errors.
 */ 
int ldap_get_user_info(const char *account, char **email) 
{
    int rc;
    struct berval **value;
    LDAPMessage *entry, *res;
    if(email)
      *email = NULL;
    if( (rc = ldap_search_user(account, &res)) == LDAP_SUCCESS) {
        entry = ldap_first_entry(ld, res);
        value = ldap_get_values_len(ld, entry, nickserv_conf.ldap_field_email);
        if(!value) {
           return(LDAP_OTHER);
        }
        if(email)
          *email = strdup(value[0]->bv_val);
        log_module(MAIN_LOG, LOG_DEBUG, "%s: %s\n", nickserv_conf.ldap_field_email, value[0]->bv_val);
        ldap_value_free_len(value);
        /*
        value = ldap_get_values(ld, entry, "description");
        log_module(MAIN_LOG, LOG_DEBUG, "Description: %s\n", value[0]);
        value = ldap_get_values(ld, entry, "userPassword");
        log_module(MAIN_LOG, LOG_DEBUG, "pass: %s\n", value ? value[0] : "error");
        */
    }
    return(rc);
}