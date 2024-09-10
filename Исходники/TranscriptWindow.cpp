int TranscriptWindow::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // If the edit window is visible and the user clicks outside it, end editing
    if (m_edit.IsWindowVisible())
    {
        CPoint point(::GetMessagePos());
        ScreenToClient(&point);

        if (ChildWindowFromPoint(point) != &m_edit)
            m_edit.EndEdit();
    }
    return CView::OnMouseActivate(pDesktopWnd,nHitTest,message);
}