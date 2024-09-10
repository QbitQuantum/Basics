LPUNKNOWN AFXAPI _AfxCreateObjectFromStreamedPropset(LPSTREAM lpStream, REFGUID iid)
{
	LPUNKNOWN pUnk = NULL;
	CLSID clsid;

	if (_AfxGetClassIDFromStreamedPropset(&clsid, lpStream))
	{
		// Special case: we know how to create font objects
		if (IsEqualCLSID(clsid, CLSID_StdFont) ||
			IsEqualCLSID(clsid, CLSID_StdFont_V1))
		{
			if (FAILED(OleCreateFontIndirect((LPFONTDESC)&_fdDefault, iid,
					(LPVOID*)&pUnk)))
			{
				pUnk = NULL;
			}
		}
		// Special case: we know how to create picture objects
		else if (IsEqualCLSID(clsid, CLSID_StdPicture) ||
			IsEqualCLSID(clsid, CLSID_StdPicture_V1))
		{
			if (FAILED(OleCreatePictureIndirect(NULL, iid, FALSE,
					(LPVOID*)&pUnk)))
			{
				pUnk = NULL;
			}
		}
		// General case: create the object
		else if (FAILED(CoCreateInstance(clsid, NULL,
					CLSCTX_INPROC_SERVER, iid, (LPVOID*)&pUnk)))
		{
			pUnk = NULL;
		}

		if (pUnk != NULL)
		{
			if (!_AfxLoadObjectFromStreamedPropset(pUnk, lpStream))
			{
				RELEASE(pUnk);
				pUnk = NULL;
			}
		}
	}

	return pUnk;
}