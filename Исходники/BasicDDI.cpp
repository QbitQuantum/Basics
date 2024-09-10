/////////////////////////////////////////////////////////////////////////
//
// GetStoredApplicationOrder()
//
// Retrieves the gadget order from the property store.  The memory must
// be CoTaskMemFree'd by the caller.
//
// Parameters:
//      ppAppIds [out]
//          A pointer to an array of APPLICATION_IDs that upon return will
//          contain the application IDs in the order that they should be
//          presented on the device
//      pcAppIds [out]
//          A pointer to a DWORD that upon return will contain the count of
//          APPLICATION_ID contained in the array pointed to by ppAppIds.
//
// Return Values:
//      S_OK: Success
//
/////////////////////////////////////////////////////////////////////////
HRESULT CWssBasicDDI::GetStoredApplicationOrder(APPLICATION_ID** ppAppIds,
                                                DWORD* pcAppIds)
{
    if ((NULL == m_pUserSID) ||
        (0 == IsValidSid(m_pUserSID)) ||
        (NULL == m_pPropertyStore))
    {
        return E_UNEXPECTED;
    }

    HRESULT hr = S_OK;
    LPTSTR wszKey = NULL;

    // Initialize out parameters
    *ppAppIds = NULL;
    *pcAppIds = 0;

    //
    // Get the key to use for the property store
    //
    hr = GetApplicationOrderString(&wszKey);

    //
    // Put the data into a PROPVARIANT, and store it in the property store
    //
    if ((SUCCEEDED(hr)) && (NULL != wszKey))
    {
        PROPVARIANT pvBlob = {0};

        PropVariantInit(&pvBlob);

        hr = m_pPropertyStore->GetNamedValue(wszKey, &pvBlob);
        if (SUCCEEDED(hr) &&
            (VT_BLOB == pvBlob.vt) &&
            (0 == (pvBlob.blob.cbSize % sizeof(APPLICATION_ID))))
        {
            *pcAppIds = pvBlob.blob.cbSize / sizeof(APPLICATION_ID);
            *ppAppIds = (APPLICATION_ID*)pvBlob.blob.pBlobData;
        }

        // Don't clear the PROPVARIANT because we don't want to erase the memory that we pass out of this method
    }

    if (NULL != wszKey)
    {
        ::CoTaskMemFree(wszKey);
    }

    return hr;
}