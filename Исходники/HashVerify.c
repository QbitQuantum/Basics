LONG_PTR WINAPI HashVerifySetColor( PHASHVERIFYCONTEXT phvctx, LPNMLVCUSTOMDRAW pcd )
{
	switch (pcd->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
			return(CDRF_NOTIFYITEMDRAW);

		case CDDS_ITEMPREPAINT:
		{
			// We need to determine the highlight state during the item stage
			// because this information becomes subitem-specific if we try to
			// retrieve it when we actually need it in the subitem stage

			if (g_uWinVer >= 0x0600 && IsAppThemed())
			{
				// Clear the highlight bit...
				phvctx->dwFlags &= ~HVF_ITEM_HILITE;

				// uItemState is buggy; if LVS_SHOWSELALWAYS is set, uItemState
				// will ALWAYS have the CDIS_SELECTED bit set, regardless of
				// whether the item is actually selected, so a more expensive
				// test for the LVIS_SELECTED bit is needed...
				if ( pcd->nmcd.uItemState & CDIS_HOT ||
				     ListView_GetItemState(pcd->nmcd.hdr.hwndFrom, pcd->nmcd.dwItemSpec, LVIS_SELECTED) )
				{
					phvctx->dwFlags |= HVF_ITEM_HILITE;
				}
			}

			return(CDRF_NOTIFYSUBITEMDRAW);
		}

		case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
		{
			PHASHVERIFYITEM pItem;

			if (pcd->nmcd.dwItemSpec >= phvctx->cTotal)
				break;  // Invalid index

			pItem = phvctx->index[pcd->nmcd.dwItemSpec];

			// By default, we use the default foreground and background colors
			// except when the item is a mismatch or is unreadable, in which
			// case, we change the foreground color
			switch (pItem->uStatusID)
			{
				case HV_STATUS_MISMATCH:
					pcd->clrText = RGB(0xC0, 0x00, 0x00);
					break;

				case HV_STATUS_UNREADABLE:
					pcd->clrText = RGB(0x80, 0x80, 0x80);
					break;

				default:
					pcd->clrText = CLR_DEFAULT;
			}

			pcd->clrTextBk = CLR_DEFAULT;

			// The status column, however, deserves special treatment
			if (pcd->iSubItem == HV_COL_STATUS)
			{
				if (phvctx->dwFlags & HVF_ITEM_HILITE)
				{
					// Vista-style highlighting means that the foreground
					// color can show through, but not the background color
					if (pItem->uStatusID == HV_STATUS_MATCH)
						pcd->clrText = RGB(0x00, 0x80, 0x00);
				}
				else
				{
					switch (pItem->uStatusID)
					{
						case HV_STATUS_MATCH:
							pcd->clrText = RGB(0x00, 0x00, 0x00);
							pcd->clrTextBk = RGB(0x00, 0xE0, 0x00);
							break;

						case HV_STATUS_MISMATCH:
							pcd->clrText = RGB(0xFF, 0xFF, 0xFF);
							pcd->clrTextBk = RGB(0xC0, 0x00, 0x00);
							break;

						case HV_STATUS_UNREADABLE:
							pcd->clrText = RGB(0x00, 0x00, 0x00);
							pcd->clrTextBk = RGB(0xFF, 0xE0, 0x00);
							break;
					}
				}
			}

			break;
		}
	}

	return(CDRF_DODEFAULT);
}