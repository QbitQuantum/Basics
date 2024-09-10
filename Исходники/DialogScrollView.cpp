// a) Child dialog resize
// b) Scroll bars handling at resize
void CDialogScrollView::OnSize(UINT nType, int cx, int cy)
{
    if (nType == SIZE_MINIMIZED) {
        return;
    }
    CDialog* pDlg = GetDialog();
    if (pDlg != NULL) {
        pDlg->SetWindowPos(NULL, 0, 0, cx, cy,
                           SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
        CRect rect;
        GetClientRect(&rect);
        CRect totalRect;
        pDlg->GetClientRect(totalRect);
        SetScrollSizes(MM_TEXT, totalRect.Size(), rect.Size());
    }
    CScrollView::OnSize(nType, cx, cy);
}