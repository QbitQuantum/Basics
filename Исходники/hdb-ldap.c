static krb5_error_code
LDAP_remove(krb5_context context, HDB * db, hdb_entry * entry)
{
    krb5_error_code ret;
    LDAPMessage *msg, *e;
    char *dn = NULL;
    int rc, limit = LDAP_NO_LIMIT;

    ret = LDAP_principal2message(context, db, entry->principal, &msg);
    if (ret)
	goto out;

    e = ldap_first_entry(HDB2LDAP(db), msg);
    if (e == NULL) {
	ret = HDB_ERR_NOENTRY;
	goto out;
    }

    dn = ldap_get_dn(HDB2LDAP(db), e);
    if (dn == NULL) {
	ret = HDB_ERR_NOENTRY;
	goto out;
    }

    rc = ldap_set_option(HDB2LDAP(db), LDAP_OPT_SIZELIMIT, (const void *)&limit);
    if (rc != LDAP_SUCCESS) {
	krb5_set_error_string(context, "ldap_set_option: %s",
			      ldap_err2string(rc));
	ret = HDB_ERR_BADVERSION;
	goto out;
    }

    rc = ldap_delete_s(HDB2LDAP(db), dn);
    if (check_ldap(context, db, rc)) {
	krb5_set_error_string(context, "ldap_delete_s: %s", 
			      ldap_err2string(rc));
	ret = HDB_ERR_CANT_LOCK_DB;
    } else
	ret = 0;

  out:
    if (dn != NULL)
	free(dn);
    if (msg != NULL)
	ldap_msgfree(msg);

    return ret;
}