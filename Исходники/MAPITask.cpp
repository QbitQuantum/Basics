HRESULT MAPITask::InitNamedPropsForTask()
{
    // init named props
    nameIds[0] = 0x8126;
    nameIds[1] = 0x8116;
    nameIds[2] = 0x8101;
    nameIds[3] = 0x8102;
    nameIds[4] = 0x8104;
    nameIds[5] = 0x8105;
    nameIds[6] = 0x8111;
    nameIds[7] = 0x8110;

    nameIdsC[0] = 0x8539;
    nameIdsC[1] = 0x8534;
    nameIdsC[2] = 0x8535;
    nameIdsC[3] = 0x8503;
    nameIdsC[4] = 0x8560;
    nameIdsC[5] = 0x8506;

    HRESULT hr = S_OK;
    Zimbra::Util::ScopedBuffer<SPropValue> pPropValMsgClass;

    if (FAILED(hr = HrGetOneProp(m_pMessage, PR_MESSAGE_CLASS, pPropValMsgClass.getptr())))
        throw MAPITaskException(hr, L"InitNamedPropsForTask(): HrGetOneProp Failed.",
                                ERR_MAPI_TASK, __LINE__, __FILE__);

    // initialize the MAPINAMEID structure GetIDsFromNames requires
    LPMAPINAMEID ppNames[N_NUMTASKPROPS] = { 0 };
    for (int i = 0; i < N_NUMTASKPROPS; i++)
    {
        MAPIAllocateBuffer(sizeof (MAPINAMEID), (LPVOID *)&(ppNames[i]));
        ppNames[i]->ulKind = MNID_ID;
        ppNames[i]->lpguid = (LPGUID)(&PS_OUTLOOK_TASK);
        ppNames[i]->Kind.lID = nameIds[i];
    }

    LPMAPINAMEID ppNamesC[N_NUMCOMMONTPROPS] = { 0 };
    for (int i = 0; i < N_NUMCOMMONTPROPS; i++)
    {
        MAPIAllocateBuffer(sizeof (MAPINAMEID), (LPVOID *)&(ppNamesC[i]));
        ppNamesC[i]->ulKind = MNID_ID;
        ppNamesC[i]->lpguid = (LPGUID)(&PS_OUTLOOK_COMMON);
        ppNamesC[i]->Kind.lID = nameIdsC[i];
    }

    // get the real prop tag ID's
    LPSPropTagArray pTaskTags  = NULL;
    LPSPropTagArray pTaskTagsC = NULL;

    if (FAILED(hr = m_pMessage->GetIDsFromNames(N_NUMTASKPROPS, ppNames, MAPI_CREATE,
                    &pTaskTags)))
        throw MAPITaskException(hr, L"Init(): GetIDsFromNames on pTaskTags Failed.", ERR_MAPI_TASK,
                                __LINE__, __FILE__);

    if (FAILED(hr = m_pMessage->GetIDsFromNames(N_NUMCOMMONTPROPS, ppNamesC, MAPI_CREATE,
                    &pTaskTagsC)))
        throw MAPITaskException(hr, L"Init(): GetIDsFromNames on pAppointmentTagsC Failed.", ERR_MAPI_TASK,
                                __LINE__, __FILE__);

    // give the prop tag ID's a type
    pr_isrecurringt = SetPropType(pTaskTags->aulPropTag[N_ISRECURT], PT_BOOLEAN);
    pr_recurstreamt = SetPropType(pTaskTags->aulPropTag[N_RECURSTREAMT], PT_BINARY);
    pr_status = SetPropType(pTaskTags->aulPropTag[N_STATUS], PT_LONG);
    pr_percentcomplete = SetPropType(pTaskTags->aulPropTag[N_PERCENTCOMPLETE], PT_DOUBLE);
    pr_taskstart = SetPropType(pTaskTags->aulPropTag[N_TASKSTART], PT_SYSTIME);
    pr_taskdue = SetPropType(pTaskTags->aulPropTag[N_TASKDUE], PT_SYSTIME);
    pr_totalwork = SetPropType(pTaskTags->aulPropTag[N_TOTALWORK], PT_LONG);
    pr_actualwork = SetPropType(pTaskTags->aulPropTag[N_ACTUALWORK], PT_LONG);
    pr_companies = SetPropType(pTaskTagsC->aulPropTag[N_COMPANIES], PT_MV_TSTRING);
    pr_mileage = SetPropType(pTaskTagsC->aulPropTag[N_MILEAGE], PT_TSTRING);
    pr_billinginfo = SetPropType(pTaskTagsC->aulPropTag[N_BILLING], PT_TSTRING);
    pr_taskreminderset = SetPropType(pTaskTagsC->aulPropTag[N_TASKREMINDERSET], PT_BOOLEAN);
    pr_taskflagdueby = SetPropType(pTaskTagsC->aulPropTag[N_TASKFLAGDUEBY], PT_SYSTIME);
    pr_private = SetPropType(pTaskTagsC->aulPropTag[N_TPRIVATE], PT_BOOLEAN);

    // free the memory we allocated on the head
    for (int i = 0; i < N_NUMTASKPROPS; i++)
    {
        MAPIFreeBuffer(ppNames[i]);
    }
    for (int i = 0; i < N_NUMCOMMONTPROPS; i++)
    {
        MAPIFreeBuffer(ppNamesC[i]);
    }
    MAPIFreeBuffer(pTaskTags);
    MAPIFreeBuffer(pTaskTagsC);

    //MAPITask::m_bNamedPropsInitialized = true;

    return S_OK;
}