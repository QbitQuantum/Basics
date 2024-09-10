// IDocHostUIHandler
STDMETHODIMP IEView::ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdTarget, IDispatch *pdispReserved) {
	IOleCommandTarget * pOleCommandTarget;
    IOleWindow * pOleWindow;
	HWND hSPWnd;
	if (builder == NULL) {
   //     return S_OK;
	}
#ifdef GECKO
	{
		return E_NOTIMPL;
/*
		HMENU hMenu;
		hMenu = GetSubMenu(LoadMenu(hInstance, MAKEINTRESOURCE(IDR_CONTEXTMENU)),0);
		CallService(MS_LANGPACK_TRANSLATEMENU,(WPARAM)hMenu,0);
		if (dwID == 6) { // anchor
			EnableMenuItem(hMenu, ID_MENU_COPYLINK, MF_BYCOMMAND | MF_ENABLED);
		} else if (dwID == 5) { // text select
			EnableMenuItem(hMenu, ID_MENU_COPY, MF_BYCOMMAND | MF_ENABLED);
		} else if (dwID == 1) { // control (image)
			EnableMenuItem(hMenu, ID_MENU_SAVEIMAGE, MF_BYCOMMAND | MF_ENABLED);
		}
		if (builder!=NULL) {

		}
		int iSelection = TrackPopupMenu(hMenu,
										  TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
										  ppt->x,
										  ppt->y,
										  0,
										  hwnd,
										  (RECT*)NULL);
		DestroyMenu(hMenu);
		if (iSelection == ID_MENU_CLEARLOG) {
			clear(NULL);
		} else {
			SendMessage(hSPWnd, WM_COMMAND, iSelection, (LPARAM) NULL);
		}
*/
	}
#else
    if (SUCCEEDED(pcmdTarget->QueryInterface(IID_IOleCommandTarget, (void**)&pOleCommandTarget))) {
		if (SUCCEEDED(pOleCommandTarget->QueryInterface(IID_IOleWindow, (void**)&pOleWindow))) {
    		pOleWindow->GetWindow(&hSPWnd);
			HMENU hMenu;
			hMenu = GetSubMenu(LoadMenu(hInstance, MAKEINTRESOURCE(IDR_CONTEXTMENU)),0);
		 	CallService(MS_LANGPACK_TRANSLATEMENU,(WPARAM)hMenu,0);
			if (dwID == 5) { // anchor
				EnableMenuItem(hMenu, ID_MENU_COPYLINK, MF_BYCOMMAND | MF_ENABLED);
			} else if (dwID == 4) { // text select
				EnableMenuItem(hMenu, ID_MENU_COPY, MF_BYCOMMAND | MF_ENABLED);
			} else if (dwID == 1) { // control (image)
				EnableMenuItem(hMenu, ID_MENU_SAVEIMAGE, MF_BYCOMMAND | MF_ENABLED);
			}
            if (builder!=NULL) {

			}
		 	int iSelection = TrackPopupMenu(hMenu,
		                                      TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
		                                      ppt->x,
		                                      ppt->y,
		                                      0,
		                                      hwnd,
		                                      (RECT*)NULL);
			DestroyMenu(hMenu);
			if (iSelection == ID_MENU_CLEARLOG) {
				clear(NULL);
			} else {
		    	SendMessage(hSPWnd, WM_COMMAND, iSelection, (LPARAM) NULL);
			}
    		pOleWindow->Release();
		}
	    pOleCommandTarget->Release();
	}
#endif
	return S_OK;
}