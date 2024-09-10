//$--HrMAPICreateAddressList-----------------------------------------------------
//  Create an address list.
// -----------------------------------------------------------------------------
HRESULT HrMAPICreateAddressList(             // RETURNS: return code
    IN ULONG cProps,                        // count of values in address list
                                            // entry
    IN LPSPropValue lpPropValues,           // pointer to address list entry
    OUT LPADRLIST *lppAdrList)              // pointer to address list pointer
{
    HRESULT         hr              = NOERROR;
    SCODE           sc              = 0;
    LPSPropValue    lpNewPropValues = NULL;
    ULONG           cBytes          = 0;

    DEBUGPUBLIC("HrMAPICreateAddressList()\n");

    hr = CHK_HrMAPICreateAddressList(
        cProps,
        lpPropValues,
        lppAdrList);

    if(FAILED(hr))
        RETURN(hr);

    *lppAdrList = NULL;

    sc = ScDupPropset(
        cProps,
        lpPropValues,
		MAPIAllocateBuffer,
		&lpNewPropValues);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cBytes = CbNewADRLIST(1);

    sc = MAPIAllocateBuffer(cBytes, (LPVOID*)lppAdrList);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;
    }                                                   

    // Initialize ADRLIST structure
    ZeroMemory(*lppAdrList, cBytes);

    (*lppAdrList)->cEntries = 1;
    (*lppAdrList)->aEntries[0].cValues = cProps;
    (*lppAdrList)->aEntries[0].rgPropVals = lpNewPropValues;

cleanup:

    if(FAILED(hr))
    {
        if(lppAdrList != NULL)
        {
            MAPIFREEBUFFER(*lppAdrList);
            *lppAdrList = NULL;
        }
        MAPIFREEBUFFER(lpNewPropValues);
    }

    RETURN(hr);
}