//******************************************************************************************
void CBCGFontComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	if (m_Images.GetSafeHandle () == NULL)
	{
		CBCGLocalResource locaRes;
		m_Images.Create (IDB_BCGBARRES_FONT, nImageWidth, 0, RGB (255, 0, 255));
	}

	ASSERT (lpDIS->CtlType == ODT_COMBOBOX);

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rc = lpDIS->rcItem;
	
	if (lpDIS->itemState & ODS_FOCUS)
	{
		pDC->DrawFocusRect(rc);
	}

	int nIndexDC = pDC->SaveDC ();

	CBrush brushFill;
	if (lpDIS->itemState & ODS_SELECTED)
	{
		brushFill.CreateSolidBrush (::GetSysColor (COLOR_HIGHLIGHT));
		pDC->SetTextColor (::GetSysColor (COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		brushFill.CreateSolidBrush (pDC->GetBkColor());
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->FillRect(rc, &brushFill);

	int id = (int)lpDIS->itemID;
	if (id >= 0)
	{
		CBCGFontDesc* pDesc= (CBCGFontDesc*)lpDIS->itemData;
		if (pDesc != NULL)
		{
			if (pDesc->m_nType & (DEVICE_FONTTYPE | TRUETYPE_FONTTYPE))
			{
				CPoint ptImage (rc.left, rc.top + (rc.Height () - nImageHeight) / 2);
				m_Images.Draw (pDC, (pDesc->m_nType & DEVICE_FONTTYPE) ? 0 : 1, 
					ptImage, ILD_NORMAL);
			}

			rc.left += nImageWidth + 6;
		}
		else
		{
			rc.left += 2;
		}

		CString strText;
		GetLBText (id, strText);

		pDC->DrawText (strText, rc, DT_SINGLELINE | DT_VCENTER);
	}

	pDC->RestoreDC (nIndexDC);
}