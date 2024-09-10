void fsODMenu::OnDrawItem(LPDRAWITEMSTRUCT pdis)
{
	CDC *dc = CDC::FromHandle (pdis->hDC);
	fsODMenuItemData* pData = (fsODMenuItemData*) pdis->itemData;
	UINT uState = pdis->itemState;
	CFont *oldfont = dc->SelectObject (pData->bBold ? &m_fontBold : &m_font);

	RECT rcItem = pdis->rcItem;
	
	RECT rcIcon = rcItem;
	rcIcon.left += 3;
	rcIcon.right = rcIcon.left + m_cxIcon;
	rcIcon.top += (rcIcon.bottom - rcIcon.top - m_cyIcon) / 2;
	rcIcon.bottom = rcIcon.top + m_cyIcon;

	RECT rcIconFrame = rcIcon;
	InflateRect (&rcIconFrame, 2, 2);

	RECT rcSel;
	
	if (pData->bMenuBar)
	{
		rcSel = pdis->rcItem;
		InflateRect (&rcSel, -1, -1);
		fsFillSolidRect (dc, &rcItem, GetSysColor (COLOR_3DFACE));
	}
	else
	{
		rcSel = rcIconFrame;
		rcSel.right = rcItem.right;
		rcSel.bottom++;
		
		fsFillSolidRect (dc, &rcItem, GetSysColor (COLOR_MENU));
		rcItem.left += m_cxIcon;
	}
	
	if (pData->strMenuText.GetLength () == 0)
	{
		RECT rect = rcItem;
		rect.left -= m_cxIcon;
		rect.top += (rect.bottom - rect.top) / 2;
		rect.bottom = rect.top+1;
		rect.right = rcItem.right;
		fsFillSolidRect (dc, &rect, GetSysColor (COLOR_GRAYTEXT));
		return;
	}

	if (uState & 0x40 )
		if (pData->bMenuBar)
			fsDrawFrame (dc, &rcSel, 1);

	if (uState & ODS_SELECTED)	
	{
		if (pData->bMenuBar)
			fsDrawPressedFrame (dc, &rcSel, 1);	
		else
		{
			
			fsFillSolidRect (dc, &rcSel, GetSysColor (COLOR_HIGHLIGHT));
		}
	}

	dc->SetBkMode (TRANSPARENT);

	if (pData->bMenuBar)
	{
		
		if (uState & ODS_GRAYED || uState & ODS_DISABLED) 
			dc->SetTextColor (GetSysColor (COLOR_GRAYTEXT));
		dc->DrawText (pData->strMenuText, &rcItem, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	}
	else
	{
		CPen pen (PS_SOLID, 1, GetSystemMetrics (COLOR_HIGHLIGHTTEXT));

		CPen *oldpen = dc->SelectObject (&pen);

		if (uState & ODS_GRAYED || uState & ODS_DISABLED) 
			dc->SetTextColor (GetSysColor (COLOR_GRAYTEXT));
		else if (uState & ODS_SELECTED)
			dc->SetTextColor (GetSysColor (COLOR_HIGHLIGHTTEXT));
		else
			dc->SetTextColor (GetSysColor (COLOR_MENUTEXT));

		

		LPCSTR pszTab = strchr (pData->strMenuText, '\t');
		int left = pszTab ? pszTab - pData->strMenuText : pData->strMenuText.GetLength ();

		rcItem.left += 9; rcItem.right -= 15;
		dc->DrawText (pData->strMenuText, left, &rcItem, DT_VCENTER | DT_SINGLELINE);

		if (pszTab)
			dc->DrawText (pszTab+1, -1, &rcItem, DT_VCENTER | DT_SINGLELINE | DT_RIGHT);

		dc->SelectObject (oldpen);
	}

	

	POINT ptIcon;
	ptIcon.x = rcIcon.left + 1;
	ptIcon.y = rcIcon.top + 1;

	RECT rcClr = pdis->rcItem;
	rcClr.right = m_cxIcon + 5;

	if (uState & ODS_CHECKED)
	{
		if (pData->iCheckImage >= 0)
		{
			fsFillSolidRect (dc, &rcClr, GetSysColor (COLOR_MENU));
			m_pImages->Draw (dc, pData->iCheckImage, ptIcon, ILD_TRANSPARENT);
		}
		else if (pData->iImage >= 0)
		{
			fsFillSolidRect (dc, &rcClr, GetSysColor (COLOR_MENU));
			
			
			rcIconFrame.right--;
			fsDrawPressedFrame (dc, &rcIconFrame, 1);
			m_pImages->Draw (dc, pData->iImage, ptIcon, ILD_TRANSPARENT);
		}
		else
		{
			CFont font;
			char check;
			int fsize;

			switch (pData->iCheckImage)
			{
				case ODMENU_CHECKIMAGE_CHECK:
				{
					DrawCheckMark (dc, rcIcon, uState & ODS_SELECTED, uState & ODS_GRAYED);
					
				}
				break;

				case ODMENU_CHECKIMAGE_RADIO:
				{
					check = 105;
					fsize = m_cyIcon;
					font.CreateFont (fsize, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Marlett");
					CFont* oldfont = dc->SelectObject (&font);
					dc->DrawText (&check, 1, &rcIcon, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					dc->SelectObject (oldfont);
				}
				break;

				default:
					return;
			}
		}
	}
	else if (pData->iImage != -1)
	{
		fsFillSolidRect (dc, &rcClr, GetSysColor (COLOR_MENU));

		if (uState & ODS_GRAYED || uState & ODS_DISABLED)
		{
			if (m_pDisImages == NULL)
			{
				HICON hI = m_pImages->ExtractIcon (pData->iImage);

				DrawState (dc->m_hDC, NULL, NULL, LPARAM (hI), 0, ptIcon.x, ptIcon.y, m_cxIcon, m_cyIcon, 
					DST_ICON | DSS_DISABLED);

				DestroyIcon (hI); 
			}
			else
				m_pDisImages->Draw (dc, pData->iImage, ptIcon, ILD_TRANSPARENT);

		}
		else
		{
			if (uState & ODS_SELECTED)
				fsDrawFrame (dc, &rcIconFrame, 1);

			m_pImages->Draw (dc, pData->iImage, ptIcon, ILD_TRANSPARENT);
		}
	}

	dc->SelectObject (oldfont);
}