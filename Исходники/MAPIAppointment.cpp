HRESULT MAPIAppointment::InitNamedPropsForAppt()
{
    // init named props
    nameIds[0] = 0x0023;
    nameIds[1] = 0x820D;
    nameIds[2] = 0x820E;
    nameIds[3] = 0x8208;
    nameIds[4] = 0x8205;
    nameIds[5] = 0x8215;
    nameIds[6] = 0x8223;
    nameIds[7] = 0x8216;
    nameIds[8] = 0x8234;
    nameIds[9] = 0x8218;
    nameIds[10] = 0x8228;

    nameIdsC[0] = 0x8501;
    nameIdsC[1] = 0x8506;
	nameIdsC[2] = 0x8503;

    HRESULT hr = S_OK;
    Zimbra::Util::ScopedBuffer<SPropValue> pPropValMsgClass;

    if (FAILED(hr = HrGetOneProp(m_pMessage, PR_MESSAGE_CLASS, pPropValMsgClass.getptr())))
        throw MAPIAppointmentException(hr, L"InitNamedPropsForAppt(): HrGetOneProp Failed.", 
		ERR_MAPI_APPOINTMENT, __LINE__, __FILE__);

    // initialize the MAPINAMEID structure GetIDsFromNames requires
    LPMAPINAMEID ppNames[N_NUMAPPTPROPS] = { 0 };
    for (int i = 0; i < N_NUMAPPTPROPS; i++)
    {
        MAPIAllocateBuffer(sizeof (MAPINAMEID), (LPVOID *)&(ppNames[i]));
        ppNames[i]->ulKind = MNID_ID;
        ppNames[i]->lpguid = (i == N_UID) ? (LPGUID)(&PS_OUTLOOK_MTG) : (LPGUID)(&PS_OUTLOOK_APPT);
        ppNames[i]->Kind.lID = nameIds[i];
    }

    LPMAPINAMEID ppNamesC[N_NUMCOMMONPROPS] = { 0 };
    for (int i = 0; i < N_NUMCOMMONPROPS; i++)
    {
        MAPIAllocateBuffer(sizeof (MAPINAMEID), (LPVOID *)&(ppNamesC[i]));
        ppNamesC[i]->ulKind = MNID_ID;
        ppNamesC[i]->lpguid = (LPGUID)(&PS_OUTLOOK_COMMON);
        ppNamesC[i]->Kind.lID = nameIdsC[i];
    }

    // get the real prop tag ID's
    LPSPropTagArray pAppointmentTags = NULL;
    LPSPropTagArray pAppointmentTagsC = NULL;

    if (FAILED(hr = m_pMessage->GetIDsFromNames(N_NUMAPPTPROPS, ppNames, MAPI_CREATE,
            &pAppointmentTags)))
        throw MAPIAppointmentException(hr, L"Init(): GetIDsFromNames on pAppointmentTags Failed.", 
		ERR_MAPI_APPOINTMENT, __LINE__, __FILE__);

    if (FAILED(hr = m_pMessage->GetIDsFromNames(N_NUMCOMMONPROPS, ppNamesC, MAPI_CREATE,
            &pAppointmentTagsC)))
        throw MAPIAppointmentException(hr, L"Init(): GetIDsFromNames on pAppointmentTagsC Failed.", 
		ERR_MAPI_APPOINTMENT, __LINE__, __FILE__);

    // give the prop tag ID's a type
    pr_clean_global_objid = SetPropType(pAppointmentTags->aulPropTag[N_UID], PT_BINARY);
    pr_appt_start = SetPropType(pAppointmentTags->aulPropTag[N_APPTSTART], PT_SYSTIME);
    pr_appt_end = SetPropType(pAppointmentTags->aulPropTag[N_APPTEND], PT_SYSTIME);
    pr_location = SetPropType(pAppointmentTags->aulPropTag[N_LOCATION], PT_TSTRING);
    pr_busystatus = SetPropType(pAppointmentTags->aulPropTag[N_BUSYSTATUS], PT_LONG);
    pr_allday = SetPropType(pAppointmentTags->aulPropTag[N_ALLDAY], PT_BOOLEAN);
    pr_isrecurring = SetPropType(pAppointmentTags->aulPropTag[N_ISRECUR], PT_BOOLEAN);
    pr_recurstream = SetPropType(pAppointmentTags->aulPropTag[N_RECURSTREAM], PT_BINARY);
    pr_timezoneid = SetPropType(pAppointmentTags->aulPropTag[N_TIMEZONEID], PT_TSTRING);
    pr_responsestatus = SetPropType(pAppointmentTags->aulPropTag[N_RESPONSESTATUS], PT_LONG);
    pr_exceptionreplacetime = SetPropType(pAppointmentTags->aulPropTag[N_EXCEPTIONREPLACETIME], PT_SYSTIME);
    pr_reminderminutes = SetPropType(pAppointmentTagsC->aulPropTag[N_REMINDERMINUTES], PT_LONG);
	
    pr_private = SetPropType(pAppointmentTagsC->aulPropTag[N_PRIVATE], PT_BOOLEAN);
	pr_reminderset = SetPropType(pAppointmentTagsC->aulPropTag[N_REMINDERSET], PT_BOOLEAN);
    // free the memory we allocated on the head
    for (int i = 0; i < N_NUMAPPTPROPS; i++)
    {
        MAPIFreeBuffer(ppNames[i]);
    }
    for (int i = 0; i < N_NUMCOMMONPROPS; i++)
    {
        MAPIFreeBuffer(ppNamesC[i]);
    }
    MAPIFreeBuffer(pAppointmentTags);
    MAPIFreeBuffer(pAppointmentTagsC);

    //MAPIAppointment::m_bNamedPropsInitialized = true;

    return S_OK;
}