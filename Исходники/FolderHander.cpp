void CFolderHander::OnBtnFileTypes(EventArgs *pEvt)
{
    SWindow *pBtn = sobj_cast<SWindow>(pEvt->sender);
    CRect rcBtn = pBtn->GetWindowRect();
    HWND hWnd = pBtn->GetContainer()->GetHostHwnd();
    ::ClientToScreen(hWnd,(LPPOINT)&rcBtn);
    ::ClientToScreen(hWnd,(LPPOINT)&rcBtn+1);

    SMenu menu;
    menu.LoadMenu(_T("menu_filetype"),_T("xml"));
    for(int i=0;i<(int)m_lstLangExts.GetCount();i++)
    {
        SStringW strDesc = m_lstLangExts[i].strLang+L":"+m_lstLangExts[i].strExts;
        menu.InsertMenu(i,MF_BYPOSITION,i+10,S_CW2T(strDesc),-1);
    }

    int id = menu.TrackPopupMenu(TPM_RIGHTALIGN|TPM_RETURNCMD,rcBtn.right,rcBtn.bottom,hWnd);
    if(id!=0)
    {
        id-=10;
        SEdit *pEdit = m_pFolderRoot->FindChildByName2<SEdit>(L"edit_filetypes");
        SASSERT(pEdit);
        if(pEdit->GetWindowTextLength()!=0)
        {
            pEdit->SetSel((DWORD)-1);
            pEdit->ReplaceSel(L";");            
        }
        pEdit->SetSel((DWORD)-1);
        pEdit->ReplaceSel(m_lstLangExts[id].strExts);
    }
}