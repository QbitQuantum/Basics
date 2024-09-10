BOOL EmbedBrowserObject(PWBOBJ pwbo)
{
	HWND hwnd;
	IOleObject			*browserObject;
	IWebBrowser2		*webBrowser2;
	RECT				rect;
	char				*ptr;
	_IOleClientSiteEx	*_iOleClientSiteEx;

	if(!pwbo)
		return FALSE;
	hwnd = pwbo->hwnd;

	if(!(ptr = (char *)GlobalAlloc(GMEM_FIXED, sizeof(_IOleClientSiteEx) + sizeof(IOleObject *))))
		return FALSE;

	_iOleClientSiteEx = (_IOleClientSiteEx *)(ptr + sizeof(IOleObject *));
	_iOleClientSiteEx->client.lpVtbl = &MyIOleClientSiteTable;
	_iOleClientSiteEx->inplace.inplace.lpVtbl = &MyIOleInPlaceSiteTable;
	_iOleClientSiteEx->inplace.frame.frame.lpVtbl = &MyIOleInPlaceFrameTable;
	_iOleClientSiteEx->inplace.frame.window = hwnd;
	_iOleClientSiteEx->ui.ui.lpVtbl = &MyIDocHostUIHandlerTable;

	if(!OleCreate((REFCLSID)&CLSID_WebBrowser, (IID *)&IID_IOleObject, OLERENDER_DRAW, 0, (IOleClientSite *)_iOleClientSiteEx, &MyIStorage, (void**)&browserObject)) {

		*((IOleObject **)ptr) = browserObject;

		// The original code uses SetWindowLong/GetWindowLong with GWL_USERDATA to store the
		// browser object pointer. we use pwbo->lparams[0] because the former is already used
		// to store the WinBinder object.

		pwbo->lparams[0] = (LONG)ptr;

//		SetWindowLong(hwnd, GWL_USERDATA, (LONG)ptr);

		browserObject->lpVtbl->SetHostNames(browserObject, L"My Host Name", 0);

		GetClientRect(hwnd, &rect);

		if(!OleSetContainedObject((struct IUnknown *)browserObject, TRUE) &&
		  !browserObject->lpVtbl->DoVerb(browserObject, OLEIVERB_SHOW, NULL, (IOleClientSite *)_iOleClientSiteEx, -1, hwnd, &rect) &&
		  !browserObject->lpVtbl->QueryInterface(browserObject, (IID *)&IID_IWebBrowser2, (void**)&webBrowser2)) {
			webBrowser2->lpVtbl->put_Left(webBrowser2, 0);
			webBrowser2->lpVtbl->put_Top(webBrowser2, 0);
			webBrowser2->lpVtbl->put_Width(webBrowser2, rect.right);
			webBrowser2->lpVtbl->put_Height(webBrowser2, rect.bottom);
			webBrowser2->lpVtbl->Release(webBrowser2);
			return TRUE;
		}

		UnEmbedBrowserObject(hwnd);
		return FALSE;
	}

	GlobalFree(ptr);
	return FALSE;
}