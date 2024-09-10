//$--HrMAPIFindOutbox---------------------------------------------------------
//  Find IPM outbox folder.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindOutbox(             // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid)              // Entry ID of IPM outbox
{
    HRESULT       hr          = NOERROR;
    HRESULT       hrT         = NOERROR;
    SCODE         sc          = 0;
    ULONG         cValues     = 0;
    LPSPropValue  lpPropValue = NULL;
    ULONG         cbeid       = 0;
    SPropTagArray rgPropTag   = { 1, { PR_IPM_OUTBOX_ENTRYID } };
    
    DEBUGPUBLIC("HrMAPIFindOutbox()");

    hr = CHK_HrMAPIFindOutbox(
        lpMdb,
        lpcbeid,
        lppeid);

    if(FAILED(hr))
        RETURN(hr);

    *lpcbeid = 0;
    *lppeid  = NULL;

    // Get the outbox entry ID property. 
    hrT = MAPICALL(lpMdb)->GetProps(
        /*lpMdb,*/
        &rgPropTag,
        fMapiUnicode,
        &cValues,
        &lpPropValue);

    if(hrT == MAPI_W_ERRORS_RETURNED)
    {
        if((lpPropValue != NULL) && (lpPropValue->Value.ul == MAPI_E_NOT_FOUND))
        {
            hr = HR_LOG(MAPI_E_NOT_FOUND);
        }
        else
        {
            hr = HR_LOG(E_FAIL);
        }
        goto cleanup;
    }

    if(FAILED(hrT))
    {
        lpPropValue = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR(cValues != 0, "ZERO cValues variable");

    ASSERTERROR(lpPropValue != NULL, "NULL lpPropValue variable");

    // Check to make sure we got the right property.
    if (lpPropValue->ulPropTag != PR_IPM_OUTBOX_ENTRYID)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cbeid = lpPropValue->Value.bin.cb;

    sc = MAPIAllocateBuffer(cbeid, (void **)lppeid);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    // Copy outbox Entry ID
    CopyMemory(
        *lppeid,
        lpPropValue->Value.bin.lpb,
        cbeid);

    *lpcbeid = cbeid;

cleanup:

    MAPIFREEBUFFER(lpPropValue);

    RETURN(hr);
}