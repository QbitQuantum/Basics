/** entry-point function for following referrals, required in some cases by Active Directory */
static int rebindProc(LDAP *ld, LDAP_CONST char *url, ber_tag_t request, ber_int_t msgid, void *mdata)
{
    drvdata_t data = mdata;
    data->ld = ld;
    if(ldap_simple_bind_s(data->ld, data->binddn, data->bindpw)) {
        log_debug(ZONE, "ldapvcard: bind failed (to %s): %s", url, ldap_err2string(_ldap_get_lderrno(data->ld)));
        ldap_unbind_s(data->ld);
        data->ld = NULL;
        return LDAP_INAPPROPRIATE_AUTH;
    }

    return LDAP_SUCCESS;
}