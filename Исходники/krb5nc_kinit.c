static krb5_error_code KRB5_CALLCONV
kinit_prompter(krb5_context context,
               void *data,
               const char *name,
               const char *banner,
               int num_prompts,
               krb5_prompt prompts[])
{
    int i;
    k5_kinit_task * kt;
    khm_size ncp;
    krb5_error_code code = 0;
    BOOL new_prompts = TRUE;
    khm_handle csp_prcache = NULL;

    kt = (k5_kinit_task *) data;
    assert(kt && kt->magic == K5_KINIT_TASK_MAGIC);

    EnterCriticalSection(&kt->cs);

    if (kt->state == K5_KINIT_STATE_ABORTED) {
        LeaveCriticalSection(&kt->cs);
        return KRB5_LIBOS_PWDINTR;
    }

#ifdef DEBUG
    assert(kt->state == K5_KINIT_STATE_INCALL ||
           kt->state == K5_KINIT_STATE_CONFIRM);

    _reportf(L"k5_kinit_prompter() received %d prompts with name=[%S] banner=[%S]",
             num_prompts,
             name, banner);
    for (i=0; i < num_prompts; i++) {
        _reportf(L"Prompt[%d]: string[%S]", i, prompts[i].prompt);
    }
#endif

    /* we got prompts?  Then we assume that the principal is valid */

    if (!kt->is_valid_principal) {
        kt->is_valid_principal = TRUE;

        /* if the flags that were used to call kinit were restricted
           because we didn't know the validity of the principal, then
           we need to go back and retry the call with the correct
           flags. */
        if (kt->params.forwardable ||
            kt->params.proxiable ||
            kt->params.renewable) {

            _reportf(L"Retrying kinit call due to restricted flags on first call.");
            kt->state = K5_KINIT_STATE_RETRY;
            LeaveCriticalSection(&kt->cs);

            return KRB5_LIBOS_PWDINTR;
        }
    }

    /* check if we are already showing the right prompts */
    khui_cw_get_prompt_count(kt->nc, &ncp);

    if (num_prompts != (int) ncp && num_prompts != 0)
        goto _show_new_prompts;

    for (i=0; i < num_prompts; i++) {
        wchar_t wprompt[KHUI_MAXCCH_PROMPT];
        khui_new_creds_prompt * p;

        if(prompts[i].prompt) {
            AnsiStrToUnicode(wprompt, sizeof(wprompt),
                             prompts[i].prompt);
        } else {
            wprompt[0] = L'\0';
        }

        if (KHM_FAILED(khui_cw_get_prompt(kt->nc, i, &p)))
            break;

        if (                    /* if we received a prompt string,
                                   then it should be the same as the
                                   one that is displayed */
            (wprompt[0] != L'\0' &&
             (p->prompt == NULL ||
              wcscmp(wprompt, p->prompt))) ||

                                /* if we didn't receive one, then
                                   there shouldn't be one displayed.
                                   This case really shouldn't happen
                                   in reality, but we check anyway. */
            (wprompt[0] == L'\0' &&
             p->prompt != NULL) ||

                                /* the type should match */
            (prompts[i].type != p->type) ||

                                /* if this prompt should be hidden,
                                   then it must also be so */
            (prompts[i].hidden &&
             !(p->flags & KHUI_NCPROMPT_FLAG_HIDDEN)) ||
            (!prompts[i].hidden &&
             (p->flags & KHUI_NCPROMPT_FLAG_HIDDEN))
            )

            break;
    }

    if (i >= num_prompts) {

        new_prompts = FALSE;

        /* ok. looks like we are already showing the same set of
           prompts that we were supposed to show.  Sync up the values
           and go ahead. */
        goto _process_prompts;
    }

 _show_new_prompts:
    if (num_prompts == 0) {

        assert(FALSE);

        khui_cw_notify_identity_state(kt->nc,
                                      kt->nct->hwnd_panel,
                                      NULL,
                                      KHUI_CWNIS_READY |
                                      KHUI_CWNIS_NOPROGRESS |
                                      KHUI_CWNIS_VALIDATED, 0);

        code = 0;
        kt->is_null_password = TRUE;
        goto _process_prompts;
    }

    /* in addition to showing new prompts, we also cache the first set
       of prompts. */
    if (kt->prompt_set_index == 0) {
        khm_handle csp_idconfig = NULL;
        khm_handle csp_idk5 = NULL;

        kcdb_identity_get_config(kt->identity,
                                 KHM_FLAG_CREATE,
                                 &csp_idconfig);

        if (csp_idconfig != NULL)
            khc_open_space(csp_idconfig,
                           CSNAME_KRB5CRED,
                           KHM_FLAG_CREATE,
                           &csp_idk5);

        if (csp_idk5 != NULL)
            khc_open_space(csp_idk5,
                           CSNAME_PROMPTCACHE,
                           KHM_FLAG_CREATE,
                           &csp_prcache);

        khc_close_space(csp_idconfig);
        khc_close_space(csp_idk5);
    }

    {
        wchar_t wbanner[KHUI_MAXCCH_BANNER];
        wchar_t wname[KHUI_MAXCCH_PNAME];

        if(banner)
            AnsiStrToUnicode(wbanner, sizeof(wbanner), banner);
        else
            wbanner[0] = L'\0';

        if(name)
            AnsiStrToUnicode(wname, sizeof(wname), name);
        else
            LoadString(hResModule, IDS_PNAME_PW, wname, ARRAYLENGTH(wname));

        khui_cw_clear_prompts(kt->nc);

        khui_cw_begin_custom_prompts(kt->nc, num_prompts, wbanner, wname);

        if (csp_prcache) {
            FILETIME current;
            FILETIME lifetime;
            FILETIME expiry;
            khm_int64 iexpiry;
            khm_int32 t = 0;

            khc_write_string(csp_prcache, L"Banner", wbanner);
            khc_write_string(csp_prcache, L"Name", (name)? wname: L"");
            khc_write_int32(csp_prcache, L"PromptCount", (khm_int32) num_prompts);

            GetSystemTimeAsFileTime(&current);
#ifdef USE_PROMPT_CACHE_LIFETIME
            khc_read_int32(csp_params, L"PromptCacheLifetime", &t);
            if (t == 0)
                t = 172800;         /* 48 hours */
#else
            khc_read_int32(csp_params, L"MaxRenewLifetime", &t);
            if (t == 0)
                t = 2592000;    /* 30 days */
            t += 604800;        /* + 7 days */
#endif
            TimetToFileTimeInterval(t, &lifetime);
            expiry = FtAdd(&current, &lifetime);
            iexpiry = FtToInt(&expiry);

            khc_write_int64(csp_prcache, L"ExpiresOn", iexpiry);
        }
    }

    for(i=0; i < num_prompts; i++) {
        wchar_t wprompt[KHUI_MAXCCH_PROMPT];

        if(prompts[i].prompt) {
            AnsiStrToUnicode(wprompt, sizeof(wprompt),
                             prompts[i].prompt);
        } else {
            wprompt[0] = 0;
        }

        khui_cw_add_prompt(kt->nc, prompts[i].type,
                           wprompt, NULL,
                           (prompts[i].hidden?KHUI_NCPROMPT_FLAG_HIDDEN:0));

        if (csp_prcache) {
            khm_handle csp_p = NULL;
            wchar_t wnum[8];    /* should be enough for 10
                                   million prompts */

            wnum[0] = 0;
            StringCbPrintf(wnum, sizeof(wnum), L"%d", i);

            khc_open_space(csp_prcache, wnum, KHM_FLAG_CREATE, &csp_p);

            if (csp_p) {
                khc_write_string(csp_p, L"Prompt", wprompt);
                khc_write_int32(csp_p, L"Type", prompts[i].type);
                khc_write_int32(csp_p, L"Flags",
                                (prompts[i].hidden?
                                 KHUI_NCPROMPT_FLAG_HIDDEN:0));

                khc_close_space(csp_p);
            }
        }
    }

    if (csp_prcache) {
        khc_close_space(csp_prcache);
        csp_prcache = NULL;
    }

 _process_prompts:
    if (new_prompts) {
        kt->state = K5_KINIT_STATE_WAIT;

        kcdb_identity_set_flags(kt->identity,
                                KCDB_IDENT_FLAG_VALID | KCDB_IDENT_FLAG_KEY_EXPORT,
                                KCDB_IDENT_FLAG_VALID | KCDB_IDENT_FLAG_KEY_EXPORT);
        khui_cw_notify_identity_state(kt->nc, kt->nct->hwnd_panel, L"",
                                      KHUI_CWNIS_VALIDATED |
                                      KHUI_CWNIS_READY, 0);

        SetEvent(kt->h_parent_wait);
        LeaveCriticalSection(&kt->cs);
        WaitForSingleObject(kt->h_task_wait, INFINITE);
        EnterCriticalSection(&kt->cs);
    }

    /* we get here after the user selects an action that either
       cancels the credentials acquisition operation or triggers the
       actual acquisition of credentials. */
    if (kt->state != K5_KINIT_STATE_INCALL &&
        kt->state != K5_KINIT_STATE_CONFIRM) {
        code = KRB5_LIBOS_PWDINTR;
        goto _exit;
    }

    kt->is_null_password = FALSE;

    /* otherwise, we need to get the data back from the UI and return
       0 */

    khui_cw_sync_prompt_values(kt->nc);

    for(i=0; i<num_prompts; i++) {
        krb5_data * d;
        wchar_t wbuf[512];
        khm_size cbbuf;
        size_t cch;

        d = prompts[i].reply;

        cbbuf = sizeof(wbuf);
        if(KHM_SUCCEEDED(khui_cw_get_prompt_value(kt->nc, i, wbuf, &cbbuf))) {
            UnicodeStrToAnsi(d->data, d->length, wbuf);
            if(SUCCEEDED(StringCchLengthA(d->data, d->length, &cch)))
                d->length = (unsigned int) cch;
            else
                d->length = 0;
        } else {
            assert(FALSE);
            d->length = 0;
        }

        if (prompts[i].type == KRB5_PROMPT_TYPE_PASSWORD &&
            d->length == 0)

            kt->is_null_password = TRUE;
    }

    if (khui_cw_get_persist_private_data(kt->nc) &&
        num_prompts == 1 &&
	prompts[0].type == KRB5_PROMPT_TYPE_PASSWORD &&
        prompts[0].reply->length != 0) {
        k5_reply_to_acqpriv_id_request(kt->nc, prompts[0].reply);
    }

 _exit:

    kt->prompt_set_index++;

    LeaveCriticalSection(&kt->cs);

    /* entering a NULL password is equivalent to cancelling out */
    if (kt->is_null_password)
        return KRB5_LIBOS_PWDINTR;
    else
        return code;
}