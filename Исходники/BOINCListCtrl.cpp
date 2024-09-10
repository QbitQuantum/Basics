void CBOINCListCtrl::DrawProgressBars()
{
    long topItem, numItems, numVisibleItems, i, row;
    wxRect r, rr;
    int w = 0, x = 0, xx, yy, ww;
    int progressColumn = m_pParentView->GetProgressColumn();
    
#if USE_NATIVE_LISTCONTROL
    wxClientDC dc(this);
    m_bProgressBarEventPending = false;
#else
    wxClientDC dc(GetMainWin());   // Available only in wxGenericListCtrl
#endif

    if (progressColumn < 0) {
        m_iRowsNeedingProgressBars.Clear();
        return;
    }

    int n = (int)m_iRowsNeedingProgressBars.GetCount();
    if (n <= 0) return;
    
    wxColour progressColor = wxTheColourDatabase->Find(wxT("LIGHT BLUE"));
    wxBrush progressBrush(progressColor);
    
    numItems = GetItemCount();
    if (numItems) {
        topItem = GetTopItem();     // Doesn't work properly for Mac Native control in wxMac-2.8.7

        numVisibleItems = GetCountPerPage();
        ++numVisibleItems;

        if (numItems <= (topItem + numVisibleItems)) numVisibleItems = numItems - topItem;

        x = 0;
        for (i=0; i< progressColumn; i++) {
            x += GetColumnWidth(i);
        }
        w = GetColumnWidth(progressColumn);
        
#if USE_NATIVE_LISTCONTROL
        x -= GetScrollPos(wxHORIZONTAL);
#else
        GetMainWin()->CalcScrolledPosition(x, 0, &x, &yy);
#endif
        wxFont theFont = GetFont();
        dc.SetFont(theFont);
        
        for (int i=0; i<n; ++i) {
            row = m_iRowsNeedingProgressBars[i];
            if (row < topItem) continue;
            if (row > (topItem + numVisibleItems -1)) continue;
        

            GetItemRect(row, r);
#if ! USE_NATIVE_LISTCONTROL
            r.y = r.y - GetHeaderHeight() - 1;
#endif
            r.x = x;
            r.width = w;
            r.Inflate(-1, -2);
            rr = r;

            wxString progressString = m_pParentView->GetProgressText(row);
            dc.GetTextExtent(progressString, &xx, &yy);
            
            r.y += (r.height - yy - 1) / 2;
            
            // Adapted from ellipis code in wxRendererGeneric::DrawHeaderButtonContents()
            if (xx > r.width) {
                int ellipsisWidth;
                dc.GetTextExtent( wxT("..."), &ellipsisWidth, NULL);
                if (ellipsisWidth > r.width) {
                    progressString.Clear();
                    xx = 0;
                } else {
                    do {
                        progressString.Truncate( progressString.length() - 1 );
                        dc.GetTextExtent( progressString, &xx, &yy);
                    } while (xx + ellipsisWidth > r.width && progressString.length() );
                    progressString.append( wxT("...") );
                    xx += ellipsisWidth;
                }
            }
            
            dc.SetLogicalFunction(wxCOPY);
            dc.SetBackgroundMode(wxSOLID);
            dc.SetPen(progressColor);
            dc.SetBrush(progressBrush);
            dc.DrawRectangle( rr );

            rr.Inflate(-2, -1);
            ww = rr.width * m_pParentView->GetProgressValue(row);
            rr.x += ww;
            rr.width -= ww;

#if 0
            // Show background stripes behind progress bars
            wxListItemAttr* attr = m_pParentView->FireOnListGetItemAttr(row);
            wxColour bkgd = attr->GetBackgroundColour();
            dc.SetPen(bkgd);
            dc.SetBrush(bkgd);
#else
            dc.SetPen(*wxWHITE_PEN);
            dc.SetBrush(*wxWHITE_BRUSH);
#endif
            dc.DrawRectangle( rr );

            dc.SetPen(*wxBLACK_PEN);
            dc.SetBackgroundMode(wxTRANSPARENT);
            if (xx > (r.width - 7)) {
                dc.DrawText(progressString, r.x, r.y);
            } else {
                dc.DrawText(progressString, r.x + (w - 8 - xx), r.y);
            }
        }
    }
    m_iRowsNeedingProgressBars.Clear();
}