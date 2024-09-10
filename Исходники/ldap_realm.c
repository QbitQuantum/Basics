krb5_error_code
krb5_ldap_create_krbcontainer(krb5_context context,
                              const
                              krb5_ldap_krbcontainer_params *krbcontparams)
{
    LDAP                        *ld=NULL;
    char                        *strval[2]={NULL}, *kerberoscontdn=NULL, **rdns=NULL;
    int                         pmask=0;
    LDAPMod                     **mods = NULL;
    krb5_error_code             st=0;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;

    SETUP_CONTEXT ();

    /* get ldap handle */
    GET_HANDLE ();

    if (krbcontparams != NULL && krbcontparams->DN != NULL) {
        kerberoscontdn = krbcontparams->DN;
    } else {
        st = EINVAL;
        krb5_set_error_message(context, st,
                               _("Kerberos Container information is missing"));
        goto cleanup;
    }

    strval[0] = "krbContainer";
    strval[1] = NULL;
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "objectclass", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    rdns = ldap_explode_dn(kerberoscontdn, 1);
    if (rdns == NULL) {
        st = EINVAL;
        krb5_set_error_message(context, st,
                               _("Invalid Kerberos container DN"));
        goto cleanup;
    }

    strval[0] = rdns[0];
    strval[1] = NULL;
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "cn", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    /* check if the policy reference value exists and is of krbticketpolicyreference object class */
    if (krbcontparams && krbcontparams->policyreference) {
        st = checkattributevalue(ld, krbcontparams->policyreference, "objectclass", policyclass,
                                 &pmask);
        CHECK_CLASS_VALIDITY(st, pmask, _("ticket policy object value: "));

        strval[0] = krbcontparams->policyreference;
        strval[1] = NULL;
        if ((st=krb5_add_str_mem_ldap_mod(&mods, "krbticketpolicyreference", LDAP_MOD_ADD,
                                          strval)) != 0)
            goto cleanup;
    }

    /* create the kerberos container */
    if ((st = ldap_add_ext_s(ld, kerberoscontdn, mods, NULL, NULL)) != LDAP_SUCCESS) {
        int ost = st;
        st = translate_ldap_error (st, OP_ADD);
        krb5_set_error_message(context, st,
                               _("Kerberos Container create FAILED: %s"),
                               ldap_err2string(ost));
        goto cleanup;
    }

cleanup:

    if (rdns)
        ldap_value_free (rdns);

    ldap_mods_free(mods, 1);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return(st);
}