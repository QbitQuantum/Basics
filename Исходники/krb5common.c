khm_int32 KHMAPI
khm_krb5_find_ccache_for_identity(khm_handle ident, krb5_context *pctx,
                                  void * buffer, khm_size * pcbbuf)
{
    krb5_context        ctx = 0;
    krb5_ccache         cache = 0;
    krb5_error_code     code;
    apiCB *             cc_ctx = 0;
    struct _infoNC **   pNCi = NULL;
    int                 i;
    khm_int32           t;
    wchar_t *           ms = NULL;
    khm_size            cb;
    krb5_timestamp      expiration = 0;
    krb5_timestamp      best_match_expiration = 0;
    char                best_match_ccname[256] = "";
    khm_handle          csp_params = NULL;
    khm_handle          csp_plugins = NULL;

    if (!buffer || !pcbbuf)
    return KHM_ERROR_GENERAL;

    ctx = *pctx;

    if (!pcc_initialize ||
        !pcc_get_NC_info ||
        !pcc_free_NC_info ||
        !pcc_shutdown)
        goto _skip_cc_iter;

    code = pcc_initialize(&cc_ctx, CC_API_VER_2, NULL, NULL);
    if (code)
        goto _exit;

    code = pcc_get_NC_info(cc_ctx, &pNCi);

    if (code) 
        goto _exit;

    for(i=0; pNCi[i]; i++) {
        if (pNCi[i]->vers != CC_CRED_V5)
            continue;

        code = (*pkrb5_cc_resolve)(ctx, pNCi[i]->name, &cache);
        if (code)
            continue;

        /* need a function to check the cache for the identity
         * and determine if it has valid tickets.  If it has 
         * the right identity and valid tickets, store the 
         * expiration time and the cache name.  If it has the
         * right identity but no valid tickets, store the ccache
         * name and an expiration time of zero.  if it does not
         * have the right identity don't save the name.
         * 
         * Keep searching to find the best cache available.
         */

        if (KHM_SUCCEEDED(khm_get_identity_expiration_time(ctx, cache, 
                                                           ident, 
                                                           &expiration))) {
            if ( expiration > best_match_expiration ) {
                best_match_expiration = expiration;
                StringCbCopyA(best_match_ccname, 
                              sizeof(best_match_ccname),
                              "API:");
                StringCbCatA(best_match_ccname,
                             sizeof(best_match_ccname),
                             pNCi[i]->name);
                expiration = 0;
            }
        }

        if(ctx != NULL && cache != NULL)
            (*pkrb5_cc_close)(ctx, cache);
        cache = 0;
    }

 _skip_cc_iter:

    if (KHM_SUCCEEDED(kmm_get_plugins_config(0, &csp_plugins))) {
        khc_open_space(csp_plugins, L"Krb5Cred\\Parameters",  0, &csp_params);
        khc_close_space(csp_plugins);
        csp_plugins = NULL;
    }

#ifdef DEBUG
    if (csp_params == NULL) {
        assert(FALSE);
    }
#endif

    if (csp_params &&
        KHM_SUCCEEDED(khc_read_int32(csp_params, L"MsLsaList", &t)) && t) {
        code = (*pkrb5_cc_resolve)(ctx, "MSLSA:", &cache);
        if (code == 0 && cache) {
            if (KHM_SUCCEEDED(khm_get_identity_expiration_time(ctx, cache, 
                                                               ident, 
                                                               &expiration))) {
                if ( expiration > best_match_expiration ) {
                    best_match_expiration = expiration;
                    StringCbCopyA(best_match_ccname, sizeof(best_match_ccname),
                                  "MSLSA:");
                    expiration = 0;
                }
            }
        }

        if (ctx != NULL && cache != NULL)
            (*pkrb5_cc_close)(ctx, cache);

        cache = 0;
    }

    if (csp_params &&
        khc_read_multi_string(csp_params, L"FileCCList", NULL, &cb)
        == KHM_ERROR_TOO_LONG &&
        cb > sizeof(wchar_t) * 2) {

        wchar_t * t;
        char ccname[MAX_PATH + 6];

        ms = PMALLOC(cb);

#ifdef DEBUG
        assert(ms);
#endif

        khc_read_multi_string(csp_params, L"FileCCList", ms, &cb);
        for(t = ms; t && *t; t = multi_string_next(t)) {
            StringCchPrintfA(ccname, ARRAYLENGTH(ccname),
                             "FILE:%S", t);

            code = (*pkrb5_cc_resolve)(ctx, ccname, &cache);
            if (code)
                continue;

            if (KHM_SUCCEEDED(khm_get_identity_expiration_time(ctx, cache, 
                                                               ident, 
                                                               &expiration))) {
                if ( expiration > best_match_expiration ) {
                    best_match_expiration = expiration;
                    StringCbCopyA(best_match_ccname,
                                  sizeof(best_match_ccname),
                                  ccname);
                    expiration = 0;
                }
            }

            if (ctx != NULL && cache != NULL)
                (*pkrb5_cc_close)(ctx, cache);
            cache = 0;
        }

        PFREE(ms);
    }
 _exit:
    if (csp_params)
        khc_close_space(csp_params);

    if (pNCi)
        (*pcc_free_NC_info)(cc_ctx, &pNCi);

    if (cc_ctx)
        (*pcc_shutdown)(&cc_ctx);

    if (best_match_ccname[0]) {
        
        if (*pcbbuf = AnsiStrToUnicode((wchar_t *)buffer, 
                                       *pcbbuf,
                                       best_match_ccname)) {

            *pcbbuf = (*pcbbuf + 1) * sizeof(wchar_t);

            return KHM_ERROR_SUCCESS;
        }

    }

    return KHM_ERROR_GENERAL;
}