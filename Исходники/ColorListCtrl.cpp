//***************************************************************
void CColorListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    if (!lpDrawItemStruct) return;
    IsCreated=TRUE;
	CDC*		pDC			= CDC::FromHandle(lpDrawItemStruct->hDC);
	CMyLParam*	pMyLParam	= GetMyLParam(lpDrawItemStruct->itemID);
	CRect		rcItem;

    if (!pMyLParam) return;
    int x=0;
    typedef enum {R_NOTHINGS=0, R_FOCUS, R_SELECT, R_NORMAL, R_SEL_NOFOCUS} redrawmode;
    redrawmode redraw=R_NORMAL;

	// Get item image and state info
	LV_ITEM lvi;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = lpDrawItemStruct->itemID;
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetItem(&lvi);

	BOOL bHighlight =   (   (lvi.state & LVIS_DROPHILITED)
                            ||
				            (
                                (lvi.state & LVIS_SELECTED) 
                                && 
                                (  ( GetFocus() == this )  || ( GetStyle() & LVS_SHOWSELALWAYS ) )
					        )
				        );

    BOOL bLostFocus=(GetFocus()!=this);


    if ( (lpDrawItemStruct->itemAction&ODA_FOCUS)==ODA_FOCUS)
    {   //the control gains or loses input focus
        if (bLostFocus) redraw=R_SEL_NOFOCUS;
        else
        if ((lvi.state&LVIS_FOCUSED)==LVIS_FOCUSED) redraw=R_FOCUS;
        else 
        {
            if (bHighlight) redraw=R_SELECT;
            else redraw=R_NORMAL;
        }
    }
    else
    if ((lpDrawItemStruct->itemAction&ODA_SELECT)==ODA_SELECT)
    {   //the selection status has changed
            if (bHighlight)
            {
                if (bLostFocus) redraw=R_SEL_NOFOCUS;
                 else redraw=R_SELECT;
            }
            else redraw=R_NORMAL;
    }
    else
    {   //redraw the item
        if (bLostFocus)
        {
            if (bHighlight) redraw=R_SEL_NOFOCUS;
             else
              redraw=R_NORMAL;
        }
        else 
        {
            if ((lvi.state&LVIS_FOCUSED)==LVIS_FOCUSED) redraw=R_FOCUS;
            else 
            {
                if (bHighlight) redraw=R_SELECT;
                 else redraw=R_NORMAL;
            }
        }
    }

    CPen       *pOldPen;
    CPen        pen;
    CGdiObject *pOldBrush;

    switch(redraw)
    {

        case R_FOCUS:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, GetColorRef(DEF_SELBACKGROUND));
            pDC->SetTextColor(GetColorRef(DEF_SELTEXT));
            if (m_BigFocusRect)
            {
                pen.CreatePen( PS_DOT, 0, GetColorRef(DEF_SELTEXT) );
                pOldPen  =pDC->SelectObject(&pen);
                pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
                pDC->Rectangle(rcItem);
                pDC->SelectObject(pOldPen);
                pDC->SelectObject(pOldBrush);
            }
            else pDC->DrawFocusRect(rcItem);
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
            }
            break;
        case R_SELECT:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, GetColorRef(DEF_SELBACKGROUND));
            pDC->SetTextColor(GetColorRef(DEF_SELTEXT));
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            break;
        case R_SEL_NOFOCUS:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, GetColorRef(DEF_DESELBACKGROUND));
            pDC->SetTextColor(pMyLParam->GetTextColor(DEF_DESELTEXT));
            pen.CreatePen( PS_DOT, 0, GetColorRef(DEF_DESELBACKGROUND) );
            pOldPen  =pDC->SelectObject(&pen);
            pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
            if (!m_withSingleRect)
                pDC->Rectangle(rcItem);
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            pDC->SelectObject(pOldPen);
            pDC->SelectObject(pOldBrush);
            break;
        case R_NORMAL:
            for (x=0; x<m_columnSize; x++)
            {
	            rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, TRUE);
                pDC->FillSolidRect(rcItem, pMyLParam->GetBackColor(x));
                pDC->SetTextColor(pMyLParam->GetTextColor(x));
                if (m_withSingleRect)
                {
                    pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
                    pDC->Rectangle(rcItem);
                    pDC->SelectObject(pOldBrush);
                    
                }
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            break;
    }

    return;
}