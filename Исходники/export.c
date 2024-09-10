VOID ExportFile(PMAIN_WND_INFO Info)
{
    OPENFILENAME ofn;
    TCHAR szFileName[MAX_PATH] = _T("");

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = Info->hMainWnd;
    ofn.lpstrFilter = _T("Text (Tab Delimited)(*.txt)\0*.txt\0Text (Comma Delimited)(*.csv)\0*.csv\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = _T("txt");
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

    if(GetSaveFileName(&ofn))
    {
        if (SaveServicesToFile(Info, szFileName))
            return;
    }

    if (CommDlgExtendedError() != CDERR_GENERALCODES)
        MessageBox(NULL, _T("Export to file failed"), NULL, 0);
}