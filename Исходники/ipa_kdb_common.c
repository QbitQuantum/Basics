int ipadb_ldap_attr_to_int(LDAP *lcontext, LDAPMessage *le,
                           char *attrname, int *result)
{
    struct berval **vals;
    int ret = ENOENT;

    vals = ldap_get_values_len(lcontext, le, attrname);
    if (vals) {
        *result = atoi(vals[0]->bv_val);
        ret = 0;
        ldap_value_free_len(vals);
    }

    return ret;
}