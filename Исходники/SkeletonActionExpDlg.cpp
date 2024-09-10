void CSkeletonActionExpDlg::LoadActionList(bool FilterByFile)
{
    m_XmlFile[0] = 0;
    OPENFILENAMEW ofn; 
    ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = ::GetActiveWindow();
    ofn.lpstrFile = m_XmlFile;
    ofn.nMaxFile = 1024;
    ofn.lpstrFilter = L"动作列表(*.xml)\0*.xml\0所有文件(*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.lpstrDefExt = L"xml";
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if(GetOpenFileNameW(&ofn) == FALSE)
    {
        return;
    }
    return LoadActionList(m_XmlFile , FilterByFile);
}