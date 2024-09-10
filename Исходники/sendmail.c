/*
   Internal function to send a message via Extended MAPI. Wrapper around the Simple
   MAPI function MAPISendMail.
*/
static ULONG sendmail_extended_mapi(LHANDLE mapi_session, ULONG_PTR uiparam, lpMapiMessageW message,
    FLAGS flags)
{
    ULONG tags[] = {1, 0};
    char *subjectA = NULL, *bodyA = NULL;
    ULONG retval = MAPI_E_FAILURE;
    IMAPISession *session = NULL;
    BOOL unicode_aware = FALSE;
    IMAPITable* msg_table;
    LPSRowSet rows = NULL;
    IMsgStore* msg_store;
    IMAPIFolder* folder = NULL, *draft_folder = NULL;
    LPENTRYID entry_id;
    LPSPropValue props;
    ULONG entry_len;
    DWORD obj_type;
    IMessage* msg;
    ULONG values;
    HRESULT ret;

    TRACE("Using Extended MAPI wrapper for MAPISendMail\n");

    /* Attempt to log on via Extended MAPI */

    ret = MAPILogonEx(0, NULL, NULL, MAPI_EXTENDED | MAPI_USE_DEFAULT | MAPI_NEW_SESSION, &session);
    TRACE("MAPILogonEx: %x\n", ret);

    if (ret != S_OK)
    {
        retval = MAPI_E_LOGIN_FAILURE;
        goto cleanup;
    }

    /* Open the default message store */

    if (IMAPISession_GetMsgStoresTable(session, 0, &msg_table) == S_OK)
    {
        /* We want the default store */
        SizedSPropTagArray(2, columns) = {2, {PR_ENTRYID, PR_DEFAULT_STORE}};

        /* Set the columns we want */
        if (IMAPITable_SetColumns(msg_table, (LPSPropTagArray) &columns, 0) == S_OK)
        {
            while (1)
            {
                if (IMAPITable_QueryRows(msg_table, 1, 0, &rows) != S_OK)
                {
                    MAPIFreeBuffer(rows);
                    rows = NULL;
                }
                else if (rows->cRows != 1)
                {
                    FreeProws(rows);
                    rows = NULL;
                }
                else
                {
                    /* If it's not the default store, try the next row */
                    if (!rows->aRow[0].lpProps[1].Value.b)
                    {
                        FreeProws(rows);
                        continue;
                    }
                }

                break;
            }
        }

        IMAPITable_Release(msg_table);
    }

    /* Did we manage to get the right store? */
    if (!rows)
        goto logoff;

    /* Open the message store */
    IMAPISession_OpenMsgStore(session, 0, rows->aRow[0].lpProps[0].Value.bin.cb,
                              (ENTRYID *) rows->aRow[0].lpProps[0].Value.bin.lpb, NULL,
                              MDB_NO_DIALOG | MAPI_BEST_ACCESS, &msg_store);

    /* We don't need this any more */
    FreeProws(rows);

    /* Check if the message store supports Unicode */
    tags[1] = PR_STORE_SUPPORT_MASK;
    ret = IMsgStore_GetProps(msg_store, (LPSPropTagArray) tags, 0, &values, &props);

    if ((ret == S_OK) && (props[0].Value.l & STORE_UNICODE_OK))
        unicode_aware = TRUE;
    else
    {
        /* Don't convert to ANSI */
        if (flags & MAPI_FORCE_UNICODE)
        {
            WARN("No Unicode-capable mail client, and MAPI_FORCE_UNICODE is specified. MAPISendMail failed.\n");
            retval = MAPI_E_UNICODE_NOT_SUPPORTED;
            IMsgStore_Release(msg_store);
            goto logoff;
        }
    }

    /* First open the inbox, from which the drafts folder can be opened */
    if (IMsgStore_GetReceiveFolder(msg_store, NULL, 0, &entry_len, &entry_id, NULL) == S_OK)
    {
        IMsgStore_OpenEntry(msg_store, entry_len, entry_id, NULL, 0, &obj_type, (LPUNKNOWN*) &folder);
        MAPIFreeBuffer(entry_id);
    }

    tags[1] = PR_IPM_DRAFTS_ENTRYID;

    /* Open the drafts folder, or failing that, try asking the message store for the outbox */
    if ((folder == NULL) || ((ret = IMAPIFolder_GetProps(folder, (LPSPropTagArray) tags, 0, &values, &props)) != S_OK))
    {
        TRACE("Unable to open Drafts folder; opening Outbox instead\n");
        tags[1] = PR_IPM_OUTBOX_ENTRYID;
        ret = IMsgStore_GetProps(msg_store, (LPSPropTagArray) tags, 0, &values, &props);
    }

    if (ret != S_OK)
        goto logoff;

    IMsgStore_OpenEntry(msg_store, props[0].Value.bin.cb, (LPENTRYID) props[0].Value.bin.lpb,
        NULL, MAPI_MODIFY, &obj_type, (LPUNKNOWN *) &draft_folder);

    /* Create a new message */
    if (IMAPIFolder_CreateMessage(draft_folder, NULL, 0, &msg) == S_OK)
    {
        ULONG token;
        SPropValue p;

        /* Define message properties */
        p.ulPropTag = PR_MESSAGE_FLAGS;
        p.Value.l = MSGFLAG_FROMME | MSGFLAG_UNSENT;

        IMessage_SetProps(msg, 1, &p, NULL);

        p.ulPropTag = PR_SENTMAIL_ENTRYID;
        p.Value.bin.cb = props[0].Value.bin.cb;
        p.Value.bin.lpb = props[0].Value.bin.lpb;
        IMessage_SetProps(msg, 1,&p, NULL);

        /* Set message subject */
        if (message->lpszSubject)
        {
            if (unicode_aware)
            {
                p.ulPropTag = PR_SUBJECT_W;
                p.Value.lpszW = message->lpszSubject;
            }
            else
            {
                subjectA = convert_from_unicode(message->lpszSubject);

                p.ulPropTag = PR_SUBJECT_A;
                p.Value.lpszA = subjectA;
            }

            IMessage_SetProps(msg, 1, &p, NULL);
        }

        /* Set message body */
        if (message->lpszNoteText)
        {
            LPSTREAM stream = NULL;

            if (IMessage_OpenProperty(msg, unicode_aware ? PR_BODY_W : PR_BODY_A, &IID_IStream, 0,
                MAPI_MODIFY | MAPI_CREATE, (LPUNKNOWN*) &stream) == S_OK)
            {
                if (unicode_aware)
                    IStream_Write(stream, message->lpszNoteText, (lstrlenW(message->lpszNoteText)+1) * sizeof(WCHAR), NULL);
                else
                {
                    bodyA = convert_from_unicode(message->lpszNoteText);
                    IStream_Write(stream, bodyA, strlen(bodyA)+1, NULL);
                }

                IStream_Release(stream);
            }
        }

        /* Add message attachments */
        if (message->nFileCount > 0)
        {
            ULONG num_attach = 0;
            unsigned int i;

            for (i = 0; i < message->nFileCount; i++)
            {
                IAttach* attachment = NULL;
                char *filenameA = NULL;
                SPropValue prop[4];
                LPCWSTR filename;
                HANDLE file;

                if (!message->lpFiles[i].lpszPathName)
                    continue;

                /* Open the attachment for reading */
                file = CreateFileW(message->lpFiles[i].lpszPathName, GENERIC_READ, FILE_SHARE_READ,
                    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

                if (file == INVALID_HANDLE_VALUE)
                    continue;

                /* Check if a display filename has been given; if not, get one ourselves from path name */
                filename = message->lpFiles[i].lpszFileName;

                if (!filename)
                {
                    int j;

                    filename = message->lpFiles[i].lpszPathName;

                    for (j = lstrlenW(message->lpFiles[i].lpszPathName)-1; j >= 0; j--)
                    {
                        if (message->lpFiles[i].lpszPathName[i] == '\\' ||
                            message->lpFiles[i].lpszPathName[i] == '/')
                        {
                            filename = &message->lpFiles[i].lpszPathName[i+1];
                            break;
                        }
                    }
                }

                TRACE("Attachment %u path: '%s'; filename: '%s'\n", i, debugstr_w(message->lpFiles[i].lpszPathName),
                    debugstr_w(filename));

                /* Create the attachment */
                if (IMessage_CreateAttach(msg, NULL, 0, &num_attach, &attachment) != S_OK)
                {
                    TRACE("Unable to create attachment\n");
                    CloseHandle(file);
                    continue;
                }

                /* Set the attachment properties */
                ZeroMemory(prop, sizeof(prop));

                prop[0].ulPropTag = PR_ATTACH_METHOD;
                prop[0].Value.ul = ATTACH_BY_VALUE;

                if (unicode_aware)
                {
                    prop[1].ulPropTag = PR_ATTACH_LONG_FILENAME_W;
                    prop[1].Value.lpszW = (LPWSTR) filename;
                    prop[2].ulPropTag = PR_ATTACH_FILENAME_W;
                    prop[2].Value.lpszW = (LPWSTR) filename;
                }
                else
                {
                    filenameA = convert_from_unicode(filename);

                    prop[1].ulPropTag = PR_ATTACH_LONG_FILENAME_A;
                    prop[1].Value.lpszA = (LPSTR) filenameA;
                    prop[2].ulPropTag = PR_ATTACH_FILENAME_A;
                    prop[2].Value.lpszA = (LPSTR) filenameA;

                }

                prop[3].ulPropTag = PR_RENDERING_POSITION;
                prop[3].Value.l = -1;

                if (IAttach_SetProps(attachment, 4, prop, NULL) == S_OK)
                {
                    LPSTREAM stream = NULL;

                    if (IAttach_OpenProperty(attachment, PR_ATTACH_DATA_BIN, &IID_IStream, 0,
                        MAPI_MODIFY | MAPI_CREATE, (LPUNKNOWN*) &stream) == S_OK)
                    {
                        BYTE data[READ_BUF_SIZE];
                        DWORD size = 0, read, written;

                        while (ReadFile(file, data, READ_BUF_SIZE, &read, NULL) && (read != 0))
                        {
                            IStream_Write(stream, data, read, &written);
                            size += read;
                        }

                        TRACE("%d bytes written of attachment\n", size);

                        IStream_Commit(stream, STGC_DEFAULT);
                        IStream_Release(stream);

                        prop[0].ulPropTag = PR_ATTACH_SIZE;
                        prop[0].Value.ul = size;
                        IAttach_SetProps(attachment, 1, prop, NULL);

                        IAttach_SaveChanges(attachment, KEEP_OPEN_READONLY);
                        num_attach++;
                    }
                }

                CloseHandle(file);
                IAttach_Release(attachment);

                HeapFree(GetProcessHeap(), 0, filenameA);
            }
        }

        IMessage_SaveChanges(msg, KEEP_OPEN_READWRITE);

        /* Prepare the message form */

        if (IMAPISession_PrepareForm(session, NULL, msg, &token) == S_OK)
        {
            ULONG access = 0, status = 0, message_flags = 0, pc = 0;
            ULONG pT[2] = {1, PR_MSG_STATUS};

            /* Retrieve message status, flags, access rights and class */

            if (IMessage_GetProps(msg, (LPSPropTagArray) pT, 0, &pc, &props) == S_OK)
            {
                status = props->Value.ul;
                MAPIFreeBuffer(props);
            }

            pT[1] = PR_MESSAGE_FLAGS;

            if (IMessage_GetProps(msg, (LPSPropTagArray) pT, 0, &pc, &props) == S_OK)
            {
                message_flags = props->Value.ul;
                MAPIFreeBuffer(props);
            }

            pT[1] = PR_ACCESS;

            if (IMessage_GetProps(msg, (LPSPropTagArray) pT, 0, &pc, &props) == S_OK)
            {
                access = props->Value.ul;
                MAPIFreeBuffer(props);
            }

            pT[1] = PR_MESSAGE_CLASS_A;

            if (IMessage_GetProps(msg, (LPSPropTagArray) pT, 0, &pc, &props) == S_OK)
            {
                /* Show the message form (edit window) */

                ret = IMAPISession_ShowForm(session, 0, msg_store, draft_folder, NULL,
                                            token, NULL, 0, status, message_flags, access,
                                            props->Value.lpszA);

                switch (ret)
                {
                    case S_OK:
                        retval = SUCCESS_SUCCESS;
                        break;

                    case MAPI_E_USER_CANCEL:
                        retval = MAPI_E_USER_ABORT;
                        break;

                    default:
                        TRACE("ShowForm failure: %x\n", ret);
                        break;
                }
            }
        }

        IMessage_Release(msg);
    }

    /* Free up the resources we've used */
    IMAPIFolder_Release(draft_folder);
    if (folder) IMAPIFolder_Release(folder);
    IMsgStore_Release(msg_store);

    HeapFree(GetProcessHeap(), 0, subjectA);
    HeapFree(GetProcessHeap(), 0, bodyA);

logoff: ;
    IMAPISession_Logoff(session, 0, 0, 0);
    IMAPISession_Release(session);

cleanup: ;
    MAPIUninitialize();
    return retval;
}