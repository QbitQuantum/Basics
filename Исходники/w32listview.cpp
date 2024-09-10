bool VDUIListViewW32::Create(IVDUIParameters *pParameters) {
	mbCheckable = pParameters->GetB(nsVDUI::kUIParam_Checkable, false);

	DWORD dwFlags = LVS_REPORT | WS_TABSTOP;

	if (pParameters->GetB(nsVDUI::kUIParam_NoHeader, false))
		dwFlags |= LVS_NOCOLUMNHEADER;

	if (!CreateW32(pParameters, WC_LISTVIEW, dwFlags))
		return false;

	ListView_SetExtendedListViewStyle(mhwnd, LVS_EX_FULLROWSELECT | ListView_GetExtendedListViewStyle(mhwnd));

	if (mbCheckable) {
		const int cx = GetSystemMetrics(SM_CXMENUCHECK);
		const int cy = GetSystemMetrics(SM_CYMENUCHECK);

		if (HBITMAP hbm = CreateBitmap(cx, cy, 1, 1, NULL)) {
			if (HDC hdc = CreateCompatibleDC(NULL)) {
				if (HGDIOBJ hbmOld = SelectObject(hdc, hbm)) {
					bool success = false;

					RECT r = { 0, 0, cx, cy };

					SetBkColor(hdc, PALETTEINDEX(0));
					ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &r, "", 0, NULL);
					DrawFrameControl(hdc, &r, DFC_BUTTON, DFCS_BUTTONCHECK|DFCS_CHECKED);

					SelectObject(hdc, hbmOld);

					if (HIMAGELIST himl = ImageList_Create(cx, cy, ILC_COLOR, 1, 1)) {
						if (ImageList_Add(himl, hbm, NULL) >= 0)
							ListView_SetImageList(mhwnd, himl, LVSIL_STATE);
						else
							ImageList_Destroy(himl);
					}
				}

				DeleteDC(hdc);
			}

			DeleteObject(hbm);
		}
	}

	return true;
}