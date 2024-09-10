/*----------------------------------------------------------------------------------------------
	Creates an error object and then sets a description from a resource id. Also sets a full
	help URL as required by HtmlHelp. Uses ierr as an index for both resource id and help URL.
	@param ierr Index to a set of htm help files (second part of full help URL) and matching
	resource strings for Message Box text.
	@param pei [out] Error info object
----------------------------------------------------------------------------------------------*/
void LgKeymanHandler::ThrowErrorWithInfo(HRESULT hrErr, int stidDescription)
{
	IErrorInfoPtr qei;
	ICreateErrorInfoPtr qcei;

	// Create error info object.
	CheckHr(CreateErrorInfo(&qcei));

	StrUni stu(stidDescription);
	CheckHr(qcei->SetDescription((wchar *)stu.Chars()));

	// Now get the IErrorInfo interface of the error object and set it for the current thread.
	CheckHr(qcei->QueryInterface(IID_IErrorInfo, (void **)&qei));
	SetErrorInfo(0, qei);

	ThrowHr(hrErr, stu.Chars(), -1, qei);	// An error object exists.
}