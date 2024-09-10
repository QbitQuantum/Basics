void CInspectorTreeCtrl::drawValues(CPaintDC & dc)
{
    CRect rect;
    GetWindowRect(rect);

    dc.SetViewportOrg(0, 0);
    dc.SelectObject(linePen);
    dc.SetBkMode(TRANSPARENT);
    dc.SelectObject(GetFont());
    dc.SetTextColor(color_windowtext);  

    DRAWLINE(0, 0, rect.right, 0);

    int cWid0 = getColumnWidth(0);
    int cWid1 = getColumnWidth(1);

    int height = 0;
    HTREEITEM hItemFocus = GetSelectedItem();
    HTREEITEM hItem = GetFirstVisibleItem();
    while(hItem && height < rect.Height())
    {
        CRect iRect;
        GetItemRect(hItem, &iRect, FALSE);

        DRAWLINE(0, iRect.bottom, rect.right, iRect.bottom);
        height += iRect.Height();

        CTreeListItem * itemData = GetTreeListItem(hItem);
        if(itemData)
        {
            iRect.left = cWid0 + 6;
            iRect.right = cWid0 + cWid1;
            
            if(hItem == hItemFocus)
            {
                CRect whitespaceRect;
                GetItemRect(hItem, &whitespaceRect, TRUE);

                if(whitespaceRect.right < cWid0)
                {
                    whitespaceRect.left = whitespaceRect.right;
                    whitespaceRect.right = cWid0;
                
                    CWnd * focusWnd = GetFocus();
                    if(focusWnd && (focusWnd->m_hWnd == m_hWnd))        // I have focus             
                        dc.FillRect(whitespaceRect, &whitespaceHighlightBrush_Focused);                 
                    else                
                        dc.FillRect(whitespaceRect, &whitespaceHighlightBrush_Unfocused);                                   
                }               
                CString xpath;
                getTypeText(itemData->getType(), xpath, true);
                if(getFullXPath(hItem, xpath)) 
                {
                    CRect itemRect, r;
                    GetItemRect(hItem, &itemRect, FALSE);
                    r.UnionRect(&itemRect, &whitespaceRect);
                    tooltipCtrl->DelTool(this, TREE_TOOLTIP_ID);
                    tooltipCtrl->AddTool(this, xpath, r, TREE_TOOLTIP_ID);
                }
            }
            dc.DrawText(itemData->getValue(), &iRect, DT_SINGLELINE | DT_LEFT);
        }
        hItem = GetNextVisibleItem(hItem);      
    }
    DRAWLINE(cWid0, 0, cWid0, height);
}