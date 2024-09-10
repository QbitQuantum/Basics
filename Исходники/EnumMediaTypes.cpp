STDMETHODIMP
CEnumMediaTypes::Next(ULONG cMediaTypes,          // place this many types...
                      AM_MEDIA_TYPE **ppMediaTypes,   // ...in this array
                      ULONG *pcFetched)           // actual count passed
{
    CheckPointer(ppMediaTypes,E_POINTER);
    ValidateReadWritePtr(ppMediaTypes,cMediaTypes * sizeof(AM_MEDIA_TYPE *));
    /* Check we are still in sync with the pin */
    if (AreWeOutOfSync() == TRUE) {
        return VFW_E_ENUM_OUT_OF_SYNC;
    }

    if (pcFetched!=NULL) {
        ValidateWritePtr(pcFetched, sizeof(ULONG));
        *pcFetched = 0;           // default unless we succeed
    }
    // now check that the parameter is valid
    else if (cMediaTypes>1) {     // pcFetched == NULL
        return E_INVALIDARG;
    }
    ULONG cFetched = 0;           // increment as we get each one.

    /* Return each media type by asking the filter for them in turn - If we
    have an error code retured to us while we are retrieving a media type
    we assume that our internal state is stale with respect to the filter
    (for example the window size changing) so we return
    VFW_E_ENUM_OUT_OF_SYNC */

    while (cMediaTypes) {

        CMediaType cmt;

        HRESULT hr = m_pPin->GetMediaType(m_Position++, &cmt);
        if (S_OK != hr) {
            break;
        }

        /* We now have a CMediaType object that contains the next media type
        but when we assign it to the array position we CANNOT just assign
        the AM_MEDIA_TYPE structure because as soon as the object goes out of
        scope it will delete the memory we have just copied. The function
        we use is CreateMediaType which allocates a task memory block */

        /*  Transfer across the format block manually to save an allocate
        and free on the format block and generally go faster */

        *ppMediaTypes = (AM_MEDIA_TYPE *)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
        if (*ppMediaTypes == NULL) {
            break;
        }

        /*  Do a regular copy */
        **ppMediaTypes = (AM_MEDIA_TYPE)cmt;

        /*  Make sure the destructor doesn't free these */
        cmt.pbFormat = NULL;
        cmt.cbFormat = NULL;
        cmt.pUnk     = NULL;


        ppMediaTypes++;
        cFetched++;
        cMediaTypes--;
    }

    if (pcFetched!=NULL) {
        *pcFetched = cFetched;
    }

    return ( cMediaTypes==0 ? NOERROR : S_FALSE );
}