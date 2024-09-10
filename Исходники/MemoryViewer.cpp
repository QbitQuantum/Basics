void MemoryViewer::OnSetFocus(CWnd* pOldWnd)
{
  setCaretPos();
  InvalidateRect(NULL, TRUE);
}