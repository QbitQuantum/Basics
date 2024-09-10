void CGfxPopupMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
//	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
//	CRect rcItem(lpDrawItemStruct->rcItem);
//	pDC->FillSolidRect(rcItem, RGB(255,0,0));
	if (lpDrawItemStruct->CtlType == ODT_MENU)
	{
		UINT id = lpDrawItemStruct->itemID;
		UINT state = lpDrawItemStruct->itemState;
		bool bEnab = !(state & ODS_DISABLED);
		bool bSelect = (state & ODS_SELECTED) ? true : false;
		bool bChecked = (state & ODS_CHECKED) ? true : false;
		// David 08/04/98 - start - bold font handling
		bool bBold = (state & ODS_DEFAULT) ? true : false;
		// David 08/04/98 - end - bold font handling

		SpawnItem * pItem = (SpawnItem *) lpDrawItemStruct->itemData;
		if (pItem)
		{
			CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
			CFont * pft;
			// David 08/04/98 - start - bold font handling
			if (!bBold) pft = CFont::FromHandle((HFONT) hMenuFont ? hMenuFont : hGuiFont);
			else pft = CFont::FromHandle((HFONT) hMenuBoldFont ? hMenuBoldFont : hGuiFont);
			// David 08/04/98 - end - bold font handling
			CFont * of = pDC->SelectObject(pft);

			CRect rc(lpDrawItemStruct->rcItem);
			CRect rcImage(rc), rcText(rc);
			rcImage.right = rcImage.left + rc.Height();
			rcImage.bottom = rc.bottom;

			if (pItem->iCmd == -3) // is a separator
			{
				CPen pnDk(PS_SOLID,1,cr3dShadow);
				CPen pnLt(PS_SOLID,1,cr3dHilight);
				CPen * opn = pDC->SelectObject(&pnDk);
				pDC->MoveTo(rc.left + 2, rc.top + 2);
				pDC->LineTo(rc.right - 2, rc.top + 2);
				pDC->SelectObject(&pnLt);
				pDC->MoveTo(rc.left + 2, rc.top + 3);
				pDC->LineTo(rc.right - 2, rc.top + 3);
				pDC->SelectObject(opn);
			}
			else if (pItem->iCmd == -4) // is a title item
			{
				CString cs(pItem->cText), cs1;
				CRect rcBdr(rcText);

				if (bSelect && bEnab)
				{
					rcText.top ++;
					rcText.left += 2;
				}
				pDC->FillSolidRect(rcText, crMenu);
				pDC->DrawText(cs, rcText, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				if (bSelect && bEnab) pDC->Draw3dRect(rcBdr,cr3dShadow,cr3dHilight);
			}
			else
			{
				rcText.left += rcImage.right + 1;

				int obk = pDC->SetBkMode(TRANSPARENT);
				
				COLORREF ocr;
				if (bSelect)
				{
					if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
						pDC->FillSolidRect(rcText, crHighlight);
					else
						pDC->FillSolidRect(rc, crHighlight);

					ocr = pDC->SetTextColor(crMenuTextSel);
				}
				else
				{
					if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
						pDC->FillSolidRect(rcText, crMenu);
					else
						pDC->FillSolidRect(rc/*rcText*/, crMenu);
					ocr = pDC->SetTextColor(crMenuText);
				}

				if (pItem->iImageIdx >= 0)
				{
					int ay = (rcImage.Height() - szImage.cy) / 2;
					int ax = (rcImage.Width()  - szImage.cx) / 2;

					if (bSelect && bEnab)
						pDC->Draw3dRect(rcImage,cr3dHilight,cr3dShadow);
					else
					{
						pDC->Draw3dRect(rcImage,crMenu,crMenu);
					}


					if (bEnab)
					{
						ilList.Draw(pDC, pItem->iImageIdx, CPoint(rcImage.left + ax, rcImage.top +ay), ILD_NORMAL);
					}
					else
					{
						HICON hIcon = ilList.ExtractIcon( pItem->iImageIdx );
						pDC->DrawState( CPoint(rcImage.left + ax, rcImage.top + ay ), szImage, (HICON)hIcon, DST_ICON | DSS_DISABLED, (CBrush *)NULL );
					}
				}
				else
				{
					if (bChecked)
					{
						int ay = (rcImage.Height() - szImage.cy) / 2;
						int ax = (rcImage.Width()  - szImage.cx) / 2;

						ilOther.Draw(pDC, 0, CPoint(rcImage.left + ax, rcImage.top + ay - 2), ILD_NORMAL);
					}
				}

				CString cs(pItem->cText), cs1;
				CSize sz;
				sz = pDC->GetTextExtent(cs);
				int ay1 = (rcText.Height() - sz.cy) / 2;
				rcText.top += ay1;
				rcText.left += 2;
				rcText.right -= 15;

				int tf = cs.Find('\t');
				if (tf >= 0)
				{
					cs1 = cs.Right(cs.GetLength() - tf - 1);
					cs = cs.Left(tf);
					if (!bEnab)
					{
						if (!bSelect)
						{
							CRect rcText1(rcText);
							rcText1.InflateRect(-1,-1);
							pDC->SetTextColor(cr3dHilight);
							pDC->DrawText(cs, rcText1, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText1, DT_VCENTER|DT_RIGHT);
							pDC->SetTextColor(crGrayText);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
						}
						else
						{
							pDC->SetTextColor(crMenu);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
							pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
						}
					}
					else
					{
						pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT);
						pDC->DrawText(cs1, rcText, DT_VCENTER|DT_RIGHT);
					}
				}
				else 
				{
					if (!bEnab)
					{
						if (!bSelect)
						{
							CRect rcText1(rcText);
							rcText1.InflateRect(-1,-1);
							pDC->SetTextColor(cr3dHilight);
							pDC->DrawText(cs, rcText1, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
							pDC->SetTextColor(crGrayText);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
						else
						{
							pDC->SetTextColor(crMenu);
							pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
					}
					else
						pDC->DrawText(cs, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
				}
				pDC->SetTextColor(ocr);
				pDC->SetBkMode(obk);
			}

			pDC->SelectObject(of);
		}
	}
}