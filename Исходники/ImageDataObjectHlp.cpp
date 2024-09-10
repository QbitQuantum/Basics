// returns true on success, false on failure
//bool InsertBitmap(IRichEditOle* pRichEditOle, HBITMAP hBitmap, HGLOBAL hGlobal)
bool InsertBitmap(IRichEditOle* pRichEditOle, HENHMETAFILE hEmf)
{
	SCODE sc;

	// Get the image data object
	//
	static const FORMATETC lc_format[] =
	{
		{ CF_ENHMETAFILE, 0, DVASPECT_CONTENT, -1, TYMED_ENHMF }//,
		//		{ CF_BITMAP, 0, DVASPECT_CONTENT, -1, TYMED_GDI },
		//		{ CF_TEXT,   0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL } 
	};

	STGMEDIUM lc_stgmed[] =
	{
		{ TYMED_ENHMF, { (HBITMAP)hEmf }, 0 }//,
		//		{ TYMED_GDI, { hBitmap }, 0 },
		//		{ TYMED_HGLOBAL, { (HBITMAP)hGlobal }, 0 }
	};

	IDataObject *pods;
	CreateDataObject(lc_format, lc_stgmed, 1, &pods);

	// Get the RichEdit container site
	//
	IOleClientSite *pOleClientSite;
	pRichEditOle->GetClientSite(&pOleClientSite);

	// Initialize a Storage Object
	//
	LPLOCKBYTES lpLockBytes = NULL;
	sc = CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
	{
		pOleClientSite->Release();
		return false;
	}

	IStorage *pStorage;
	sc = StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);
	if (sc != S_OK)
	{
		lpLockBytes->Release();
		pOleClientSite->Release();
		return false;
	}

	// The final ole object which will be inserted in the richedit control
	//
	IOleObject *pOleObject;
	sc = OleCreateStaticFromData(pods, IID_IOleObject, OLERENDER_FORMAT,
		(LPFORMATETC)lc_format, pOleClientSite, pStorage, (void **)&pOleObject);
	if (sc != S_OK)
	{
		pStorage->Release();
		lpLockBytes->Release();
		pOleClientSite->Release();
		return false;
	}

	// all items are "contained" -- this makes our reference to this object
	//  weak -- which is needed for links to embedding silent update.
	OleSetContainedObject(pOleObject, TRUE);

	// Now Add the object to the RichEdit 
	//
	REOBJECT reobject = { 0 };

	reobject.cbStruct = sizeof(REOBJECT);
	reobject.cp = REO_CP_SELECTION;
	reobject.dvaspect = DVASPECT_CONTENT;
	reobject.poleobj = pOleObject;
	reobject.polesite = pOleClientSite;
	reobject.pstg = pStorage;
	reobject.dwFlags = REO_BELOWBASELINE;

	sc = pOleObject->GetUserClassID(&reobject.clsid);
	if (sc != S_OK)
	{
		pOleObject->Release();
		pStorage->Release();
		lpLockBytes->Release();
		pOleClientSite->Release();
		return false;
	}

	// Insert the bitmap at the current location in the richedit control
	//
	sc = pRichEditOle->InsertObject(&reobject);

	// Release all unnecessary interfaces
	//
	pOleObject->Release();
	pStorage->Release();
	lpLockBytes->Release();
	pOleClientSite->Release();
	pods->Release();

	return sc == S_OK;
}