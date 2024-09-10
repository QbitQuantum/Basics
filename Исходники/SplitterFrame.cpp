// Set new position for splitter
void CSplitterFrame::SetAbsPosition(CPoint pt)
{
    CWnd *pParent = GetParent();
    ASSERT(pParent!=NULL);

    pParent->ScreenToClient(&pt);
    SetWindowPos(&wndTop,pt.x,pt.y,0,0,SWP_NOSIZE);
}