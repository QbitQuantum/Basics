FARINTERNAL_(BOOL) UtIsFormatSupported(IDataObject FAR* lpDataObj,
		DWORD dwDirection, CLIPFORMAT cfFormat)
{
	VDATEHEAP();

	FORMATETC formatetc; // a place to fetch formats from the enumerator
	IEnumFORMATETC FAR* penm; // enumerates the formats of [lpDataObj]
	ULONG ulNumFetched; // a count of the number of formats fetched
	HRESULT error; // the error state so far

	// try to get the enumerator from the data object
	error = lpDataObj->EnumFormatEtc(dwDirection, &penm);

	if (error != NOERROR)
	{                       
		if (FAILED(error))
			return FALSE;
		else
		{
			CLSID clsid;

			// Use reg db; this case is primarily for the OLE1
			// compatibility code since it may talk to a data
			// object from a server in the same process as
			// the server.
			if (UtGetClassID(lpDataObj, &clsid) != TRUE)
				return(FALSE);

			// synthesize an enumerator
			// REVIEW, if the data object is synthesized for
			// the OLE1 object, why doesn't that implementation
			// go ahead and synthesize this?  Why does it have
			// to be done like this?  What if it's on the clipboard
			// and someone wants to use it?
			if (OleRegEnumFormatEtc(clsid, dwDirection, &penm)
					!= NOERROR)
				return FALSE;
			Assert(penm);
		}
	}

	// check for the format we're looking for
	while(NOERROR == (error = penm->Next(1, &formatetc, &ulNumFetched)))
	{
		if ((ulNumFetched == 1) && (formatetc.cfFormat == cfFormat))
			break;
	}
	
	// release the enumerator
	penm->Release();

	// if error isn't S_FALSE, we fetched an item, and broke out of the
	// while loop above --> the format was found.  Return TRUE indicating
	// that the format is supported
	return(error == NOERROR ? TRUE : FALSE);
}