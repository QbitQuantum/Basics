static
DWORD
VmDnsRpcCreateSrpAuthIdentity(
    PCSTR user,
    PCSTR domain,
    PCSTR password,
    PSTR *retUpn,
    rpc_auth_identity_handle_t *rpc_identity_h
    )
{
    OM_uint32 min = 0;
    OM_uint32 maj = 0;
    const gss_OID_desc gss_srp_password_oid = { GSSAPI_SRP_CRED_OPT_PW_LEN,
                                                (void *) GSSAPI_SRP_CRED_OPT_PW};
    const gss_OID_desc spnego_mech_oid = { SPNEGO_OID_LENGTH, (void *)SPNEGO_OID };
    gss_buffer_desc name_buf = { 0 };
    gss_name_t gss_name_buf = NULL;
    gss_buffer_desc gss_pwd = { 0 };
    size_t upn_len = 0;
    char *upn = NULL;
    gss_cred_id_t cred_handle = NULL;
    gss_OID_desc mech_oid_array[1];
    gss_OID_set_desc desired_mech = { 0 };

    if (domain)
    {
        /* user@DOMAIN\0 */
        upn_len = strlen(user) + 1 + strlen(domain) + 1;
        upn = calloc(upn_len, sizeof(char));
        if (!upn)
        {
            maj = GSS_S_FAILURE;
            min = ENOMEM;
        }
#ifndef _WIN32
        snprintf(upn, upn_len, "%s@%s", user, domain);
#else
        _snprintf_s(upn, upn_len, upn_len, "%s@%s", user, domain);
#endif
    }
    else
    {
        /* Assume a UPN-like name form when no domain is provided */
        upn = strdup((char *)user);
        if (!upn)
        {
            maj = GSS_S_FAILURE;
            min = ENOMEM;
        }
    }
    name_buf.value = upn;
    name_buf.length = strlen(name_buf.value);
    maj = gss_import_name(
        &min,
        &name_buf,
        GSS_C_NT_USER_NAME,
        &gss_name_buf);
    if (maj)
    {
        goto error;
    }

    /*
    * Hard code desired mech OID to SRP
    */
    desired_mech.count = 1;
    desired_mech.elements = mech_oid_array;
    desired_mech.elements[0] = spnego_mech_oid;
    maj = gss_acquire_cred(
        &min,
        gss_name_buf,
        0,
        &desired_mech,
        GSS_C_INITIATE,
        &cred_handle,
        NULL,
        NULL);
    if (maj)
    {
        goto error;
    }

    gss_pwd.value = (char *)password;
    gss_pwd.length = strlen(gss_pwd.value);
    maj = gss_set_cred_option(
        &min,
        &cred_handle,
        (gss_OID)&gss_srp_password_oid,
        &gss_pwd);
    if (maj)
    {
        goto error;
    }

    *retUpn = upn;
    upn = NULL;
    *rpc_identity_h = (rpc_auth_identity_handle_t)cred_handle;

error:
    if (maj)
    {
        maj = min ? min : maj;
    }

    if (upn)
    {
        free(upn);
    }
    if (gss_name_buf)
    {
        gss_release_name(&min, &gss_name_buf);
    }

    return (DWORD)maj;
}