void k4_handle_wmnc_notify(k4_dlg_data * d,
                           WPARAM wParam,
                           LPARAM lParam) {
    switch(HIWORD(wParam)) {
    case WMNC_UPDATE_CREDTEXT:
        {
            if (d->nct->credtext) {
                PFREE(d->nct->credtext);
                d->nct->credtext = NULL;
            }

            if (d->nc->n_identities > 0 &&
                d->nc->identities[0]) {

                khm_int32 flags = 0;
                wchar_t idname[KCDB_IDENT_MAXCCH_NAME];
                wchar_t * atsign;
                wchar_t * realm;
                khm_size cb;

                kcdb_identity_get_flags(d->nc->identities[0], &flags);

                if (!(flags & KCDB_IDENT_FLAG_VALID)) {
                    break;
                }

                cb = sizeof(idname);
                kcdb_identity_get_name(d->nc->identities[0], idname,
                                       &cb);

                atsign = wcsrchr(idname, L'@');

                if (atsign == NULL || !atsign[1])
                    break;

                realm = ++atsign;

                if (d->k4_enabled) {
                    wchar_t wmethod[128];
                    wchar_t wfmt[128];
                    wchar_t wct[512];

                    LoadString(hResModule, IDS_CT_TGTFOR,
                               wfmt, ARRAYLENGTH(wfmt));

                    if (d->method == K4_METHOD_AUTO)
                        LoadString(hResModule, IDS_METHOD_AUTO, wmethod,
                                   ARRAYLENGTH(wmethod));
                    else if (d->method == K4_METHOD_PASSWORD)
                        LoadString(hResModule, IDS_METHOD_PWD, wmethod,
                                   ARRAYLENGTH(wmethod));
                    else if (d->method == K4_METHOD_K524)
                        LoadString(hResModule, IDS_METHOD_K524, wmethod,
                                   ARRAYLENGTH(wmethod));
                    else {
                        assert(FALSE);
                    }

                    StringCbPrintf(wct, sizeof(wct), wfmt, realm, wmethod);

                    StringCbLength(wct, sizeof(wct), &cb);
                    cb += sizeof(wchar_t);

                    d->nct->credtext = PMALLOC(cb);

                    StringCbCopy(d->nct->credtext, cb, wct);
                } else {
                    wchar_t wct[256];

                    LoadString(hResModule, IDS_CT_DISABLED,
                               wct, ARRAYLENGTH(wct));

                    StringCbLength(wct, sizeof(wct), &cb);
                    cb += sizeof(wchar_t);

                    d->nct->credtext = PMALLOC(cb);

                    StringCbCopy(d->nct->credtext, cb, wct);
                }
            }
            /* no identities were selected.  it is not the
               responsibility of krb4 to complain about this. */
        }
        break;

    case WMNC_IDENTITY_CHANGE:
        k4_read_identity_data(d);
        k4_update_display(d, TRUE);
        break;

    case WMNC_CREDTEXT_LINK:
        {
            wchar_t wid[KHUI_MAXCCH_HTLINK_FIELD];
            wchar_t * wids;
            khui_htwnd_link * l;

            l = (khui_htwnd_link *) lParam;

            StringCchCopyN(wid, ARRAYLENGTH(wid), l->id, l->id_len);
            wids = wcschr(wid, L':');

            if (!wids)
                break;
            else
                wids++;

            if (!wcscmp(wids, L"Enable")) {
                d->k4_enabled = TRUE;

                k4_update_display(d, TRUE);
                khui_cw_enable_type(d->nc, credtype_id_krb4, TRUE);
            }
        }
        break;
    }
}