// *** IContextMenu methods ***
STDMETHODIMP CShellExt::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT /*idCmdLast*/, UINT /*uFlags*/) {
	UINT idCmd = idCmdFirst;

	FORMATETC fmte = {
		CF_HDROP,
		(DVTARGETDEVICE FAR *)NULL,
		DVASPECT_CONTENT,
		-1,
		TYMED_HGLOBAL
	};

	HRESULT hres = m_pDataObj->GetData(&fmte, &m_stgMedium);

	if (SUCCEEDED(hres)) {
		if (m_stgMedium.hGlobal)
			m_cbFiles = DragQueryFile((HDROP)m_stgMedium.hGlobal, (UINT)-1, 0, 0);
	}

	UINT nIndex = indexMenu++;

	InsertMenu(hMenu, nIndex, MF_STRING|MF_BYPOSITION, idCmd++, m_szMenuTitle);

	if (m_showIcon) {
		HBITMAP icon = NULL;
		if (m_winVer >= WINVER_VISTA) {
			icon = NULL;
			HICON hicon;
			DWORD menuIconWidth = GetSystemMetrics(SM_CXMENUCHECK);
			DWORD menuIconHeight = GetSystemMetrics(SM_CYMENUCHECK);
			HRESULT hr = LoadShellIcon(menuIconWidth, menuIconHeight, &hicon);
			if (SUCCEEDED(hr)) {
				icon = IconToBitmapPARGB32(hicon, menuIconWidth, menuIconHeight);
				DestroyIcon(hicon);
			}
		} else {
			icon = HBMMENU_CALLBACK;
		}

		if (icon != NULL) {
			MENUITEMINFO mii;
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_BITMAP;
			mii.hbmpItem = icon;
			//mii.hbmpChecked = icon;
			//mii.hbmpUnchecked = icon;

			SetMenuItemInfo(hMenu, nIndex, MF_BYPOSITION, &mii);

			if (m_winVer >= WINVER_VISTA) {
				MENUINFO MenuInfo;
				MenuInfo.cbSize = sizeof(MenuInfo);
				MenuInfo.fMask = MIM_STYLE;
				MenuInfo.dwStyle = MNS_CHECKORBMP;

				SetMenuInfo(hMenu, &MenuInfo);
			}

		}
	}

	m_hMenu = hMenu;
	m_menuID = idCmd;

	return ResultFromShort(idCmd-idCmdFirst);
}