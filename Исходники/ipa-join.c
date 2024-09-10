/*
 * Get the certificate subject base from the IPA configuration.
 *
 * Not considered a show-stopper if this fails for some reason.
 *
 * The caller is responsible for binding/unbinding to LDAP.
 */
static int
get_subject(LDAP *ld, char *ldap_base, const char **subject, int quiet)
{
    char *attrs[] = {"ipaCertificateSubjectBase", NULL};
    char *base = NULL;
    LDAPMessage *entry, *res = NULL;
    struct berval **ncvals;
    int ret, rval = 0;

    ret = asprintf(&base, "cn=ipaconfig,cn=etc,%s", ldap_base);
    if (ret == -1)
    {
        if (!quiet)
            fprintf(stderr, _("Out of memory!\n"));
        rval = 3;
        goto done;
    }

    ret = ldap_search_ext_s(ld, base, LDAP_SCOPE_BASE,
                            "objectclass=*", attrs, 0,
                            NULL, NULL, NULL, 0, &res);

    if (ret != LDAP_SUCCESS) {
        fprintf(stderr,
                _("Search for ipaCertificateSubjectBase failed with error %d"),
                ret);
        rval = 14;
        goto done;
    }

    entry = ldap_first_entry(ld, res);
    ncvals = ldap_get_values_len(ld, entry, attrs[0]);
    if (!ncvals) {
        fprintf(stderr, _("No values for %s"), attrs[0]);
        rval = 14;
        goto done;
    }

    *subject = strdup(ncvals[0]->bv_val);

    ldap_value_free_len(ncvals);

done:
    free(base);
    if (res) ldap_msgfree(res);

    return rval;
}