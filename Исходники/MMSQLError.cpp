HRESULT MMSQLError::ReportErrors(HRESULT err, TCHAR *msg, FILE *stream)
{
	HRESULT hr;
	_bstr_t dummy;
	// Obtain the current Error object, if any, by using the
	// OLE Automation GetErrorInfo function, which will give
	// us back an IErrorInfo interface pointer if successful
	severity=msg[10];
	hr = GetErrorInfo(0, &pIErrorInfo);
	// We've got the IErrorInfo interface pointer on the Error object
	if( SUCCEEDED(hr) && pIErrorInfo )
	{
		// OLE DB extends the OLE Automation error model by allowing
		// Error objects to support the IErrorRecords interface; this
		// interface can expose information on multiple errors.
		hr = pIErrorInfo->QueryInterface(IID_IErrorRecords, 
			(void**)&pIErrorRecords);
		if(SUCCEEDED(hr))
		{
			// Get the count of error records from the object
			hr = pIErrorRecords->GetRecordCount(&cRecords);

			// Loop through the set of error records and
			// display the error information for each one
			for( iErr = 0; iErr < cRecords; iErr++ )
			{
				MMSQLErrorRecord theErr(err,iErr,pIErrorRecords);
				dummy=msg;
				ReportError(&theErr,(char *)dummy,stream);
//				myDisplayErrorRecord(originalError, iErr, pIErrorRecords,
//					pwszFile, ulLine);
			}
		}
		// The object didn't support IErrorRecords; display
		// the error information for this single error
		else
		{
//			myDisplayErrorInfo(hrReturned, pIErrorInfo, pwszFile, ulLine);
			MMSQLErrorRecord theErr(err,pIErrorInfo);
			dummy=msg;
			ReportError(&theErr,(char *)dummy,stream);
		}
	}
	// There was no Error object, so just display the HRESULT to the user
	else
	{
			MMSQLErrorRecord theErr(err,NULL);
			dummy=msg;
			ReportError(&theErr,(char *)dummy,stream);
	}

return hr;
} //ReportErrors