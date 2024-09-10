//$--HrMAPIMoveOneProp-----------------------------------------------------------
//  Move one property from a source object to a destination object.
// -----------------------------------------------------------------------------
HRESULT HrMAPIMoveOneProp(               // RETURNS: return code
    IN LPMAPIPROP lpSrcObj,             // pointer to source object
    IN ULONG ulSrcPropTag,              // source property tag
    IN ULONG ulDstPropTag,              // destination property tag
    IN BOOL IsMust,                     // TRUE if a required property
    IN BOOL IsReplace,                  // TRUE if existing destination
                                        // property can be replaced
    IN OUT LPMAPIPROP lpDstObj)         // pointer to destination object
{
    HRESULT         hr                  = NOERROR;
    HRESULT         hrT                 = NOERROR;
    SCODE           sc                  = 0;
    ULONG           cProps              = 0;
    LPSPropValue    lpProps             = NULL;
    SizedSPropTagArray(1, rgPropTag)    = { 1, 0 };

    DEBUGPUBLIC("HrMAPIMoveOneProp()\n");

    hr = CHK_HrMAPIMoveOneProp(
        lpSrcObj,
        ulSrcPropTag,
        ulDstPropTag,
        IsMust,
        IsReplace,
        lpDstObj);

    if(FAILED(hr))
        RETURN(hr);

    if(PROP_TYPE(ulSrcPropTag) != PROP_TYPE(ulDstPropTag))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if((IsReplace == FALSE) && FPropExists(lpDstObj, ulDstPropTag))
    {
        MODULE_WARNING("Destination property exists and not overwritten.");

        goto cleanup;
    }

    rgPropTag.cValues = 1;
    rgPropTag.aulPropTag[0] = ulSrcPropTag;

    hrT = MAPICALL(lpSrcObj)->GetProps(
        /*lpSrcObj,*/
        (LPSPropTagArray)&rgPropTag,
        fMapiUnicode,
        &cProps,
        &lpProps);

    if(hrT == MAPI_W_ERRORS_RETURNED)
    {
        hrT = lpProps->Value.ul;

        if(hrT != MAPI_E_NOT_FOUND)
        {
            hr = HR_LOG(E_FAIL);
        }
        else if(IsMust == TRUE)
        {
            hr = HR_LOG(MAPI_E_NOT_FOUND);
        }

        goto cleanup;
    }

    if(FAILED(hrT))
    {
        lpProps = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR(cProps != 0, "ZERO cProps variable");

    ASSERTERROR(lpProps != NULL, "NULL lpProps variable");

    lpProps->ulPropTag = ulDstPropTag;

    hrT = MAPICALL(lpDstObj)->SetProps(
        /*lpDstObj,*/
        cProps,
        lpProps,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
         
cleanup:

    MAPIFREEBUFFER(lpProps);

    RETURN(hr);
}