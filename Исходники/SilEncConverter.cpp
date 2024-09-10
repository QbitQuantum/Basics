// here's a helper function for displaying useful error messages
BOOL ProcessHResult(HRESULT hr, IUnknown* p, const IID& iid)
{
	if( hr == S_OK )
		return true;

	// otherwise, throw a _com_issue_errorex and catch it (so we can use it to get
	//  the error description out of it for us.
	try
	{
		_com_issue_errorex(hr, p, iid);
	}
	catch(_com_error & er)
	{
		if( er.Description().length() > 0)
		{
			::MessageBox(NULL, er.Description(), strCaption, MB_OK);
		}
		else
		{
			::MessageBox(NULL, er.ErrorMessage(), strCaption, MB_OK);
		}
	}

	return false;
}