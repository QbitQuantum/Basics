ShortCutItem *ShortCutManager::MakeSystemShortCut(int systemIndex)
{
    MYICON_INFO info = MyGetIconInfo(m_initIcon[systemIndex]);
    ShortCutItem *p = new ShortCutItem(this, m_dockPanelDlg, m_initIconTitle[systemIndex].GetBuffer(), DuplicateIcon(NULL, m_initIcon[systemIndex]), true, systemIndex);
    RECT rc;
    p->Create((CWnd *)m_dockPanelDlg, CRect(10, 10, 210, 30), _T("Nice Work"));
    return p;
}