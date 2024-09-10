void CStudentSmsDlg::OnSmsInputNotify(EventArgs *e)
{
    EventRENotify *e2 = sobj_cast<EventRENotify>(e);
    if(e2->iNotify != EN_CHANGE) return;
    SEdit *pEdit = sobj_cast<SEdit>(e->sender);
    int nLen = pEdit->GetWindowTextLength();
    SWindow *pWordCount = FindChildByID(R.id.txt_wordcount); 
    pWordCount->SetWindowText(SStringT().Format(_T("%d"),nLen));
    pWordCount->EnableWindow(nLen<100,TRUE);
}