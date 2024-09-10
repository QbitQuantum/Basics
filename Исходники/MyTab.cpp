BOOL CMyTab::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
    {
        BOOL bPrevious = (GetAsyncKeyState(VK_SHIFT) & 0x8000)?TRUE:FALSE;
        CWnd* pDummy = NULL;
        CWnd* pFirst = this->GetNextDlgTabItem(pDummy);
        CWnd* pLast = this->GetNextDlgTabItem(pFirst, TRUE);
        CWnd* pActive = this->GetFocus();
        CWnd* pNext = this->GetNextDlgTabItem(pActive, bPrevious);
        if( ( ( (pNext == pFirst && !bPrevious) || (bPrevious && pNext == pLast)) || pActive == pNext ) && GetParent())
        {
            if(bPrevious)
                GetParent()->SetFocus();
            else
            {
                pNext = AfxGetMainWnd()->GetNextDlgTabItem(GetParent());
                if(pNext)
                    pNext->SetFocus();
            }
            return TRUE;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}