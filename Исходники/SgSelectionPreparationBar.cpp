BOOL CSgSelectionPreparationBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   CPoint ptCursor;
   GetCursorPos(&ptCursor);
   CRect rcClient;
   GetClientRect(&rcClient);

   CRect rcDrag;
   rcDrag.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.top + 15);

   ScreenToClient(&ptCursor);
   if(rcDrag.PtInRect(ptCursor))
      SetCursor(LoadCursor(NULL, IDC_HAND));

   return CWnd::OnSetCursor(pWnd, nHitTest, message);;
}