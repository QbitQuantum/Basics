static int ipa_ldap_extended_op(LDAP *ld, const char *reqoid,
                                struct berval *control,
                                LDAPControl ***srvctrl)
{
    struct berval *retdata = NULL;
    LDAPMessage *res = NULL;
    char *retoid = NULL;
    struct timeval tv;
    char *err = NULL;
    int msgid;
    int ret, rc;

    ret = ldap_extended_operation(ld, reqoid, control,
                                  NULL, NULL, &msgid);
    if (ret != LDAP_SUCCESS) {
        fprintf(stderr, _("Operation failed: %s\n"), ldap_err2string(ret));
        return ret;
    }

    /* wait max 100 secs for the answer */
    tv.tv_sec = 100;
    tv.tv_usec = 0;
    ret = ldap_result(ld, msgid, 1, &tv, &res);
    if (ret == -1) {
        fprintf(stderr, _("Failed to get result: %s\n"), ldap_err2string(ret));
        goto done;
    }
    else if (res == NULL) {
        fprintf(stderr, _("Timeout exceeded."));
        goto done;
    }

    ret = ldap_parse_extended_result(ld, res, &retoid, &retdata, 0);
    if (ret != LDAP_SUCCESS) {
        fprintf(stderr, _("Failed to parse extended result: %s\n"),
                        ldap_err2string(ret));
        goto done;
    }

    ret = ldap_parse_result(ld, res, &rc, NULL, &err, NULL, srvctrl, 0);
    if (ret != LDAP_SUCCESS || rc != LDAP_SUCCESS) {
        fprintf(stderr, _("Failed to parse result: %s\n"),
                        err ? err : ldap_err2string(ret));
        if (ret == LDAP_SUCCESS) ret = rc;
        goto done;
    }

done:
    if (err) ldap_memfree(err);
    if (res) ldap_msgfree(res);
    return ret;
}