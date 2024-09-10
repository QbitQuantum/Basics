//$--HrEDKSearchTableByProp-----------------------------------------------------
//  Find the entry IDs matching the restriction.
// -----------------------------------------------------------------------------
static HRESULT HrEDKSearchTableByProp(  // RETURNS: return code
    IN LPMAPITABLE lpTable,             // pointer to table
    IN LPSPropValue lpSPropValue,       // property value
    OUT LPENTRYLIST *lppMsgList)        // list of matching entry IDs
{
    HRESULT       hr         = NOERROR;
    HRESULT       hrT        = NOERROR;
    LPSRowSet     lpRows     = NULL;
    LPENTRYLIST   lpMsgList  = NULL;
    ULONG         i          = 0;
    ULONG         cbeid      = 0;
    LPENTRYID     lpeid      = NULL;
    ULONG         cRows      = 0;
    SPropTagArray rgPropTags = { 1, { PR_ENTRYID } };
    SRestriction  sres       = { 0 };
    LPSPropValue  lpProp     = NULL;

    DEBUGPRIVATE("HrEDKSearchTableByProp()");

    hr = CHK_HrEDKSearchTableByProp(
        lpTable,
        lpSPropValue,
        lppMsgList);

    if(FAILED(hr))
        RETURN(hr);

    *lppMsgList = NULL;

    // Set the columns to return
    hrT = MAPICALL(lpTable)->SetColumns(/*lpTable,*/ &rgPropTags, TBL_BATCH);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Restrict rows to those that match criteria

    sres.rt                         = RES_PROPERTY;
    sres.res.resProperty.relop      = RELOP_EQ;
    sres.res.resProperty.ulPropTag  = lpSPropValue->ulPropTag;
    sres.res.resProperty.lpProp     = lpSPropValue;

    hrT = MAPICALL(lpTable)->Restrict(/*lpTable,*/ &sres, 0);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Search the rows of the table, EDK_MAX_QUERY_ROWS at a time
    
    for(;;)
    {
    
        // Get a row set

        hrT = MAPICALL(lpTable)->QueryRows(
            /*lpTable,*/
            EDK_MAX_QUERY_ROWS,
            0,
            &lpRows);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        cRows = lpRows->cRows;

        // If table is empty then no message(s)

        if((cRows == 0) && (lpMsgList == NULL))
        {
            hr = HR_LOG(EDK_E_NOT_FOUND);
            goto cleanup;
        }

        // Create list of entry IDs

        for(i = 0; i < cRows; i++)
        {
            lpProp = lpRows->aRow[i].lpProps;

            if((lpProp[0].ulPropTag == PR_ENTRYID) && (lpRows->aRow[i].cValues > 0))
            {
                cbeid = lpProp[0].Value.bin.cb;

                lpeid = (LPENTRYID)lpProp[0].Value.bin.lpb;

                if(lpMsgList == NULL)
                {
                    hrT = HrMAPICreateEntryList(cbeid,lpeid,&lpMsgList);

                    if(FAILED(hrT))
                    {
                        hr = HR_LOG(E_FAIL);
                        goto cleanup;
                    }
                }
                else
                {
                    hrT = HrMAPIAppendEntryList(cbeid,lpeid,lpMsgList);

                    if(FAILED(hrT))
                    {
                        hr = HR_LOG(E_FAIL);
                        goto cleanup;
                    }
                }
            }
            else
            {
                ASSERTERROR(
                    (lpProp[0].ulPropTag == PR_ENTRYID),"INVALID property tag");

                ASSERTERROR((lpRows->aRow[i].cValues > 0),"INVALID row entry");
            }
        }

        FREEPROWS(lpRows);
    }

cleanup:

    FREEPROWS(lpRows);

    if(FAILED(hr))
    {
        hrT = HrMAPIDestroyEntryList(&lpMsgList);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
        }

        *lppMsgList = NULL;
    }
    else
    {
        *lppMsgList = lpMsgList;
    }

    RETURN(hr);
}