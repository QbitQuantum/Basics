void CDownloadClientsCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (!theApp.emuledlg->IsRunning())
		return;
	if (!lpDrawItemStruct->itemData)
		return;

	CMemDC dc(CDC::FromHandle(lpDrawItemStruct->hDC), &lpDrawItemStruct->rcItem);
	BOOL bCtrlFocused;
	InitItemMemDC(dc, lpDrawItemStruct, bCtrlFocused);
	CRect cur_rec(lpDrawItemStruct->rcItem);
	CRect rcClient;
	GetClientRect(&rcClient);
	const CUpDownClient *client = (CUpDownClient *)lpDrawItemStruct->itemData;

	CHeaderCtrl *pHeaderCtrl = GetHeaderCtrl();
	int iCount = pHeaderCtrl->GetItemCount();
	cur_rec.right = cur_rec.left - sm_iLabelOffset;
	cur_rec.left += sm_iIconOffset;
	for (int iCurrent = 0; iCurrent < iCount; iCurrent++)
	{
		int iColumn = pHeaderCtrl->OrderToIndex(iCurrent);
		if (!IsColumnHidden(iColumn))
		{
			UINT uDrawTextAlignment;
			int iColumnWidth = GetColumnWidth(iColumn, uDrawTextAlignment);
			cur_rec.right += iColumnWidth;
			if (cur_rec.left < cur_rec.right && HaveIntersection(rcClient, cur_rec))
			{
				TCHAR szItem[1024];
				GetItemDisplayText(client, iColumn, szItem, _countof(szItem));
				switch (iColumn)
				{
					case 0:{
						int iImage;
						if (client->credits != NULL)
						{
							if (client->IsFriend())
								iImage = 4;
							else if (client->GetClientSoft() == SO_EDONKEYHYBRID) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 8;
								else
									iImage = 7;
							}
							else if (client->GetClientSoft() == SO_MLDONKEY) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 6;
								else
									iImage = 5;
							}
							else if (client->GetClientSoft() == SO_SHAREAZA) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 10;
								else
									iImage = 9;
							}
							else if (client->GetClientSoft() == SO_AMULE) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 12;
								else
									iImage = 11;
							}
							else if (client->GetClientSoft() == SO_LPHANT) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 14;
								else
									iImage = 13;
							}
							else if (client->ExtProtocolAvailable()) {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 3;
								else
									iImage = 1;
							}
							else {
								if (client->credits->GetScoreRatio(client->GetIP()) > 1)
									iImage = 2;
								else
									iImage = 0;
							}
						}
						else
							iImage = 0;

						UINT nOverlayImage = 0;
						if ((client->Credits() && client->Credits()->GetCurrentIdentState(client->GetIP()) == IS_IDENTIFIED))
							nOverlayImage |= 1;
						if (client->IsObfuscatedConnectionEstablished())
							nOverlayImage |= 2;
						int iIconPosY = (cur_rec.Height() > 16) ? ((cur_rec.Height() - 16) / 2) : 1;
						POINT point = { cur_rec.left, cur_rec.top + iIconPosY };
						m_ImageList.Draw(dc, iImage, point, ILD_NORMAL | INDEXTOOVERLAYMASK(nOverlayImage));

						cur_rec.left += 16 + sm_iLabelOffset;
						dc.DrawText(szItem, -1, &cur_rec, MLC_DT_TEXT | uDrawTextAlignment);
						cur_rec.left -= 16;
						cur_rec.right -= sm_iSubItemInset;
						break;
					}

					case 4:
						cur_rec.bottom--;
						cur_rec.top++;
						client->DrawStatusBar(dc, &cur_rec, false, thePrefs.UseFlatBar());
						cur_rec.bottom++;
						cur_rec.top--;
						break;

					default:
						dc.DrawText(szItem, -1, &cur_rec, MLC_DT_TEXT | uDrawTextAlignment);
						break;
				}
			}
			cur_rec.left += iColumnWidth;
		}
	}

	DrawFocusRect(dc, lpDrawItemStruct->rcItem, lpDrawItemStruct->itemState & ODS_FOCUS, bCtrlFocused, lpDrawItemStruct->itemState & ODS_SELECTED);
}