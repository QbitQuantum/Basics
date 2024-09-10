void CDuiItemBox::EnsureVisible(CDuiWindow *pItem)
{
    if(!HasScrollBar(TRUE)) return;
    DUIASSERT(pItem);
    CRect rcItem;
    pItem->GetRect(&rcItem);
    int yOffset=0;
    if(rcItem.bottom>m_rcWindow.bottom)
    {
        yOffset=rcItem.bottom-m_rcWindow.bottom;
    }
    else if(rcItem.top<m_rcWindow.top)
    {
        yOffset=rcItem.top-m_rcWindow.top;
    }
    SetScrollPos(TRUE,GetScrollPos(TRUE)+yOffset,TRUE);
}