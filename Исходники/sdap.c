int sdap_get_msg_dn(TALLOC_CTX *memctx, struct sdap_handle *sh,
                    struct sdap_msg *sm, char **_dn)
{
    char *str;
    int lerrno;
    int ret;

    lerrno = 0;
    ret = ldap_set_option(sh->ldap, LDAP_OPT_RESULT_CODE, &lerrno);
    if (ret != LDAP_OPT_SUCCESS) {
        DEBUG(1, ("ldap_set_option failed [%s], ignored.\n",
                  sss_ldap_err2string(ret)));
    }

    str = ldap_get_dn(sh->ldap, sm->msg);
    if (!str) {
        ldap_get_option(sh->ldap, LDAP_OPT_RESULT_CODE, &lerrno);
        DEBUG(1, ("ldap_get_dn failed: %d(%s)\n",
                  lerrno, sss_ldap_err2string(lerrno)));
        return EIO;
    }

    *_dn = talloc_strdup(memctx, str);
    ldap_memfree(str);
    if (!*_dn) return ENOMEM;

    return EOK;
}