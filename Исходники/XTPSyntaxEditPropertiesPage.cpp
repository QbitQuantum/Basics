AFX_STATIC int CALLBACK EnumFontFamExProc(
	ENUMLOGFONTEX *lpelfe,    // logical-font data
	NEWTEXTMETRICEX *lpntme,  // physical-font data
	DWORD FontType,           // type of font
	LPARAM lParam)            // application-defined data
{
	CComboBox* pWndCombo = DYNAMIC_DOWNCAST(CComboBox, (CComboBox*)lParam);
	if (::IsWindow(pWndCombo->GetSafeHwnd()))
	{
		switch (pWndCombo->GetDlgCtrlID())
		{
		case XTP_IDC_EDIT_COMB_NAMES:
			{
				//if (lpelfe->elfLogFont.lfPitchAndFamily & FIXED_PITCH)
				{
					// Make sure the fonts are only added once.
					if (pWndCombo->FindStringExact(0, (LPCTSTR)lpelfe->elfFullName) == CB_ERR)
					{
						// Add to list
						pWndCombo->AddString((LPCTSTR)lpelfe->elfLogFont.lfFaceName);
					}
				}
			}
			break;
		case XTP_IDC_EDIT_COMB_SIZES:
			{
				if (FontType != TRUETYPE_FONTTYPE)
				{
					CWindowDC dc(NULL);
					CString csSize;
					csSize.Format(_T("%i"), ::MulDiv(lpntme->ntmTm.tmHeight - lpntme->ntmTm.tmInternalLeading,
						72, ::GetDeviceCaps(dc.m_hDC, LOGPIXELSY)));

					// Make sure the fonts are only added once.
					if (pWndCombo->FindStringExact(0, (LPCTSTR)csSize) == CB_ERR)
					{
						// Add to list
						pWndCombo->AddString((LPCTSTR)csSize);
					}
				}
			}
			break;
		case XTP_IDC_EDIT_COMB_SCRIPT:
			{
				if (lpelfe->elfScript[0] != _T('\0'))
				{
					// Make sure the fonts are only added once.
					if (pWndCombo->FindStringExact(0, (LPCTSTR)lpelfe->elfScript) == CB_ERR)
					{
						// Add to list
						int iIndex = pWndCombo->AddString((LPCTSTR)lpelfe->elfScript);
						if (iIndex != CB_ERR)
						{
							pWndCombo->SetItemData(iIndex,
								(DWORD)lpelfe->elfLogFont.lfCharSet);
						}
					}
				}
			}
			break;
		}
	}
	return TRUE;
}