//***************************************************************
void CMyColorList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    if (!lpDrawItemStruct) return;
	CDC*		pDC			= CDC::FromHandle(lpDrawItemStruct->hDC);
	int m=GetHeaderCtrl()->GetItemCount();
	for(int i=0;i<m;i++)
	{
		CString str;
		CRect rcItem;
		GetSubItemRect(lpDrawItemStruct->itemID,i,LVIR_LABEL,rcItem);
		str=GetItemText(lpDrawItemStruct->itemID,i);
		CMyColor *col=(CMyColor *)m_ArrayCol.GetAt(lpDrawItemStruct->itemID);
		pDC->SetBkMode(TRANSPARENT);
		CBrush brush;
		brush.CreateSolidBrush(col->colBack);
		pDC->FillRect(rcItem,&brush);
		pDC->SetTextColor(col->colText);
		LV_ITEM lvi;
		lvi.mask = LVIF_IMAGE | LVIF_STATE;
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.iSubItem = 0;
		lvi.stateMask = 0xFFFF;		// get all state flags
		GetItem(&lvi);
		if((lvi.state & LVIS_SELECTED)||(lvi.state & LVIS_FOCUSED))
		{
			if(m_blnSelect)
			{
				int r1=GetRValue(col->colSelect);
				int g1=GetGValue(col->colSelect);
				int b1=GetBValue(col->colSelect);
				for(int i=rcItem.Height()/2;i>0;i--)
				{
					r1=(r1+5)>255?255:(r1+5);
					g1=(g1+5)>255?255:(g1+5);
					b1=(b1+5)>255?255:(b1+5);
					CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
					CPen *old = pDC->SelectObject(&pen);
					pDC->MoveTo(rcItem.left,rcItem.top+i);
					pDC->LineTo(rcItem.right,rcItem.top+i);
					pDC->MoveTo(rcItem.left,rcItem.bottom-i);
					pDC->LineTo(rcItem.right,rcItem.bottom-i);
					pDC->SelectObject(old);
				}
			}
		}
		int nAlign=atoi(m_ArrayHeaderAlign.GetAt(i));
		if(i==0&&GetImageList(LVSIL_SMALL)!=NULL)
		{		
			CPoint ptImage;
			ptImage.x=rcItem.left;
			ptImage.y=rcItem.top;
			GetImageList(LVSIL_SMALL)->Draw(pDC,lvi.iImage,ptImage,ILD_TRANSPARENT);
			pDC->SetBkMode(TRANSPARENT);
			rcItem.left=rcItem.left+16;
			if(nAlign==LVCFMT_LEFT)
				rcItem.left=rcItem.left+8;
		}

		switch(nAlign)
		{
		case LVCFMT_LEFT:
			pDC->DrawText(str,rcItem,DT_LEFT);
			break;
		case LVCFMT_CENTER:
			pDC->DrawText(str,rcItem,DT_CENTER);
			break;
		case LVCFMT_RIGHT:
			pDC->DrawText(str,rcItem,DT_RIGHT);	
			break;
		default:
			pDC->DrawText(str,rcItem,DT_CENTER);
			break;
		}

	}
}