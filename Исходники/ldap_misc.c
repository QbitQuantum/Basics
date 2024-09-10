/* Extract a name from policy_dn, which must be directly under the realm
 * container. */
krb5_error_code
krb5_ldap_policydn_to_name(krb5_context context, const char *policy_dn,
                           char **name_out)
{
    size_t len1, len2, plen;
    krb5_error_code ret;
    kdb5_dal_handle *dal_handle;
    krb5_ldap_context *ldap_context;
    const char *realmdn;

    *name_out = NULL;
    SETUP_CONTEXT();

    realmdn = ldap_context->lrparams->realmdn;
    if (realmdn == NULL)
        return EINVAL;

    /* policyn_dn should be "cn=<policyname>,<realmdn>". */
    len1 = strlen(realmdn);
    len2 = strlen(policy_dn);
    if (len1 == 0 || len2 == 0 || len1 + 1 >= len2)
        return EINVAL;
    plen = len2 - len1 - 1;
    if (policy_dn[plen] != ',' || strcmp(realmdn, policy_dn + plen + 1) != 0)
        return EINVAL;

#if defined HAVE_LDAP_STR2DN
    {
        char *rdn;
        LDAPDN dn;

        rdn = k5memdup0(policy_dn, plen, &ret);
        if (rdn == NULL)
            return ret;
        ret = ldap_str2dn(rdn, &dn, LDAP_DN_FORMAT_LDAPV3 | LDAP_DN_PEDANTIC);
        free(rdn);
        if (ret)
            return EINVAL;
        if (dn[0] == NULL || dn[1] != NULL ||
            dn[0][0]->la_attr.bv_len != 2 ||
            strncasecmp(dn[0][0]->la_attr.bv_val, "cn", 2) != 0) {
            ret = EINVAL;
        } else {
            *name_out = k5memdup0(dn[0][0]->la_value.bv_val,
                                  dn[0][0]->la_value.bv_len, &ret);
        }
        ldap_dnfree(dn);
        return ret;
    }
#elif defined HAVE_LDAP_EXPLODE_DN
    {
        char **parsed_dn;

        /* 1 = return DN components without type prefix */
        parsed_dn = ldap_explode_dn(policy_dn, 1);
        if (parsed_dn == NULL)
            return EINVAL;
        *name_out = strdup(parsed_dn[0]);
        if (*name_out == NULL)
            return ENOMEM;
        ldap_value_free(parsed_dn);
        return 0;
    }
#else
    return EINVAL;
#endif
}