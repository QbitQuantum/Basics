//Changed from
//ms-help://MS.SSC.v35/MS.SSC.v35.EN/ssctechref/html/a25fafe1-e90a-4545-8836-749dd44135c0.htm
CString SqlCeHelper::GetErrorsMessage()
{
    static CString sErrIErrorInfo     = L"IErrorInfo interface";
    static CString sErrIErrorRecords  = L"IErrorRecords interface";
    static CString sErrRecordCount    = L"error record count";
    static CString sErrInfo           = L"ERRORINFO structure";
    static CString sErrStandardInfo   = L"standard error info";
    static CString sErrDescription    = L"standard error description";
    static CString sErrNoSource       = L"error source";

    HRESULT hr                          = S_OK;
    IErrorInfo       *pIErrorInfo       = NULL;
    IErrorRecords    *pIErrorRecords    = NULL;
    ERRORINFO        errorInfo          = { 0 };
    IErrorInfo       *pIErrorInfoRecord = NULL;
	
	CString message = L"";
	char str[255];
    try
    {
        // This interface supports returning error information.
        // Get the error object from the system for the current
        // thread.
        hr = GetErrorInfo(0, &pIErrorInfo);
        if ( hr == S_FALSE )
        {
            message = "No error occured.";
            return message;
        }

        if(FAILED(hr) || NULL == pIErrorInfo)
            throw sErrIErrorInfo;

        // The error records are retrieved from the IIErrorRecords
        // interface, which can be obtained from the IErrorInfo
        // interface.
        hr = pIErrorInfo->QueryInterface(IID_IErrorRecords,
            (void **) &pIErrorRecords);
        if ( FAILED(hr) || NULL == pIErrorRecords )
            throw sErrIErrorRecords;

        // The IErrorInfo interface is no longer required because
        // we have the IErrorRecords interface, relase it.
        pIErrorInfo->Release();
        pIErrorInfo = NULL;

        ULONG ulNumErrorRecs = 0;

        // Determine the number of records in this error object
        hr = pIErrorRecords->GetRecordCount(&ulNumErrorRecs);
        if ( FAILED(hr) )
            throw sErrRecordCount;


        // Loop over each error record in the error object to display 
        // information about each error. Errors are returned. 
        for (DWORD dwErrorIndex = 0;
             dwErrorIndex < ulNumErrorRecs;
             dwErrorIndex++)
        {
            // Retrieve basic error information for this error.
            hr = pIErrorRecords->GetBasicErrorInfo(dwErrorIndex,
              &errorInfo);
            if ( FAILED(hr) )
                throw sErrInfo;

            TCHAR szCLSID[64]  = { 0 };
            TCHAR szIID[64]    = { 0 };
            TCHAR szDISPID[64] = { 0 };

            StringFromGUID2(errorInfo.clsid, (LPOLESTR)szCLSID,
                sizeof(szCLSID));
            StringFromGUID2(errorInfo.iid, (LPOLESTR)szIID,
                sizeof(szIID));

            sprintf(str, "HRESULT           = %lx\n", errorInfo.hrError);
            message += str;
			sprintf(str, "clsid             = %S\n", szCLSID);
            message += str;
            sprintf(str, "iid               = %S\n", szIID);
            message += str;
            sprintf(str, "dispid            = %ld\n", errorInfo.dispid);
            message += str;
            sprintf(str, "Native Error Code = %lx\n", errorInfo.dwMinor);
            message += str;

            // Retrieve standard error information for this error.
            hr = pIErrorRecords->GetErrorInfo(dwErrorIndex, NULL,
                &pIErrorInfoRecord);

            if ( FAILED(hr) )
                throw sErrStandardInfo;

            BSTR bstrDescriptionOfError;
            BSTR bstrSourceOfError;

            // Get the description of the error.
            hr = pIErrorInfoRecord->GetDescription(
                   &bstrDescriptionOfError);
            if ( FAILED(hr) )
                throw sErrDescription;

            sprintf(str, "Description = %S\n", bstrDescriptionOfError);
            message += str;
			
            // Get the source of the error.
            hr = pIErrorInfoRecord->GetSource(&bstrSourceOfError);
            if ( FAILED(hr) )
                throw sErrNoSource;

            sprintf(str, "Description = %S\n", bstrSourceOfError);
            message += str;
			
            // This interface variable will be used the next time 
            // though this loop. In the last error case this interface 
            // is no longer needed so we must release it.
            if(NULL != pIErrorInfoRecord)
                pIErrorInfoRecord->Release();
            pIErrorInfoRecord = NULL;
        }
    }
	catch( CString& szMsg )
    {
        message = L"Failed to retrieve " + szMsg;
    }

    if( pIErrorInfoRecord )
        pIErrorInfoRecord->Release();

    if ( pIErrorInfo )
        pIErrorInfo->Release();

    if ( pIErrorRecords )
        pIErrorRecords->Release();

    return message;
}