static
OM_uint32
_srp_gss_auth_init(
    OM_uint32 *minor_status,
    srp_gss_ctx_id_t srp_context_handle,
    int state,
    gss_buffer_t input_token,
    gss_buffer_t output_token)
{
    ber_tag_t ber_state = 0;
    struct berval ber_ctx = {0};
    struct berval *ber_upn = NULL;
    struct berval *ber_bytes_A = NULL;
    struct berval ber_salt = {0};
    struct berval ber_mda = {0};
    struct berval ber_B = {0};
    struct berval *flatten = NULL;
    BerElement *ber = NULL;
    BerElement *ber_resp = NULL;
    int berror = 0;
    int sts = 0;
    OM_uint32 maj = 0;
    OM_uint32 min = 0;
    OM_uint32 min_tmp = 0;
    gss_buffer_desc tmp_in_tok = {0};
    gss_buffer_desc disp_name_buf = {0};
    gss_buffer_t disp_name = NULL;
    gss_OID disp_name_OID = NULL;
    char *srp_upn_name = NULL;
    int srp_decode_mda_len = 0;
    int srp_decode_salt_len = 0;
    const unsigned char *srp_mda = NULL;
    const unsigned char *srp_salt = NULL;
    SRP_HashAlgorithm hash_alg = SRP_SHA1;
    SRP_NGType ng_type = SRP_NG_2048;
    struct SRPVerifier *ver = NULL;
    const unsigned char *srp_bytes_B = NULL;
    int srp_bytes_B_len = 0;
    const unsigned char *srp_session_key = NULL;
    unsigned char *ret_srp_session_key = NULL;
    int srp_session_key_len = 0;
    ber_int_t gss_srp_version_maj = 0;
    ber_int_t gss_srp_version_min = 0;
    PVMDIR_SERVER_CONTEXT hServer = NULL;
    srp_verifier_handle_t hSrp = NULL; /* aliased / cast to "ver" variable */
    srp_secret_blob_data srp_data = {0};
    int bUseCSRP = 0; /* Use CRP library directly */

    ber_ctx.bv_val = (void *) input_token->value;
    ber_ctx.bv_len = input_token->length;
    ber = ber_init(&ber_ctx);
    if (!ber)
    {
        maj = GSS_S_FAILURE;
        goto error;
    }

    srp_debug_printf("_srp_gss_auth_init(): state=SRP_AUTH_INIT\n");

    /*
     * ptr points to ASN.1 encoded data which is dependent on the authentication
     * state. The appropriate decoder format string is applied for each state
     */
    berror = ber_scanf(ber, "t{ii",
                       &ber_state, &gss_srp_version_maj, &gss_srp_version_min);
    if (berror == -1)
    {
        srp_debug_printf("_srp_gss_auth_init() ber_scanf(t{ii): failed berror=%d\n", berror);
        maj = GSS_S_FAILURE;
        goto error;
    }
    berror = ber_scanf(ber, "OO}", &ber_upn, &ber_bytes_A);
    if (berror == -1)
    {
        srp_debug_printf("_srp_gss_auth_init() ber_scanf(OO): failed berror=%d\n", berror);
        maj = GSS_S_FAILURE;
        goto error;
    }

    srp_debug_printf("_srp_gss_auth_init(accept_sec_context): protocol version %d.%d\n",
                     gss_srp_version_maj, gss_srp_version_min);
    srp_print_hex(ber_bytes_A->bv_val,
                  (int) ber_bytes_A->bv_len,
                  "_srp_gss_auth_init(accept_sec_context): bytes_A");
    /*
     * This is mostly impossible, as state IS the "t" field.
     * More a double check for proper decoding.
     */
    if ((int) ber_state != state)
    {
        maj = GSS_S_FAILURE;
        goto error;
    }

    tmp_in_tok.value = ber_upn->bv_val;
    tmp_in_tok.length = ber_upn->bv_len;
    maj = gss_import_name(&min,
                          &tmp_in_tok,
                          NULL,
                          &srp_context_handle->gss_upn_name);
    if (maj)
    {
        srp_debug_printf("_srp_gss_auth_init() gss_import_name failed maj=%d\n", maj);
        goto error;
    }

    maj = gss_display_name(&min,
                           srp_context_handle->gss_upn_name,
                           &disp_name_buf,
                           &disp_name_OID);
    if (maj)
    {
        srp_debug_printf("_srp_gss_auth_init() gss_display_name failed maj=%d\n", maj);
        goto error;
    }

    disp_name = &disp_name_buf;
    srp_debug_printf("_srp_gss_auth_init() srp_gss_accept_sec_context: UPN name=%.*s\n",
                     (int) disp_name_buf.length, (char *) disp_name_buf.value);

    srp_upn_name = calloc(disp_name_buf.length + 1, sizeof(char));
    if (!srp_upn_name)
    {
        maj = GSS_S_FAILURE;
        min = ENOMEM;
        goto error;
    }
    snprintf(srp_upn_name,
             disp_name_buf.length+1,
             "%.*s",
             (int) disp_name_buf.length,
             (char *) disp_name_buf.value);


    maj = _srp_gss_auth_create_machine_acct_binding(
              &bUseCSRP,
              &min,
              &hServer);
    if (maj)
    {
        srp_debug_printf("_srp_gss_auth_init() _srp_gss_auth_create_machine_acct_binding failed maj=%d\n", maj);
        maj = GSS_S_FAILURE;
        goto error;
    }

    if (!bUseCSRP)
    {
        sts = cli_rpc_srp_verifier_new(
                hServer ? hServer->hBinding : NULL,
                hash_alg,
                ng_type,
                srp_upn_name,
                ber_bytes_A->bv_val, (int) ber_bytes_A->bv_len,
                &srp_bytes_B, &srp_bytes_B_len,
                &srp_salt, &srp_decode_salt_len,
                &srp_mda, &srp_decode_mda_len,
                NULL, NULL, /* n_hex, g_hex */
                &hSrp);
        if (sts)
        {
            srp_debug_printf("_srp_gss_auth_init() cli_rpc_srp_verifier_new: failed sts=%d\n", sts);
            maj = GSS_S_FAILURE;
            min = sts;
            goto error;
        }
        ver = (struct SRPVerifier *) hSrp, hSrp = NULL;
    }
    else
    {
        sts = _get_srp_secret_decoded(
                  srp_upn_name,
                  &srp_data);
        if (sts)
        {
            srp_debug_printf("_srp_gss_auth_init() _get_srp_secret_decoded: failed sts=%d\n", sts);
            maj = GSS_S_FAILURE;
            min = sts;
            goto error;
        }

        /* Call SRP library implementation directly */
        ver =  srp_verifier_new(hash_alg, 
                                ng_type,
                                srp_upn_name,

                                /* SRP Salt value */
                                srp_data.salt, srp_data.salt_len,

                                /* SRP "V" verifier secret */
                                srp_data.v, srp_data.v_len,

                                /* SRP bytes_A */
                                ber_bytes_A->bv_val, (int) ber_bytes_A->bv_len,

                                /* SRP bytes B */
                                &srp_bytes_B, &srp_bytes_B_len,

                                /* SRP n_hex / g_hex */
                                NULL, NULL);
        if (!ver)
        {
            srp_debug_printf("_srp_gss_auth_init() srp_verifier_new: failed sts=%d\n", sts);
            maj = GSS_S_FAILURE;
            goto error;
        }
        srp_salt = srp_data.salt;
        srp_decode_salt_len = srp_data.salt_len;

    }

    if (!srp_bytes_B)
    {
        srp_debug_printf("_srp_gss_auth_init() srp_verifier_new: failed!\n");
        maj = GSS_S_FAILURE;
        goto error;
    }

    srp_print_hex(srp_salt, srp_decode_salt_len,
                  "_srp_gss_auth_init(accept_sec_context): srp_salt value");
    srp_print_hex(srp_bytes_B, srp_bytes_B_len,
                  "_srp_gss_auth_init(accept_sec_context): srp_B value");
    ber_mda.bv_val = (unsigned char *) srp_mda;
    ber_mda.bv_len = srp_decode_mda_len;

    ber_salt.bv_val = (unsigned char *) srp_salt;
    ber_salt.bv_len = srp_decode_salt_len;
    /*
     * B is computed: (kv + g**b) % N
     */
    ber_B.bv_val = (void *) srp_bytes_B;
    ber_B.bv_len = srp_bytes_B_len;

    ber_resp = ber_alloc_t(LBER_USE_DER);
    if (!ber_resp)
    {
        maj = GSS_S_FAILURE;
        min = ENOMEM;
        goto error;
    }

    /*
     * Response format:
     * tag | MDA | salt | B
     */
    berror = ber_printf(ber_resp, "t{OOO}",
                 SRP_AUTH_SALT_RESP,
                 &ber_mda,
                 &ber_salt,
                 &ber_B);
    if (berror == -1)
    {
        srp_debug_printf("_srp_gss_auth_init() ber_printf: failed berror=%d\n", berror);
        maj = GSS_S_FAILURE;
        goto error;
    }

    berror = ber_flatten(ber_resp, &flatten);
    if (berror == -1)
    {
        srp_debug_printf("_srp_gss_auth_init() ber_flatten: failed berror=%d\n", berror);
        maj = GSS_S_FAILURE;
        goto error;
    }

    output_token->value = gssalloc_calloc(1, flatten->bv_len);
    if (!output_token->value)
    {
        maj = GSS_S_FAILURE;
        goto error;
    }
    output_token->length = flatten->bv_len;
    memcpy(output_token->value, flatten->bv_val, flatten->bv_len);

    if (bUseCSRP)
    {
        srp_session_key = srp_verifier_get_session_key(ver, &srp_session_key_len);
    }
    else
    {
        sts = cli_rpc_srp_verifier_get_session_key(
            hServer ? hServer->hBinding : NULL,
            ver,
            &srp_session_key,
            &srp_session_key_len);
        if (sts)
        {
            min = sts;
            maj = GSS_S_FAILURE;
            goto error;
        }

    }

    if (srp_session_key && srp_session_key_len > 0)
    {
        ret_srp_session_key =
            calloc(srp_session_key_len, sizeof(unsigned char));
        if (!ret_srp_session_key)
        {
            maj = GSS_S_FAILURE;
            min = ENOMEM;
            goto error;
        }
    }
    memcpy(ret_srp_session_key,
           srp_session_key,
           srp_session_key_len);

    /* Set context handle/return values here; all previous calls succeeded */
    maj = GSS_S_CONTINUE_NEEDED;
    srp_context_handle->hServer = hServer, hServer = NULL;

    /* Used in generating Kerberos keyblock salt value */
    srp_context_handle->upn_name = srp_upn_name, srp_upn_name = NULL;
    srp_context_handle->srp_ver = ver, ver = NULL;

    /* Return the SRP session key in the context handle */
    srp_context_handle->srp_session_key_len = srp_session_key_len;
    srp_context_handle->srp_session_key = ret_srp_session_key, ret_srp_session_key = NULL;
    srp_context_handle->bUseCSRP = bUseCSRP;

    srp_print_hex(srp_session_key, srp_session_key_len,
                  "_srp_gss_auth_init(accept_sec_ctx) got session key");

error:
    if (ver)
    {
        if (bUseCSRP)
        {
            srp_verifier_delete(ver);
        }
        else
        {
            cli_rpc_srp_verifier_delete(
                hServer ? hServer->hBinding : NULL,
                (void **) &ver);
        }
    }
    VmDirCloseServer(hServer);
    if (srp_upn_name)
    {
        free(srp_upn_name);
    }
    if (ber_upn)
    {
        ber_bvfree(ber_upn);
    }
    if (ber_bytes_A)
    {
        ber_bvfree(ber_bytes_A);
    }
    ber_bvfree(flatten);
    ber_free(ber, 1);
    ber_free(ber_resp, 1);

    if (disp_name)
    {
        gss_release_buffer(&min_tmp, disp_name);
    }
    if (!bUseCSRP && srp_bytes_B)
    {
        free((void *) srp_bytes_B);
    }
    if (!bUseCSRP && srp_salt)
    {
        free((void *) srp_salt);
    }
    if (srp_mda)
    {
        free((void *) srp_mda);
    }
    if (!bUseCSRP && srp_session_key)
    {
        free((void *) srp_session_key);
    }
    if (bUseCSRP)
    {
        _free_srp_secret_decoded(&srp_data);
    }
    if (ret_srp_session_key)
    {
        free((void *) ret_srp_session_key);
    }

    if (maj)
    {
        if (min)
        {
            *minor_status = min;
        }
    }
    return maj;
}