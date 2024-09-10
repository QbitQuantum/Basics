BOOL CPropPageRestore::CheckData()
{
    switch(m_iSource)
    {
    case FILE_MODE:
        if(m_strBackupPath.IsEmpty())
        {
            ::AfxMessageBox(IDS_ERR_NO_BACKUP_PATH);
            CWnd*   pWnd = GetDlgItem(IDC_BACKUP_PATH_EDIT);
            GotoDlgCtrl(pWnd);
            return FALSE;
        }
        else
        {
            if(m_strBackupPath.Find(_T('.')) == -1)
            {
                m_strBackupPath += _T(".4cb");
                CWnd*   pWnd = GetDlgItem(IDC_BACKUP_PATH_EDIT);
                pWnd->SetWindowText(m_strBackupPath);
                pWnd->UpdateWindow();
            }
            CFileStatus tStatus;
            if(!CFile::GetStatus(m_strBackupPath, tStatus))
            {
                ::AfxMessageBox(_T("Specified backup file does not exist."));
                CWnd*   pWnd = GetDlgItem(IDC_BACKUP_PATH_EDIT);
                GotoDlgCtrl(pWnd);
                return FALSE;
            }
        }
        break;
    case TARGET_MODE:
        if(m_strAddress.IsEmpty())
        {
            ::AfxMessageBox(IDS_ERR_NO_ADDRESS);
            CWnd*   pWnd = GetDlgItem(IDC_ADDRESS_EDIT);
            GotoDlgCtrl(pWnd);
            return FALSE;
        }
        break;
    }

    if(m_strProjectPath.IsEmpty())
    {
        ::AfxMessageBox(IDS_ERR_NO_PROJECT_PATH);
        CWnd*   pWnd = GetDlgItem(IDC_PROJECT_PATH_EDIT);
        GotoDlgCtrl(pWnd);
        return FALSE;
    }

    CFileStatus tStatus;
    if(CFile::GetStatus(m_strProjectPath, tStatus))
    {
        CString strMessage(_T("Project Path already exists."));
        ::AfxMessageBox(strMessage);
        m_pMainSheet->SetStatusText(strMessage);
        CWnd*   pWnd = GetDlgItem(IDC_PROJECT_PATH_EDIT);
        GotoDlgCtrl(pWnd);
        return FALSE;
    }
    return TRUE;
}