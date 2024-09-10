void FileScrapDropDlg::OnContextMenu(CWnd* pWnd, CPoint pt) 
{
    BCMenu sMenu;
    if (sMenu.LoadMenu(IDR_FILE_SCRAP_DROP) == XPR_TRUE)
    {
        if (pt.x == -1 || pt.y == -1)
        {
            CRect sRect;
            GetClientRect(&sRect);
            ClientToScreen(&sRect);
            pt = sRect.TopLeft();
        }

        BCMenu *sPopupMenu = (BCMenu *)sMenu.GetSubMenu(0);
        if (XPR_IS_NOT_NULL(sPopupMenu))
        {
            sPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt, this);
        }
    }
}